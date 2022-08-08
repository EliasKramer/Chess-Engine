#pragma once
#include "../../ChessProject/Move.h"
#include "../../ChessProject/ChessBoardTest.h"
#include <vector>
bool containsMove(const std::vector<std::unique_ptr<Move>>& list, Move x);
int getRecursivelyAllMovesForBoard(int depth, ChessColor currColor, ChessBoardTest& board);