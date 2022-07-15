#include "RayCastOptions.h"

RayCastOptions::RayCastOptions()
{
	_start = Coordinate();
	_maxIterations = -1;
	_addingValToFile = -1;
	_addingValToRank = -1;
	_needsMoveList = false;
	_color = ChessColor::NoColor;
	_imaginaryMove = Move();
}

RayCastOptions::RayCastOptions(
	Coordinate* start,
	short maxIterations,
	short addingValToFile,
	short addingValToRank,
	bool needsMoveList,
	ChessColor* color,
	Move* imaginaryMove)
{
	_start = *start;
	if (maxIterations <= 0)
	{
		maxIterations = -1;
	}
	_maxIterations = maxIterations;
	_addingValToFile = addingValToFile;
	_addingValToRank = addingValToRank;
	_needsMoveList = needsMoveList;
	_color = *color;
	_imaginaryMove = *imaginaryMove;
}

Coordinate RayCastOptions::getStart()
{
	return _start;
}

short RayCastOptions::getMaxIterations()
{
	return _maxIterations;
}

short RayCastOptions::getAddingValToFile()
{
	return _addingValToFile;
}

short RayCastOptions::getAddingValToRank()
{
	return _addingValToFile;
}

bool RayCastOptions::getNeedsMoveList()
{
	return _needsMoveList;
}

ChessColor RayCastOptions::getColor()
{
	return _color;
}

Move RayCastOptions::getImaginaryMove()
{
	return _imaginaryMove;
}
