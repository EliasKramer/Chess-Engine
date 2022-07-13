#include "RayCastOptions.h"

RayCastOptions::RayCastOptions()
{
	_start = Coordinate();
	_maxIterations = -1;
	_addingValToFile = -1;
	_addingValToRank = -1;
	_needsMoveList = false;
	_imaginaryMove = Move();
}

RayCastOptions::RayCastOptions(
	Coordinate* start,
	short maxIterations,
	short addingValToFile,
	short addingValToRank,
	bool needsMoveList,
	Move* imaginaryMove)
{
	_start = *start;
	_maxIterations = maxIterations;
	_addingValToFile = addingValToFile;
	_addingValToRank = addingValToRank;
	_needsMoveList = needsMoveList;
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

Move RayCastOptions::getImaginaryMove()
{
	return _imaginaryMove;
}
