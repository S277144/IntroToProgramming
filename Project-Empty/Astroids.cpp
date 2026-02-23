#include <iostream>
#include <vector>
#include <SDL3\SDL.h>

#include "player.h"

int main()
{
	constexpr int ScreenWidth = 1000;
	constexpr int ScreenHeight = 1000;

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

	bool running{ true };

	const float PadWidth{ 50.f };
	const float PadHeight{ 50.f };

	const float PlayerOneX = 10.0f;
	const float PlayerOneY = 10.0f;

	const float PlayerY = ScreenWidth / 2.0f - PadHeight / 2.0f;
	const float PlayerX = ScreenWidth / 2.0f - PadHeight / 2.0f;
	const float PlayerSpeed{ 0.08f };

	SDL_FRect player_one{ PlayerOneX, PlayerOneY, PadWidth, PadHeight };

	const float BallDim{ 12.5f };
	const float BallX = { ScreenWidth / 2.0f - BallDim / 2.0f };
	const float BallY = { ScreenHeight / 2.0f - BallDim / 2.0f };
	const float Ballspeed{ 0.05f };

	SDL_FRect ball{ BallX, BallY, BallDim, BallDim };

	float POneX = PlayerX;
	float POneY = PlayerY;
	float ballX = BallX;
	float ballY = BallY;

	float velX = Ballspeed;
	float velY = Ballspeed;;

	bool isWPressed{ false };
	bool isAPressed{ false };
	bool isSPressed{ false };
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

		std::vector<float> stuff{};

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
				if (event.key.key == SDLK_A) isAPressed = true;
				if (event.key.key == SDLK_S) isSPressed = true;
				if (event.key.key == SDLK_D) isDPressed = true;
			}

			if (event.type == SDL_EventType::SDL_EVENT_KEY_UP)
			{
				if (event.key.key == SDLK_W) isWPressed = false;
				if (event.key.key == SDLK_A) isAPressed = false;
				if (event.key.key == SDLK_S) isSPressed = false;
				if (event.key.key == SDLK_D) isDPressed = false;
			}
		}

		if (isWPressed)
		{

			POneY -= PlayerSpeed;
		}

		if (isAPressed)
		{
			POneX -= PlayerSpeed;

		}

		if (isSPressed)
		{

			POneY += PlayerSpeed;
		}

		if (isDPressed)
		{
			POneX += PlayerSpeed;

		}

		if (POneX > ScreenWidth)
		{
			POneX = 0;
		}

		if (POneX < 0)
		{
			POneX = ScreenWidth - PadWidth;
		}

		if (POneY > ScreenHeight)
		{
			POneY = 0;
		}

		if (POneY < 0)
		{
			POneY = ScreenHeight - PadHeight;
		}

		player_one.x = POneX;
		player_one.y = POneY;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 43, 250, 140, 255);
		SDL_RenderFillRect(renderer, &player_one);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &ball);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}