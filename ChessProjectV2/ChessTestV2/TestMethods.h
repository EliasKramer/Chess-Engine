#pragma once

#include "../../ChessProjectV2/ChessProjectV2/Move.h"
#include "../../ChessProjectV2/ChessProjectV2/ChessBoard.h"
#include <vector>
#include <string>
#include <utility>

bool moveListContains(Move m, const UniqueMoveList& moves);

int numberOfMovesAfterDepth(const ChessBoard& board, int depth);

UniqueMoveList getAllMovesAtDepth(const ChessBoard& board, int depth);
int getNumberOfEnPassantMoves(const UniqueMoveList& moves);
int getNumberOfPromotionMoves(const UniqueMoveList& moves);
int getNumberOfCastlingMoves(const UniqueMoveList& moves);

std::vector<std::string> getAllMoveStringsAtDepth(const ChessBoard& board, std::string currStr, int depth);
std::vector<std::pair<std::string, int>> getNumberOfMovesAfterFirstMove(const ChessBoard& board, int depth);