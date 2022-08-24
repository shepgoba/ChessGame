#include "ChessBoard.h"

// Return true on success
bool ChessBoard::MovePiece(ChessPieceLocation from, ChessPieceLocation to)
{	ChessPiece &pieceTo = m_board[to.y][to.x];
	const ChessPiece &pieceFrom = m_board[from.y][from.x];
	
	if (!pieceFrom.IsValid())
		return false;

	m_board[to.y][to.x] = pieceFrom;
	m_board[from.y][from.x] = ChessPiece(PlayerNone, PieceTypeNone);

	pieceTo.IncrementMoveCount();
	return true;
}

const ChessPiece &ChessBoard::GetPiece(ChessPieceLocation loc) const
{
	return m_board[loc.y][loc.x];
}