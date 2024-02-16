#pragma once
#ifndef __BOARD_H__
#define __BOARD_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Board 
{
public:
	int state[24];
	
	Board();
	void PrintStateToLog();
	bool CheckMoulinFormation(int newPosition, int player);
	bool UpdateBoardStateAndCheckForMoulinFormation(int newPosition, int player);
	bool CheckIfPieceIsRemoveable(int newPosition, int otherPlayer);
	int CountReaminingPiecesOnBoard(int player);
	bool CheckForValidMove(int newPosition, int oldPosition);
	bool CheckIfPlayerCanMoveAnyOfHisPieces(int player);
	bool CheckIfPlayerCanMoveSelectedPiece(int indexOnBoard);
};


#endif // __BOARD_H__