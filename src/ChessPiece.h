#ifndef CHESSPIECE_INCLUDE_H
#define CHESSPIECE_INCLUDE_H
#include <cstddef>

enum Player : std::size_t {
	PlayerWhite = 0,
	PlayerBlack = 1,
	PlayerNone = 2
};

enum PieceType : std::size_t {
	PieceTypePawn = 0,
	PieceTypeRook = 1,
	PieceTypeKnight = 2,
	PieceTypeBishop = 3,
	PieceTypeQueen = 4,
	PieceTypeKing = 5,
	PieceTypeNone = 6
};

class ChessPiece {
private:
	Player owner;
	PieceType type;
public:
	ChessPiece(Player p, PieceType t) : owner(p), type(t) {}

	Player GetOwner() const {
		return owner;
	}

	PieceType GetType() const {
		return type;
	}

	bool IsValid() const {
		return (owner != PlayerNone) && (type != PieceTypeNone);
	}
};

#endif // CHESSPIECE_INCLUDE_H