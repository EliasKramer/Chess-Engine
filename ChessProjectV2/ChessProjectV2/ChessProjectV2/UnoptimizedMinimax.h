#pragma once
#pragma once
#include "Medicrius.h"
#include <string>
#include <chrono>

//https://translate.google.com/?sl=en&tl=la&text=doctor%20average&op=translate
//An intelligent player, that can play quite good

class UnoptimizedMinimax : public Medicrius
{
public:
	int getMove(const ChessBoard& board, const UniqueMoveList& moves) override;
};