#include <iostream>
#include <vector>
#include <SDL3\SDL.h>

#include "DynamicArray.h"

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

	bool running{ true };

	const float PadWidth{ 150.f };
	const float PadHeight{ 15.f };

	const float PlayerX = 10.0f;

	const float PlayerX = ScreenWidth / 2.0f - PadHeight / 2.0f;
	const float PlayerSpeed{ 0.08f };

	SDL_FRect player{ PlayerX, ScreenHeight - 100, PadWidth, PadHeight };

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

		std::vector<float> stuff{};



		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 43, 250, 140, 255);
		SDL_RenderFillRect(renderer, &player);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &ball);

		SDL_RenderPresent(renderer);

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

