#ifndef CHESSBOARD_INCLUDE_H
#define CHESSBOARD_INCLUDE_H
#include "ChessPiece.h"
#include <cassert>
#include <cstddef>

// Described with the top left tile as the origin,
// and the x-axis increasing as it moves to the right,
// and the y-axis increasing as it moves down
struct ChessPieceLocation {
	unsigned int x;
	unsigned int y;

	ChessPieceLocation(unsigned int x, unsigned int y) : x(x), y(y) {
		assert(x >= 0 && x <= 7);
		assert(y >= 0 && y <= 7);
	}
};

class ChessBoard {
private:
	static constexpr std::size_t BOARD_WIDTH = 8;
	static constexpr std::size_t BOARD_HEIGHT = 8;

	ChessPiece board[BOARD_WIDTH][BOARD_HEIGHT] = {
		{
			ChessPiece(PlayerBlack, PieceTypeRook),
			ChessPiece(PlayerBlack, PieceTypeKnight),
			ChessPiece(PlayerBlack, PieceTypeBishop),
			ChessPiece(PlayerBlack, PieceTypeQueen),
			ChessPiece(PlayerBlack, PieceTypeKing),
			ChessPiece(PlayerBlack, PieceTypeBishop),
			ChessPiece(PlayerBlack, PieceTypeKnight),
			ChessPiece(PlayerBlack, PieceTypeRook)
		},
		{
			ChessPiece(PlayerBlack, PieceTypePawn),
			ChessPiece(PlayerBlack, PieceTypePawn),
			ChessPiece(PlayerBlack, PieceTypePawn),
			ChessPiece(PlayerBlack, PieceTypePawn),
			ChessPiece(PlayerBlack, PieceTypePawn),
			ChessPiece(PlayerBlack, PieceTypePawn),
			ChessPiece(PlayerBlack, PieceTypePawn),
			ChessPiece(PlayerBlack, PieceTypePawn)
		},
		{
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone)
		},
		{
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone)
		},
		{
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone)
		},
		{
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone)
		},
		{
			ChessPiece(PlayerWhite, PieceTypePawn),
			ChessPiece(PlayerWhite, PieceTypePawn),
			ChessPiece(PlayerWhite, PieceTypePawn),
			ChessPiece(PlayerWhite, PieceTypePawn),
			ChessPiece(PlayerWhite, PieceTypePawn),
			ChessPiece(PlayerWhite, PieceTypePawn),
			ChessPiece(PlayerWhite, PieceTypePawn),
			ChessPiece(PlayerWhite, PieceTypePawn)
		},
		{
			ChessPiece(PlayerWhite, PieceTypeRook),
			ChessPiece(PlayerWhite, PieceTypeKnight),
			ChessPiece(PlayerWhite, PieceTypeBishop),
			ChessPiece(PlayerWhite, PieceTypeQueen),
			ChessPiece(PlayerWhite, PieceTypeKing),
			ChessPiece(PlayerWhite, PieceTypeBishop),
			ChessPiece(PlayerWhite, PieceTypeKnight),
			ChessPiece(PlayerWhite, PieceTypeRook)
		}
	};
public:
	bool MovePiece(ChessPieceLocation from, ChessPieceLocation to);
	const ChessPiece &GetPiece(ChessPieceLocation loc) const;

	unsigned int GetWidth() const { return BOARD_WIDTH; }
	unsigned int GetHeight() const { return BOARD_HEIGHT; }
};

#endif // CHESSBOARD_INCLUDE_H