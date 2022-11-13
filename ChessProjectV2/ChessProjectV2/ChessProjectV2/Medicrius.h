#pragma once
#include "Player.h"
#include "Move.h"
#include <string>
#include <chrono>

//https://translate.google.com/?sl=en&tl=la&text=doctor%20average&op=translate
//An intelligent player, that can play quite good

class Medicrius : public Player
{
public:
	Medicrius();
	Medicrius(std::string name);

	int get_move(const ChessBoard& board, const MoveList& moves) override;

	int evaluate_board(const ChessBoard& board);
protected:
	void print_search_statistics(
		std::string methodUsed,
		int nodesSearched,
		int endStatesEvaluated,
		int depth,
		const Move& selectedMove,
		int score,
		long long timeElapsed,
		std::string additionalInfo = ""
	);

private:
	int get_move_score_recursively(
		ChessBoard board,
		int depth,
		bool isMaximizingPlayer,
		int alpha,
		int beta,
		int& nodesSearched,
		int& endStatesSearched,
		int& maxCaptureDepthReached
	);
	int get_all_capture_moves_score_recursively(
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