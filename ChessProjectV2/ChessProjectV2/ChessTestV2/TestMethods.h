#pragma once

#include "../../ChessProjectV2/ChessProjectV2/Move.h"
#include "../../ChessProjectV2/ChessProjectV2/ChessBoard.h"
#include <vector>
#include <string>
#include <utility>

bool moveListContains(Move m, const MoveList& moves);

int numberOfMovesAfterDepth(const ChessBoard& board, int depth);

MoveList getAllMovesAtDepth(const ChessBoard& board, int depth);
int getNumberOfEnPassantMoves(const MoveList& moves);
int getNumberOfPromotionMoves(const MoveList& moves);
int getNumberOfCastlingMoves(const MoveList& moves);

std::vector<std::string> getAllMoveStringsAtDepth(const ChessBoard& board, std::string currStr, int depth);
std::vector<std::pair<std::string, int>> getNumberOfMovesAfterFirstMove(const ChessBoard& board, int depth);