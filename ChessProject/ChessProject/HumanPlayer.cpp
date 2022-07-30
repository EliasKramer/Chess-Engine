#include "HumanPlayer.h"

HumanPlayer::HumanPlayer()
{
}

Move* HumanPlayer::getNextMove(std::vector<Move*> possibleMoves)
{
	while (1)
	{
		std::cout << "Type input like that: 'a1 to a2'\n";

		char input[100];
		std::cin.getline(input, sizeof(input));

		std::string rawInput = input;
		//input check todo
		std::cout << "raw: " << rawInput << "\n\n";

		std::string starCoordString = rawInput.substr(0, 2);
		std::string endCoordString = rawInput.substr(6, 2);

		std::cout << "starCoordString: " << starCoordString << "\n";
		std::cout << "endCoordString: " << endCoordString << "\n";

		std::cout << "all moves: \n";
		for (Move* currMove : possibleMoves)
		{
			std::cout << "currMove: " << currMove->getStart().toString()
				<< " to " << currMove->getDestination().toString() << "\n";
			
			if (currMove->getStart().toString() == starCoordString &&
				currMove->getDestination().toString() == endCoordString)
			{
				std::cout << "do move\n";
				return currMove;
			}
		}
		std::cout << "\n\nmove not found try again\n\n";

	}
}
