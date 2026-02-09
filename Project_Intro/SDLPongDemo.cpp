#include <iostream>

#include <SDL3\SDL.h>

int main()
{
	constexpr int ScreenWidth = 1200;
	constexpr int ScreenHeight = 720;

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

	bool running{true};

	const float PadWidth { 15.f };
	const float PadHeight {100.f};

	const float PlayerOneX = 10.0f;
	const float PlayerTwoX = ScreenWidth - PadWidth - PlayerOneX;
		
	const float PlayerY = ScreenHeight / 2.0f - PadHeight / 2.0f;
	const float PlayerSpeed{ 0.1f };

	SDL_FRect player_one{ PlayerOneX, PlayerY, PadWidth, PadHeight };
	SDL_FRect player_two{ PlayerTwoX, PlayerY, PadWidth, PadHeight };

	const float BallDim { 12.5f };
	const float BallX = { ScreenWidth / 2.0f - BallDim / 2.0f };
	const float BallY = { ScreenHeight / 2.0f - BallDim / 2.0f };
	const float Ballspeed{ 0.05f };

	SDL_FRect ball{ BallX, BallY, BallDim, BallDim };

	float POneY = PlayerY;
	float PTwoY = PlayerY;
	float ballX = BallX;
	float ballY = BallY;

	float velX = Ballspeed;
	float velY = Ballspeed;;

	bool isWPressed{ false };
	bool isSPressed{ false };
	bool isOPressed{ false };
	bool isLPressed{ false };

	while (running)
	{
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
				if (event.key.key == SDLK_W) isWPressed = true;
				if (event.key.key == SDLK_S) isSPressed = true;

				if (event.key.key == SDLK_O) isOPressed = true;
				if (event.key.key == SDLK_L) isLPressed = true;
			}

			if (event.type == SDL_EventType::SDL_EVENT_KEY_UP)
			{
				if (event.key.key == SDLK_W) isWPressed = false;
				if (event.key.key == SDLK_S) isSPressed = false;

				if (event.key.key == SDLK_O) isOPressed = false;
				if (event.key.key == SDLK_L) isLPressed = false;
			}
		}

		if (isWPressed)
		{
			POneY -= PlayerSpeed;
		}
		if (isSPressed)
		{
			POneY += PlayerSpeed;
		}

		if (isOPressed)
		{
			PTwoY -= PlayerSpeed;
		}
		if (isLPressed)
		{
			PTwoY += PlayerSpeed;
		}
	

		player_one.y = POneY;
		player_two.y = PTwoY;

		ball.x += velX;
		ball.y += velY;

		if (ball.y <= 0 || ball.y + BallDim >= ScreenHeight)
		{
			velY *= -1;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &player_one);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &player_two);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &ball);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

