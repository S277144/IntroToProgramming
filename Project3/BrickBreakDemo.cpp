#include <iostream>
#include <SDL3\SDL.h>

int main()
{
	constexpr int ScreenWidth = 1100;
	constexpr int ScreenHeight = 1400;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window(nullptr);
	SDL_Renderer* renderer(nullptr);

	SDL_CreateWindowAndRenderer("Pong", ScreenWidth, ScreenHeight, 0, &window, &renderer);

	if (window == nullptr)
	{
		std::cerr << "Failed to initialize SDL window\n";
		SDL_Quit();
		return -1;
	}

	if (renderer == nullptr)
	{
		std::cerr << "Failed to initialize SDL Renderer\n";
		SDL_DestroyWindow(window);
		SDL_Quit;
		return -1;
	}

	//Setting and declaring values

	bool running{ true };

	const float PadWidth{ 150.f };
	const float PadHeight{ 15.f };

	const float PlayerOneX = 10.0f;

	const float PlayerX = ScreenWidth / 2.0f - PadHeight / 2.0f;
	const float PlayerSpeed{ 0.08f };

	SDL_FRect player_one{ PlayerOneX, ScreenHeight - 100, PadWidth, PadHeight };

	const float BallDim{ 12.5f };
	const float BallX = { ScreenWidth / 2.0f - BallDim / 2.0f };
	const float BallY = { ScreenHeight / 2.0f - BallDim / 2.0f };
	const float Ballspeed{ 0.05f };

	SDL_FRect ball{ BallX, BallY, BallDim, BallDim };

	float POneX = PlayerX;
	float ballX = BallX;
	float ballY = BallY;

	float velX = Ballspeed;
	float velY = Ballspeed;;

	bool isAPressed{ false };
	bool isDPressed{ false };

	constexpr int BlockColumns{ 10 };
	constexpr int BlockRows{ 4 };
	constexpr float BlockGap{ 10.0f };

	constexpr float BlockAreaWidth = ScreenWidth - BlockGap;
	constexpr float BlockAreaHeight = ScreenHeight / 3.0f;

	constexpr float BlockWidth = (BlockAreaWidth - BlockGap * BlockColumns) / BlockColumns;
	constexpr float BlockHeight = BlockAreaHeight / BlockRows;

	while (running)
	{
		//Player movement 

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EventType::SDL_EVENT_QUIT)
			{
				running = false;
				break;
			}

			if (event.type == SDL_EventType::SDL_EVENT_KEY_DOWN)
			{
				if (event.key.key == SDLK_ESCAPE) running = false;
				if (event.key.key == SDLK_A) isAPressed = true;
				if (event.key.key == SDLK_D) isDPressed = true;
			}

			if (event.type == SDL_EventType::SDL_EVENT_KEY_UP)
			{
				if (event.key.key == SDLK_A) isAPressed = false;
				if (event.key.key == SDLK_D) isDPressed = false;
			}
		}

			if (isAPressed)
			{
				POneX -= PlayerSpeed;
			}
			if (isDPressed)
			{
				POneX += PlayerSpeed;
			}

			player_one.x = POneX;

			ball.x += velX;
			ball.y += velY;

			//Stops the paddles from leaving map

			if (POneX < 0)
			{
				POneX = 0;
			}

			if (POneX > ScreenWidth - 115)
			{
				POneX = ScreenWidth - 115;
			}

			//Checking if ball and paddle is overlapping

			if (ball.x <= 0 || ball.x + BallDim >= ScreenWidth || ball.y >= ScreenHeight)
			{
				velX *= -1;
			}

			if (SDL_HasRectIntersectionFloat(&player_one, &ball))
			{
				velY *= -1;
			}

			if (ball.y <= 0 )
			{
				velY *= -1;
			}

			// Ball respawning

			if (ball.y > ScreenHeight)
			{
				ball.x = ScreenWidth / 2.0f - BallDim / 2.0f;
				ball.y = ScreenHeight / 2.0f - BallDim / 2.0f;

				velX *= -1;
			}

			//Blocks spawning and functionality

			SDL_FRect blockRect{BlockGap, BlockGap, BlockWidth, BlockHeight};
			SDL_FRect blocks [BlockRows * BlockColumns];

			bool destroy_blocks [BlockRows * BlockColumns];

			for (int y = 0; y < BlockRows; y++)
			{
				for (int x = 0; x < BlockColumns; x++)
				{
					int index = y + x * BlockRows;
					destroy_blocks[index] = false;

					blocks[index].x = BlockGap + x + (BlockWidth + BlockGap);
					blocks[index].y = BlockGap + y + (BlockHeight + BlockGap);

					blocks[index].w = BlockWidth;
					blocks[index].h = BlockHeight;
				}
			}
			/*
			player.chechAgainstBounds();

			ball.rect.x += ball.vel_x;
			ball.rect.y += ball.vel_y;
			*/


			for (int y = 0; y < BlockRows; y++)
			{
				for (int x = 0; x < BlockColumns; x++)
				{
					int index = y + x * BlockRows;
					
					if (!destroy_blocks[index] && SDL_HasRectIntersectionFloat(&ball, &blocks[index]))
					{
						destroy_blocks[index] = true;
						if (ball.x < blocks[index].x || ball.x > blocks[index].x + BlockWidth)
						{
							velX *= -1;

							velY *= -1;
						}
					}
				}
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			SDL_SetRenderDrawColor(renderer, 43, 250, 140, 255);
			SDL_RenderFillRect(renderer, &player_one);

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &ball);

			SDL_SetRenderDrawColor(renderer, 222, 88, 61, 255);
			SDL_RenderFillRect(renderer, &blockRect);

			SDL_RenderPresent(renderer);

    }

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 0;
}