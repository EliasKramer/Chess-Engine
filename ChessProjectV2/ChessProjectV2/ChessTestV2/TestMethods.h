#pragma once

#include "../../ChessProjectV2/ChessProjectV2/Move.h"
#include "../../ChessProjectV2/ChessProjectV2/ChessBoard.h"

bool moveListContains(Move m, const UniqueMoveList& moves);

int numberOfMovesAfterDepth(const ChessBoard& board, int depth);

UniqueMoveList getAllMovesAtDepth(const ChessBoard& board, int depth);
int getNumberOfEnPassantMoves(const UniqueMoveList& moves);
int getNumberOfPromotionMoves(const UniqueMoveList& moves);
int getNumberOfCastlingMoves(const UniqueMoveList& moves);