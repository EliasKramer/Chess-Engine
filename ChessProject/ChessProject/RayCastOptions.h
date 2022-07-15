#pragma once
#include "Move.h"
#include "MetaData.h"
class RayCastOptions
{
private:
	//the coordinate where the raycast should start
	Coordinate _start;
	//the max number of iterations the raycast can do (-1 for disabling)
	short _maxIterations;
	//adding this value to the file every iteration
	short _addingValToFile;
	//adding this value to the rank every iteration
	short _addingValToRank;
	//result needs all moves
	bool _needsMoveList;
	//color of piece you want to raycast
	ChessColor _color;
	//do the raycast as if this move is done,
	//but dont actually do it
	Move _imaginaryMove;
public:
	RayCastOptions();
	
	RayCastOptions(
		Coordinate* start,
		short maxIterations,
		short addingValToFile,
		short addingValToRank,
		bool needsMoveList,
		ChessColor* color,
		Move* imaginaryMove);
	
	Coordinate getStart();
	short getMaxIterations();
	short getAddingValToFile();
	short getAddingValToRank();
	bool getNeedsMoveList();
	ChessColor getColor();
	Move getImaginaryMove();
};

