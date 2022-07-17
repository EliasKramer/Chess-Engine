#pragma once
#include "Move.h"
#include "MetaData.h"
class RayCastOptions
{
private:
	//the coordinate where the raycast starts
	Coordinate _origin;
	//the max number of iterations the raycast can do (-1 for disabling)
	short _maxIterations;
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
		bool needsMoveList,
		ChessColor* color);
	
	Coordinate getOrigin();
	short getMaxIterations();
	bool getNeedsMoveList();
	ChessColor getColor();
	Move getImaginaryMove();
	
	void setStart(Coordinate* val);
	void setMaxIterations(short val);
	void setNeedsMoveList(bool val);
	void setColor(ChessColor* val);
	void setImaginaryMove(Move* val);
};