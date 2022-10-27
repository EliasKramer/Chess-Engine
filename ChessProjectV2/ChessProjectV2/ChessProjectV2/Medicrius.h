#pragma once
#include "Player.h"
#include "Move.h"
#include "MoveEnPassant.h"
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
protected:
	//TODO: make the selected move const
	void printSearchStatistics(
		std::string methodUsed,
		int nodesSearched,
		int endStatesEvaluated,
		int depth,
		Move selectedMove,
		int score,
		long long timeElapsed);

private:
	int getMoveScoreRecursively(
		ChessBoard board,
		int depth,
		bool isMaximizingPlayer,
		int alpha,
		int beta,
		int& nodesSearched,
		int& endStatesSearched,
		int& maxCaptureDepthReached
	);
	int getAllCaputureMoveScoreRecursively(
		ChessBoard board,
		bool isMaximizingPlayer,
		int alpha,
		int beta,
		int& nodesSearched,
		int& endStatesSearched,
		int& maxDepthReached,
		int currDepth = 0
	);
};