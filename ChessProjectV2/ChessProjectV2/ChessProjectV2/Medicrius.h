#pragma once
#include "Player.h"

//https://translate.google.com/?sl=en&tl=la&text=doctor%20average&op=translate
//An intelligent player, that can play quite good

class Medicrius : public Player
{
public:
	int getMove(const ChessBoard& board, const UniqueMoveList& moves) override;
	
	int evaluateBoard(const ChessBoard& board);
	
private:
	int getMoveRecursively(ChessBoard board, int depth, int& notesSearched);
};