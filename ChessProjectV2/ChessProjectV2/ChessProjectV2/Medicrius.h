#pragma once
#include "Player.h"
#include <string>
#include <chrono>

//https://translate.google.com/?sl=en&tl=la&text=doctor%20average&op=translate
//An intelligent player, that can play quite good

class Medicrius : public Player
{
public:
	Medicrius();
	Medicrius(std::string name);

	int getMove(const ChessBoard& board, const UniqueMoveList& moves) override;
	
	int evaluateBoard(const ChessBoard& board);
	
private:
	int getMoveScoreRecursively(
		ChessBoard board,
		int depth,
		int alpha,
		int beta,
		int& nodesSearched,
		int& endStatesSearched,
		int& maxCaptureDepthReached
	);
	int getAllCaputureMoveScoreRecursively(
		ChessBoard board,
		int alpha,
		int beta,
		int& nodesSearched,
		int& endStatesSearched,
		int& maxDepthReached,
		int currDepth = 0
	);
};