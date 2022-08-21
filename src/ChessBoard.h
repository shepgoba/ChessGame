#ifndef CHESSBOARD_INCLUDE_H
#define CHESSBOARD_INCLUDE_H
#include "ChessPiece.h"
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <optional>

// Described with the top left tile as the origin,
// and the x-axis increasing as it moves to the right,
// and the y-axis increasing as it moves down
struct ChessPieceLocation {
	std::size_t x;
	std::size_t y;

	ChessPieceLocation(std::size_t x, std::size_t y) : x(x), y(y) {
		assert(CanCreateLocation(x, y) && "Invalid location");
	}

	ChessPieceLocation operator+(const ChessPieceLocation &other) const {
		return ChessPieceLocation(x + other.x, y + other.y);
	}

	ChessPieceLocation operator-(const ChessPieceLocation &other) const {
		return ChessPieceLocation(x - other.x, y - other.y);
	}

	bool operator==(const ChessPieceLocation &other) const {
		return (x == other.x) && (y == other.y);
	}
	
	constexpr static bool CanCreateLocation(std::size_t x, std::size_t y) {
		return (x <= 7) && (y <= 7);
	}

	static std::optional<ChessPieceLocation> CreateLocationIfPossible(std::size_t x, std::size_t y) {
		if (CanCreateLocation(x, y))
			return ChessPieceLocation(x, y);
		
		return std::nullopt;
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

	std::size_t GetWidth() const { return BOARD_WIDTH; }
	std::size_t GetHeight() const { return BOARD_HEIGHT; }
};

#endif // CHESSBOARD_INCLUDE_H