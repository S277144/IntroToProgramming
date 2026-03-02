#include <iostream>

#include <SDL3\SDL.h>



struct Paddle
{
	Paddle(float y, SDL_FRect rect) : y{ y }, rect{ rect } {}
	float y;
	SDL_FRect rect;

	void AddOneToScore()
	{
		score++;
	}

	uint8_t getScore()
	{
		return score;
	}

private:
	uint8_t score{ 0 };
};

class Ball
{

	float x;
	float y;
	float vel_X;
	float vel_Y;
	SDL_FRect rect;
};

int main()
{
	constexpr int ScreenWidth = 1500;
	constexpr int ScreenHeight = 800;

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

	bool running{true};

	const float PlayArea = ScreenHeight - 150;

	const float PadWidth { 15.f };
	const float PadHeight {100.f};

	const float PlayerOneX = 10.0f;
	const float PlayerTwoX = ScreenWidth - PadWidth - PlayerOneX;
		
	const float PlayerY = ScreenHeight / 2.0f - PadHeight / 2.0f;
	const float PlayerSpeed{ 0.08f };

	Paddle player_one{ PlayerY, {PlayerOneX, PlayerY, PadWidth, PadHeight } };
	Paddle player_two{ PlayerY, {PlayerTwoX, PlayerY, PadWidth, PadHeight } };

	const float BallDim{ 12.5f };
	const float BallX = { ScreenWidth / 2.0f - BallDim / 2.0f };
	const float BallY = { ScreenHeight / 2.0f - BallDim / 2.0f };
	const float Ballspeed{ 0.11f };

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

	const int MaxScore { 5 };
	//constexpr float TallyWidth { 10.0f };
	//constexpr float TallyGap { 10.0f };
	//constexpr float TallyOneStartX { ScreenHeight - 150.0f};
	//constexpr float TallyTwoStartX { ScreenWidth - (MaxScore * (TallyWidth + TallyGap))};

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
				if (event.key.key == SDLK_W) isWPressed = true;
				if (event.key.key == SDLK_S) isSPressed = true;

				if (event.key.key == SDLK_UP) isOPressed = true;
				if (event.key.key == SDLK_DOWN) isLPressed = true;
			}

			if (event.type == SDL_EventType::SDL_EVENT_KEY_UP)
			{
				if (event.key.key == SDLK_W) isWPressed = false;
				if (event.key.key == SDLK_S) isSPressed = false;

				if (event.key.key == SDLK_UP) isOPressed = false;
				if (event.key.key == SDLK_DOWN) isLPressed = false;
			}
		}

		if (isWPressed)
		{
			player_one.y -= PlayerSpeed;
		}
		if (isSPressed)
		{
			player_one.y += PlayerSpeed;
		}

		if (isOPressed)
		{
			PTwoY -= PlayerSpeed;
		}
		if (isLPressed)
		{
			PTwoY += PlayerSpeed;
		}
		
		if (ball.y > 0)
		{
			PTwoY = ball.y;
			//POneY = ball.y;
		}

		ball.x += velX;
		ball.y += velY;

		//Stops the paddles from leaving map

		if (player_one.y < 0)
		{
			player_one.y = 0;
		}

		if (player_one.y > PlayArea - PadHeight)
		{
			player_one.y = PlayArea - PadHeight;
		}

		if (PTwoY < 0)
		{
			PTwoY = 0;
		}

		if (PTwoY > PlayArea - PadHeight)
		{
			PTwoY = PlayArea - PadHeight;
		}

		player_one.rect.y = player_one.y;
		player_two.rect.y = PTwoY;

		//Checking if ball and paddles are overlapping

		if (ball.y <= 0 || ball.y + BallDim >= PlayArea)
		{
			velY *= -1;
		}
				
		if (SDL_HasRectIntersectionFloat (&player_one.rect ,&ball))
		{
			velX *= -1;
		}

		if (SDL_HasRectIntersectionFloat(&player_two.rect, &ball))
		{
			velX *= -1;
		}

		// Ball speed up

		if (SDL_HasRectIntersectionFloat(&player_two.rect, &ball))
		{
			velX *= 1.2f;

			std::cout << velX << "\n";

			if (velX >= 5.0f)
			{
				velX = 5.0f;
			}
		}

		if (SDL_HasRectIntersectionFloat(&player_one.rect, &ball))
		{
			velX *= 1.1f;

			std::cout << velX << "\n";

			if (velX >= 4.0f)
			{
				velX = 5.0f;
			}
		}

		// Ball Spin mechanic

		if (SDL_HasRectIntersectionFloat(&player_one.rect, &ball) && PadHeight > (PadHeight - 50))
		{
			velY = Ballspeed;
		}

		if (SDL_HasRectIntersectionFloat(&player_one.rect, &ball) && (PadHeight - 50))
		{
			velY = -Ballspeed;
		}
		
		if (SDL_HasRectIntersectionFloat(&player_two.rect, &ball) && PadHeight > (PadHeight - 50))
		{
			velY = Ballspeed;
		}

		if (SDL_HasRectIntersectionFloat(&player_two.rect, &ball) && (PadHeight - 50))
		{
			velY = -Ballspeed;
		}

		// Ball respawning

		if (ball.x > ScreenWidth) 
		{
			ball.x = ScreenWidth * 0.9f - BallDim / 2.0f;
			ball.y = (ScreenHeight - 150) / 2.0f - BallDim / 2.0f;

			velX *= -1;

			player_one.AddOneToScore();

			std::cout << "1 Point to Red\n";

			velX = -Ballspeed;
		}

		if (ball.x < 0)
		{
			ball.x = ScreenWidth / 9.0f - BallDim / 2.0f;
			ball.y = (ScreenHeight - 150) / 2.0f - BallDim / 2.0f;

			velX *= -1;

			player_two.AddOneToScore();

			std::cout << "1 Point to Blue\n";

			velX = Ballspeed;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_FRect border{ 0, ScreenHeight - 150.0f, ScreenWidth, 150.0f };
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderFillRect(renderer, &border);

		float p2ScoreX = 1400;
		for (int i = 0; i < player_two.getScore(); i++) {
			SDL_FRect pointtwo{ p2ScoreX, ScreenHeight - 150.0f, 20.0f, ScreenHeight - PlayArea };
			SDL_SetRenderDrawColor(renderer, 137, 255, 255, 255);
			SDL_RenderFillRect(renderer, &pointtwo);
			p2ScoreX -= 40.0f;
		}

		float p1ScoreX = 100;
		for (int i = 0; i < player_one.getScore(); i++) {
			SDL_FRect pointone{ p1ScoreX, ScreenHeight - 150.0f, 20.0f, ScreenHeight - PlayArea };
			SDL_SetRenderDrawColor(renderer, 255, 82, 82, 255);
			SDL_RenderFillRect(renderer, &pointone);
			p1ScoreX += 40.0f;
		}

		SDL_SetRenderDrawColor(renderer, 255, 82, 82, 255);
		SDL_RenderFillRect(renderer, &player_one.rect);

		SDL_SetRenderDrawColor(renderer, 137, 255, 255, 255);
		SDL_RenderFillRect(renderer, &player_two.rect);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &ball);

		if (player_one.getScore() == 5)
		{
			SDL_FRect EndP1{ 0, 0, ScreenWidth, PlayArea };
			SDL_SetRenderDrawColor(renderer, 255, 82, 82, 255);
			SDL_RenderFillRect(renderer, &EndP1);

			velX = 0;
		}

		if (player_two.getScore() == 5)
		{
			SDL_FRect EndP2{ 0, 0, ScreenWidth, PlayArea };
			SDL_SetRenderDrawColor(renderer, 137, 255, 255, 255);
			SDL_RenderFillRect(renderer, &EndP2);

			velX = 0;
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

// vc files + add to linker >> input in properties
// 