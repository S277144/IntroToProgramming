//#include <iostream>
//#include <vector>
//#include <SDL3\SDL.h>
//
//#include "Game.h"
//#include "Gameobject.h"
//#include "Namespace.h"
//
//int main()
//{
//	constexpr int ScreenWidth = 1350;
//	constexpr int ScreenHeight = 1350;
//
//	SDL_Init(SDL_INIT_VIDEO);
//
//	SDL_Window* window(nullptr);
//	SDL_Renderer* renderer(nullptr);
//
//	SDL_CreateWindowAndRenderer("Pong", ScreenWidth, ScreenHeight, 0, &window, &renderer);
//
//	if (window == nullptr)
//	{
//		std::cerr << "Failed to initialize SDL window\n";
//		SDL_Quit();
//		return -1;
//	}
//
//	if (renderer == nullptr)
//	{
//		std::cerr << "Failed to initialize SDL Renderer\n";
//		SDL_DestroyWindow(window);
//		SDL_Quit;
//		return -1;
//	}
//
//	// Declairs
//
//	bool running{ true };
//
//	const float PadWidth{ 20.f };
//	const float PadHeight{ 30.f };
//
//	const float PlayerX = 10.0f;
//	const float PlayerY = 10.0f;
//
//	const float Player_OneY = ScreenWidth / 2.0f - PadHeight / 2.0f;
//	const float Player_OneX = ScreenWidth / 2.0f - PadHeight / 2.0f;
//	const float PlayerSpeed{ 0.15f };
//
//	SDL_FRect player_one{ Player_OneX, Player_OneY, PadWidth, PadHeight };
//
//	const float BullDim{ 12.5f };
//	const float BullX = { ScreenWidth / 2.0f - BullDim / 2.0f };
//	const float BullY = { ScreenHeight / 2.0f - BullDim / 2.0f };
//	const float Bullspeed{ 0.05f };
//
//	SDL_FRect bullet{ BullX, BullY, BullDim, BullDim };
//	SDL_FRect astroid{};
//
//	float POneX = Player_OneX;
//	float POneY = Player_OneY;
//	float bullX = BullX;
//	float bullY = BullY;
//
//	float velX = Bullspeed;
//	float velY = Bullspeed;
//
//	bool isWPressed{ false };
//	bool isAPressed{ false };
//	bool isSPressed{ false };
//	bool isDPressed{ false };
//
//	constexpr int BlockColumns{ 10 };
//	constexpr int BlockRows{ 4 };
//	constexpr float BlockGap{ 10.0f };
//
//	constexpr float BlockAreaWidth = ScreenWidth - BlockGap;
//	constexpr float BlockAreaHeight = ScreenHeight / 3.0f;
//
//	constexpr float BlockWidth = (BlockAreaWidth - BlockGap * BlockColumns) / BlockColumns;
//	constexpr float BlockHeight = BlockAreaHeight / BlockRows;
//
//	while (running)
//	{
//		// Player movement
//
//		SDL_Event event;
//		while (SDL_PollEvent(&event))
//		{
//			if (event.type == SDL_EventType::SDL_EVENT_QUIT)
//			{
//				running = false;
//				break;
//			}
//
//			if (event.type == SDL_EventType::SDL_EVENT_KEY_DOWN)
//			{
//				if (event.key.key == SDLK_ESCAPE) running = false;
//				if (event.key.key == SDLK_W) isWPressed = true;
//				if (event.key.key == SDLK_A) isAPressed = true;
//				if (event.key.key == SDLK_S) isSPressed = true;
//				if (event.key.key == SDLK_D) isDPressed = true;
//			}
//
//			if (event.type == SDL_EventType::SDL_EVENT_KEY_UP)
//			{
//				if (event.key.key == SDLK_W) isWPressed = false;
//				if (event.key.key == SDLK_A) isAPressed = false;
//				if (event.key.key == SDLK_S) isSPressed = false;
//				if (event.key.key == SDLK_D) isDPressed = false;
//			}
//		}
//
//
//
//		if (POneX > ScreenWidth)
//		{
//			POneX = 0;
//		}
//
//		if (POneX < 0)
//		{
//			POneX = ScreenWidth - PadWidth;
//		}
//
//		if (POneY > ScreenHeight)
//		{
//			POneY = 0;
//		}
//
//		if (POneY < 0)
//		{
//			POneY = ScreenHeight - PadHeight;
//		}
//
//		player_one.x = POneX;
//		player_one.y = POneY;
//
//		if (isWPressed)
//		{
//			POneY -= PlayerSpeed;
//			//player = Gameobject::_position;
//			//POneY = Gameobject::getY;
//		}
//
//		if (isAPressed)
//		{
//			POneX -= PlayerSpeed;
//
//
//		}
//
//		if (isSPressed)
//		{
//			POneY += PlayerSpeed;
//
//
//		}
//
//		if (isDPressed)
//		{
//			POneX += PlayerSpeed;
//
//
//		}
//
//		// Shooting mechanic
//
//
//
//		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//		SDL_RenderClear(renderer);
//
//		SDL_SetRenderDrawColor(renderer, 99, 156, 99, 255);
//		SDL_RenderFillRect(renderer, &player_one);
//
//		SDL_SetRenderDrawColor(renderer, 126, 209, 240, 255);
//		SDL_RenderFillRect(renderer, &bullet);
//
//		SDL_SetRenderDrawColor(renderer, 110, 75, 54, 255);
//		SDL_RenderFillRect(renderer, &astroid);
//
//		SDL_RenderPresent(renderer);
//	}
//
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//
//	return 0;
//}