#include <iostream>
#include <random>


//Chris's Version

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution dis(0, 100);

	const int number = dis(gen);
	int guess(-1);

	while (number != guess)
	{
		std::cout << "Enter your number between 1 and 100\n";
		std::cin >> guess;

		if (guess == number)
		{
			std::cout << "You have guessed correctly\n";
		}

		else if (guess < number)
		{
			std::cout << "Your guess was low\n";
		}

		else
		{
			std::cout << "Your guess was high\n";
		}

	}
};
