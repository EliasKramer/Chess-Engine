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

		std::vector<Move*> movesUserWantToDo;

		for (Move* currMove : possibleMoves)
		{
			/*
			std::cout << "currMove: " << currMove->getStart().toString()
				<< " to " << currMove->getDestination().toString() << "\n";
			*/
			if (currMove->getStart().toString() == starCoordString &&
				currMove->getDestination().toString() == endCoordString)
			{
				movesUserWantToDo.push_back(currMove);
			}
		}
		
		if (movesUserWantToDo.size() == 0)
		{
			std::cout << "\n\nmove not found try again\n\n";
		}
		else if (movesUserWantToDo.size()  == 1)
		{
			return movesUserWantToDo.back();
		}
		else 
		{
			while (1)
			{
				std::cout << "\n\nselect promotion piece:\n" <<
					"(Q for queen, R for rook, B for bishop, K for knight)\n";

				std::string typeInput;

				std::cin >> typeInput;
				
				for (Move* currMove : movesUserWantToDo)
				{
					//todo: cast this better
					MovePawnPromotion* move = dynamic_cast<MovePawnPromotion*>(currMove);					
					
					if (move == nullptr)
					{
						throw "something went wrong. there are multiple moves, but these are not pawn promotions";
					}
					
					PieceType type = move->getPromotionType();
					if (getShortNameOfChessType(&type) == typeInput)
					{
						return currMove;
					}
				}
			}
		}
	}
}