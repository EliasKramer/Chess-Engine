#pragma once
#include "Move.h"
#include <string>
#include "ChessBoard.h"
#include <iostream>
class Player
{
protected:
	std::string _name;

public:
	Player(std::string name);

	std::string get_name();

	//returns the index of the move in the list
	virtual int get_move(const ChessBoard& board, const MoveList& moves);
};