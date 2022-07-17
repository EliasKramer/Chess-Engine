#include "RayCastOptions.h"

RayCastOptions::RayCastOptions()
{
	_maxIterations = -1;
	_needsMoveList = false;
	_color = ChessColor::NoColor;
	_imaginaryMove = Move();
}

RayCastOptions::RayCastOptions(
	Coordinate* start,
	short maxIterations,
	bool needsMoveList,
	ChessColor* color)
{
	_origin = *start;
	if (maxIterations <= 0)
	{
		maxIterations = -1;
	}
	_maxIterations = maxIterations;
	_needsMoveList = needsMoveList;
	_color = *color;
	_imaginaryMove = Move();
}

Coordinate RayCastOptions::getOrigin()
{
	return _origin;
}

short RayCastOptions::getMaxIterations()
{
	return _maxIterations;
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
	_origin = *val;
}

void RayCastOptions::setMaxIterations(short val)
{
	_maxIterations = val;
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