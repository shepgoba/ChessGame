#include "ChessBoard.h"

bool ChessBoard::MovePiece(ChessPieceLocation from, ChessPieceLocation to)
{
	ChessPiece &pieceFrom = board[from.y][from.x];
	ChessPiece &pieceTo = board[to.y][to.x];

	if (!pieceFrom.IsValid())
		return false;

	board[to.y][to.x] = pieceFrom;
	board[from.y][from.x] = ChessPiece(PlayerNone, PieceTypeNone);
	
	return true;
}

const ChessPiece &ChessBoard::GetPiece(ChessPieceLocation loc) const
{
	return board[loc.y][loc.x];
}