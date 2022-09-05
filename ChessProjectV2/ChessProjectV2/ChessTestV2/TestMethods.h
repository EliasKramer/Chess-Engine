#pragma once

#include "../../ChessProjectV2/ChessProjectV2/Move.h"
#include "../../ChessProjectV2/ChessProjectV2/ChessBoard.h"

bool moveListContains(Move m, const UniqueMoveList& moves);

int numberOfMovesAfterDepth(ChessBoard& board, int depth);