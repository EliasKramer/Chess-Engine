#include "HumanPlayer.h"

HumanPlayer::HumanPlayer()
	:Player("Human Player")
{}

HumanPlayer::HumanPlayer(std::string name)
	:Player(name)
{}

int HumanPlayer::get_move(
	const ChessBoard& board,
	const MoveList& moves)
{
	while (true)
	{
		std::string input;
		std::cout << "Please enter your move: \n";
		std::cin >> input;

		int i = 0;
		for (const Move curr : moves)
		{
			if (input == curr.get_string())
			{
				return i;
			}
			i++;
		}
		std::cout << "That was not a valid move\n";
	}
}