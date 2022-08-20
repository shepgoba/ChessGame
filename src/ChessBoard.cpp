#include "ChessBoard.h"

// Return true on success
bool ChessBoard::MovePiece(ChessPieceLocation from, ChessPieceLocation to)
{	ChessPiece &pieceTo = board[to.y][to.x];
	const ChessPiece &pieceFrom = board[from.y][from.x];
	
	if (!pieceFrom.IsValid())
		return false;

	board[to.y][to.x] = pieceFrom;
	board[from.y][from.x] = ChessPiece(PlayerNone, PieceTypeNone);

	pieceTo.IncrementMoveCount();
	return true;
}

const ChessPiece &ChessBoard::GetPiece(ChessPieceLocation loc) const
{
	return board[loc.y][loc.x];
}