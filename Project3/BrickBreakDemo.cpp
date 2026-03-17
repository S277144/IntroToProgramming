#include <iostream>
#include <SDL3\SDL.h>
#include <format>
#include <string>
#include <random>
#include <ctime>

int main()
{
	constexpr int ScreenWidth = 1100;
	constexpr int ScreenHeight = 1300;

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
	const float PlayerSpeed{ 0.1f };

	SDL_FRect player_one{ PlayerOneX, ScreenHeight - 150, PadWidth, PadHeight };

	const float BallDim{ 12.5f };
	const float BallX = { ScreenWidth / 2.0f - BallDim / 2.0f };
	const float BallY = { ScreenHeight / 2.0f - BallDim / 2.0f };
	const float Ballspeed{ 0.08f };

	SDL_FRect ball{ BallX, BallY, BallDim, BallDim };

	float POneX = PlayerX;
	float ballX = BallX;
	float ballY = BallY;

	float velX = Ballspeed;
	float velY = Ballspeed;;

	bool isAPressed{ false };
	bool isDPressed{ false };

	bool flippedX{ false };
	bool flippedY{ false };

	constexpr int BlockColumns{ 10 };
	constexpr int BlockRows{ 6 };
	constexpr float BlockGap{ 10.0f };

	constexpr float BlockAreaWidth = ScreenWidth - BlockGap;
	constexpr float BlockAreaHeight = ScreenHeight / 2.3f;

	constexpr float BlockWidth = (BlockAreaWidth - BlockGap * BlockColumns) / BlockColumns;
	constexpr float BlockHeight = BlockAreaHeight / BlockRows;

	constexpr float Border = ScreenHeight - BlockAreaHeight;

	int Playerlives { 3 };

	bool destroyedblocks[BlockColumns * BlockRows];
	int sz = BlockColumns * BlockRows;

	//int Random(int min, int max);
	//{
	//	int min = 1;
	//	int max = 3;

	//	static std::random_device rd;
	//	static std::mt19937 gen(rd());
	//	std::uniform_real_distribution<int> dist(min, max);
	//}

	// block Grid Spawning 

	SDL_FRect blockRect{ BlockGap, BlockWidth, BlockHeight };
	SDL_FRect blocks[BlockRows * BlockColumns];
	int blockHealth[BlockRows * BlockColumns];

	for (int y = 0; y < BlockRows; y++)
	{
		for (int x = 0; x < BlockColumns; x++)
		{
			int index = x + y * BlockColumns;
			destroyedblocks[index] = false;

			blocks[index].x = BlockGap + x * (BlockWidth + BlockGap);
			blocks[index].y = BlockGap + y * (BlockHeight + BlockGap);

			blocks[index].w = BlockWidth;
			blocks[index].h = BlockHeight;

			/*std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
			std::uniform_int_distribution<int> healthDist(1, 3);*/

			blockHealth[index] = 3;
		}
	}


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

		// Ball respawning and lives system

		if (ball.y > ScreenHeight - 100)
		{
			ball.x = ScreenWidth / 2.0f - BallDim / 2.0f;
			ball.y = ScreenHeight / 2.0f - BallDim / 2.0f;

			velX *= -1;

			Playerlives -= 1;

			std::cout << "1 life from Player\n";
		}

		// Block Grid Manager

		for (int y = 0; y < BlockRows; y++)
		{
			for (int x = 0; x < BlockColumns; x++)
			{
				int index = y + x * BlockRows;

				if (!destroyedblocks[index] && SDL_HasRectIntersectionFloat(&ball, &blocks[index]))
				{
					if (ball.x < blocks[index].x || ball.x + BallDim > blocks[index].x + BlockWidth)
					{
						velX *= -1;
						flippedX = true;
					}

					if (ball.y < blocks[index].y || ball.y + BallDim > blocks[index].y + BlockHeight)
					{
						velY *= -1;
						flippedY = true;
					}

					blockHealth[index] -= 1;

					if (blockHealth[index] == 0)
					{
						destroyedblocks[index] = true;
					}

					std::string log = std::format("ball (pos {}, {}) (vel {}, {}) intersected brick [{}] x:{}, {}, y: {}, {} - flipped x {}, flipped y {}\n",
						ball.x, ball.y, velX, velY, index, blocks[index].x, blocks[index].x + BlockWidth, blocks[index].y, blocks[index].y + BlockHeight, flippedX, flippedY);
				}
			}
		}

		// End state

		bool gameOvergood{ true };
		for (int i = 0; i < sz; i++)
		{
			if (!destroyedblocks[i]) 
			{
				gameOvergood = false;
				break;
			}
		}

		// Block lives system

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		for (int y = 0; y < BlockRows; y++)
		{
			for (int x = 0; x < BlockColumns; x++)
			{
				int index = y + x * BlockRows;

				if (blockHealth[index] == 3)
				{
					SDL_SetRenderDrawColor(renderer, 222, 88, 61, 255);
				}

				if (blockHealth[index] == 2)
				{
					SDL_SetRenderDrawColor(renderer, 236, 201, 73, 255);
				}

				if (blockHealth[index] == 1)
				{
					SDL_SetRenderDrawColor(renderer, 80, 235, 183, 255);
				}

				if (destroyedblocks[index])continue;

				SDL_RenderFillRect(renderer, &blocks[index]);
			}
		}

		// End state and rendering 

		SDL_FRect border{ 0, ScreenHeight - 100.0f, ScreenWidth, 100.0f };
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderFillRect(renderer, &border);

		SDL_FRect pointone{ 100, ScreenHeight - 100, 40.0f, ScreenHeight };
		SDL_SetRenderDrawColor(renderer, 80, 235, 183, 255);
		SDL_RenderFillRect(renderer, &pointone);

		SDL_FRect pointtwo{ 200, ScreenHeight - 100, 40.0f, ScreenHeight};
		SDL_SetRenderDrawColor(renderer, 80, 235, 183, 255);
		SDL_RenderFillRect(renderer, &pointtwo);

		SDL_FRect pointthree{ 300, ScreenHeight - 100, 40.0f, ScreenHeight };
		SDL_SetRenderDrawColor(renderer, 80, 235, 183, 255);
		SDL_RenderFillRect(renderer, &pointthree);

		SDL_SetRenderDrawColor(renderer, 80, 235, 183, 255);
		SDL_RenderFillRect(renderer, &player_one);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &ball);

		if (gameOvergood)
		{
			SDL_FRect EndG{ 0, 0, BlockAreaWidth, ScreenHeight - 100 };
			SDL_SetRenderDrawColor(renderer, 141, 247, 41, 255);
			SDL_RenderFillRect(renderer, &EndG);

			velX = 0;
		}

		if (Playerlives == 2)
		{
			SDL_FRect pointthree{ 300, ScreenHeight - 100, 40.0f, ScreenHeight };
			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
			SDL_RenderFillRect(renderer, &pointthree);
		}

		if (Playerlives == 1)
		{
			SDL_FRect pointtwo{ 200, ScreenHeight - 100, 40.0f, ScreenHeight };
			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
			SDL_RenderFillRect(renderer, &pointtwo);

			SDL_FRect pointthree{ 300, ScreenHeight - 100, 40.0f, ScreenHeight };
			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
			SDL_RenderFillRect(renderer, &pointthree);
		}

		if (Playerlives == 0)
		{
			SDL_FRect Endb{ 0, 0, BlockAreaWidth, ScreenHeight - 100 };
			SDL_SetRenderDrawColor(renderer, 224, 31, 17, 255);
			SDL_RenderFillRect(renderer, &Endb);

			SDL_FRect pointone{ 100, ScreenHeight - 100, 40.0f, ScreenHeight };
			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
			SDL_RenderFillRect(renderer, &pointone);

			SDL_FRect pointtwo{ 200, ScreenHeight - 100, 40.0f, ScreenHeight };
			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
			SDL_RenderFillRect(renderer, &pointtwo);

			SDL_FRect pointthree{ 300, ScreenHeight - 100, 40.0f, ScreenHeight };
			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
			SDL_RenderFillRect(renderer, &pointthree);

			velX = 0;
			velY = 0;
		}

		SDL_RenderPresent(renderer);

    }

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}