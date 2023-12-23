#include "ChessBoard.h"

// Return true on success
bool ChessBoard::MovePiece(ChessPieceLocation from, ChessPieceLocation to)
{	
	ChessPiece pieceFrom = GetPiece(from);

	if (!pieceFrom.IsValid())
		return false;

	m_board[from.y][from.x] = ChessPiece(PlayerNone, PieceTypeNone);

	// Move piece
	m_board[to.y][to.x] = pieceFrom;

	// Increment move count internally
	m_board[to.y][to.x].IncrementMoveCount();

	return true;
}

const ChessPiece &ChessBoard::GetPiece(ChessPieceLocation loc) const
{
	return m_board[loc.y][loc.x];
}