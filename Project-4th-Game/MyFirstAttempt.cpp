//#include <iostream>
//#include <SDL3\SDL.h>
//
//int main()
//{
//	constexpr int ScreenWidth = 1800;
//	constexpr int ScreenHeight = 1000;
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
//	bool isAPressed{ false };
//	bool isSpacePressed{ false };
//	bool isDPressed{ false };
//
//	const float Gravity{};
//
//	const float PlayerWidth{ 50.f };
//	const float PlayerHeight{ 75.f };
//
//	const float PlayerY = 375.0f;
//	const float PlayerX = ScreenWidth / 2.0f;
//	const float PlayerSpeed{ 0.3f };
//
//	SDL_FRect Player{ PlayerX, PlayerY ,PlayerWidth ,PlayerHeight };
//	SDL_FRect Platfrorm1{ 0.0f, ScreenHeight - 150.0f, 750.0f, 150.0f };
//	SDL_FRect Platfrorm2{ 1100.0f, ScreenHeight - 150.0f, 750.0f, 150.0f };
//	SDL_FRect Platfrorm3{ 600.0f, 450.0f, 650.0f, 150.0f };
//
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
//				if (event.key.key == SDLK_A) isAPressed = true;
//				if (event.key.key == SDL_SCANCODE_SPACE) isSpacePressed = true;
//				if (event.key.key == SDLK_D) isDPressed = true;
//			}
//
//			if (event.type == SDL_EventType::SDL_EVENT_KEY_UP)
//			{
//				if (event.key.key == SDLK_A) isAPressed = false;
//				if (event.key.key == SDL_SCANCODE_SPACE) isSpacePressed = false;
//				if (event.key.key == SDLK_D) isDPressed = false;
//			}
//		}
//
//		if (isAPressed)
//		{
//			Player.x -= PlayerSpeed;
//		}
//
//		if (isDPressed)
//		{
//			Player.x += PlayerSpeed;
//		}
//
//		if (isSpacePressed)
//		{
//			//Player.jump;
//		}
//
//		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//		SDL_RenderClear(renderer);
//
//		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
//		SDL_RenderFillRect(renderer, &Platfrorm1);
//
//		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
//		SDL_RenderFillRect(renderer, &Platfrorm2);
//
//		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
//		SDL_RenderFillRect(renderer, &Platfrorm3);
//
//		SDL_SetRenderDrawColor(renderer, 182, 255, 35, 255);
//		SDL_RenderFillRect(renderer, &Player);
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