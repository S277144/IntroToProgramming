//#include <iostream>
//#include <SDL3\SDL.h>
//
//int main()
//{
//	constexpr int ScreenWidth = 1100;
//	constexpr int ScreenHeight = 1400;
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
//}