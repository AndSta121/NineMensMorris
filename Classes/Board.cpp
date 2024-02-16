#include "Board.h"

Board::Board()
{
	for (int i = 0; i < 24; i++)
		state[i] = 0;
}

void Board::PrintStateToLog()
{
	log("Curretn state:\n");
	log("%d		%d		%d\n", state[21], state[22], state[23]);
	log("   %d    %d    %d\n", state[18], state[19], state[20]);
	log("      %d %d %d\n", state[15], state[16], state[17]);
	log("%d %d %d    %d %d %d\n", state[9], state[10], state[11], state[12], state[13], state[14]);
	log("      %d %d %d\n", state[6], state[7], state[8]);
	log("   %d    %d    %d\n", state[3], state[4], state[5]);
	log("%d		%d		%d\n", state[0], state[1], state[2]);
}

bool Board::CheckMoulinFormation(int newPosition, int player)
{
	if (newPosition == 0)
		return((state[1] == player && state[2] == player) || (state[9] == player && state[21] == player));
	if (newPosition == 1)
		return((state[0] == player && state[2] == player) || (state[4] == player && state[7] == player));
	if (newPosition == 2)
		return((state[0] == player && state[1] == player) || (state[14] == player && state[23] == player));
	if (newPosition == 3)
		return((state[4] == player && state[5] == player) || (state[10] == player && state[18] == player));
	if (newPosition == 4)
		return((state[3] == player && state[5] == player) || (state[1] == player && state[7] == player));
	if (newPosition == 5)
		return((state[3] == player && state[4] == player) || (state[13] == player && state[20] == player));
	if (newPosition == 6)
		return((state[7] == player && state[8] == player) || (state[11] == player && state[15] == player));
	if (newPosition == 7)
		return((state[6] == player && state[8] == player) || (state[4] == player && state[1] == player));
	if (newPosition == 8)
		return((state[6] == player && state[7] == player) || (state[12] == player && state[17] == player));
	if (newPosition == 9)
		return((state[0] == player && state[21] == player) || (state[10] == player && state[11] == player));
	if (newPosition == 10)
		return((state[9] == player && state[11] == player) || (state[3] == player && state[18] == player));
	if (newPosition == 11)
		return((state[9] == player && state[10] == player) || (state[6] == player && state[15] == player));
	if (newPosition == 12)
		return((state[13] == player && state[14] == player) || (state[8] == player && state[17] == player));
	if (newPosition == 13)
		return((state[12] == player && state[14] == player) || (state[5] == player && state[20] == player));
	if (newPosition == 14)
		return((state[12] == player && state[13] == player) || (state[2] == player && state[23] == player));
	if (newPosition == 15)
		return((state[16] == player && state[17] == player) || (state[6] == player && state[11] == player));
	if (newPosition == 16)
		return((state[15] == player && state[17] == player) || (state[19] == player && state[22] == player));
	if (newPosition == 17)
		return((state[15] == player && state[16] == player) || (state[8] == player && state[12] == player));
	if (newPosition == 18)
		return((state[19] == player && state[20] == player) || (state[3] == player && state[10] == player));
	if (newPosition == 19)
		return((state[18] == player && state[20] == player) || (state[16] == player && state[22] == player));
	if (newPosition == 20)
		return((state[18] == player && state[19] == player) || (state[5] == player && state[13] == player));
	if (newPosition == 21)
		return((state[22] == player && state[23] == player) || (state[0] == player && state[9] == player));
	if (newPosition == 22)
		return((state[21] == player && state[23] == player) || (state[16] == player && state[19] == player));
	if (newPosition == 23)
		return((state[21] == player && state[22] == player) || (state[2] == player && state[14] == player));
	return false;
}

bool Board::UpdateBoardStateAndCheckForMoulinFormation(int newPosition, int player)
{
	state[newPosition] = player;
	if(CheckMoulinFormation(newPosition, player))
		return true;
	return false;
}

bool Board::CheckIfPieceIsRemoveable(int newPosition, int otherPlayer)
{
	if (!CheckMoulinFormation(newPosition, otherPlayer) || CountReaminingPiecesOnBoard(otherPlayer) == 3)
		return true;
	return false;
}

int Board::CountReaminingPiecesOnBoard(int player)
{
	int cnt = 0;
	for (int i = 0; i < 24; i++)
		if (state[i] == player)
			cnt++;
	return cnt;
}

bool Board::CheckForValidMove(int newPosition, int oldPosition)
{
	if (state[newPosition] == 0) {
		if (oldPosition == 0)
			return(newPosition == 1 || newPosition==9);
		if (oldPosition == 1)
			return(newPosition == 0 || newPosition == 2 || newPosition == 4);
		if (oldPosition == 2)
			return(newPosition == 1 || newPosition == 14);
		if (oldPosition == 3)
			return(newPosition == 10 || newPosition == 4);
		if (oldPosition == 4)
			return(newPosition == 1 || newPosition == 3 || newPosition == 5 || newPosition == 7);
		if (oldPosition == 5)
			return(newPosition == 4 || newPosition == 13);
		if (oldPosition == 6)
			return(newPosition == 7 || newPosition == 11);
		if (oldPosition == 7)
			return(newPosition == 4 || newPosition == 6 || newPosition == 8);
		if (oldPosition == 8)
			return(newPosition == 7 || newPosition == 12);
		if (oldPosition == 9)
			return(newPosition == 0 || newPosition == 10 || newPosition == 21);
		if (oldPosition == 10)
			return(newPosition == 3 || newPosition == 9 || newPosition == 11 || newPosition == 18);
		if (oldPosition == 11)
			return(newPosition == 6 || newPosition == 10 || newPosition == 15);
		if (oldPosition == 12)
			return(newPosition == 8 || newPosition == 13 || newPosition == 17);
		if (oldPosition == 13)
			return(newPosition == 5 || newPosition == 12 || newPosition == 14 || newPosition==20);
		if (oldPosition == 14)
			return(newPosition == 2 || newPosition == 13 || newPosition == 23);
		if (oldPosition == 15)
			return(newPosition == 11 || newPosition == 16);
		if (oldPosition == 16)
			return(newPosition == 15 || newPosition == 17 || newPosition == 19);
		if (oldPosition == 17)
			return(newPosition == 12 || newPosition == 16);
		if (oldPosition == 18)
			return(newPosition == 10 || newPosition == 19);
		if (oldPosition == 19)
			return(newPosition == 16 || newPosition == 18 || newPosition == 20 || newPosition==22);
		if (oldPosition == 20)
			return(newPosition == 13 || newPosition == 19);
		if (oldPosition == 21)
			return(newPosition == 9 || newPosition == 22);
		if (oldPosition == 22)
			return(newPosition == 19 || newPosition == 21 || newPosition == 23);
		if (oldPosition == 23)
			return(newPosition == 14 || newPosition == 22);
	}
	return false;
}

bool Board::CheckIfPlayerCanMoveAnyOfHisPieces(int player)
{
	for (int i = 0; i < 24; i++)
		if (state[i] == player)
			if (CheckIfPlayerCanMoveSelectedPiece(i))
				return true;

	return false;
}

bool Board::CheckIfPlayerCanMoveSelectedPiece(int indexOnBoard)
{
	if (indexOnBoard == 0)
		return(state[1] == 0 || state[9] == 0);
	if (indexOnBoard == 1)
		return(state[0] == 0 || state[2] == 0 || state[14] == 0);
	if (indexOnBoard == 2)
		return(state[1] == 0 || state[14] == 0);
	if (indexOnBoard == 3)
		return(state[4] == 0 || state[10] == 0);
	if (indexOnBoard == 4)
		return(state[1] == 0 || state[3] == 0 || state[5] == 0 || state[7] == 0);
	if (indexOnBoard == 5)
		return(state[4] == 0 || state[13] == 0);
	if (indexOnBoard == 6)
		return(state[7] == 0 || state[11] == 0);
	if (indexOnBoard == 7)
		return(state[4] == 0 || state[6] == 0 || state[8] == 0);
	if (indexOnBoard == 8)
		return(state[7] == 0 || state[12] == 0);
	if (indexOnBoard == 9)
		return(state[0] == 0 || state[10] == 0 || state[21]);
	if (indexOnBoard == 10)
		return(state[3] == 0 || state[9] == 0 || state[11] == 0 || state[18] == 0);
	if (indexOnBoard == 11)
		return(state[6] == 0 || state[10] == 0 || state[11] == 0);
	if (indexOnBoard == 12)
		return(state[8] == 0 || state[13] == 0 || state[17] == 0);
	if (indexOnBoard == 13)
		return(state[5] == 0 || state[12] == 0 || state[14] == 0 || state[20] == 0);
	if (indexOnBoard == 14)
		return(state[2] == 0 || state[13] == 0 || state[23] == 0);
	if (indexOnBoard == 15)
		return(state[11] == 0 || state[16] == 0);
	if (indexOnBoard == 16)
		return(state[15] == 0 || state[17] == 0 || state[19] == 0);
	if (indexOnBoard == 17)
		return(state[12] == 0 || state[16] == 0);
	if (indexOnBoard == 18)
		return(state[10] == 0 || state[19] == 0);
	if (indexOnBoard == 19)
		return(state[16] == 0 || state[18] == 0 || state[20] == 0 || state[22] == 0);
	if (indexOnBoard == 20)
		return(state[13] == 0 || state[19] == 0);
	if (indexOnBoard == 21)
		return(state[5] == 0 || state[22] == 0);
	if (indexOnBoard == 22)
		return(state[19] == 0 || state[21] == 0 || state[23] == 0);
	if (indexOnBoard == 23)
		return(state[14] == 0 || state[22] == 0);

	return false;
}
