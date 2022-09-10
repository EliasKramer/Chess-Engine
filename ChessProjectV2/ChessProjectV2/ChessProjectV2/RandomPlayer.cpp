#include "RandomPlayer.h"

int RandomPlayer::getMove(ChessBoard& board, UniqueMoveList& moves)
{
    //credit to stackoverflow ^^
    //https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, moves.size()-1); // define the range

    return distr(gen);
}