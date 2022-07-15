#include "RayCastOptions.h"

RayCastOptions::RayCastOptions()
{
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
	ChessColor* color)
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
	_imaginaryMove = Move();
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

void RayCastOptions::setStart(Coordinate* val)
{
	_start = *val;
}

void RayCastOptions::setMaxIterations(short val)
{
	_maxIterations = val;
}

void RayCastOptions::setAddingValFile(short val)
{
	_addingValToFile = val;
}

void RayCastOptions::setAddingValRank(short val)
{
	_addingValToRank = val;
}

void RayCastOptions::setNeedsMoveList(bool val)
{
	_needsMoveList = val;
}

void RayCastOptions::setColor(ChessColor* val)
{
	_color = *val;
}

void RayCastOptions::setImaginaryMove(Move* val)
{
	_imaginaryMove = *val;
}