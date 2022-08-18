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

	std::size_t moveCount;
public:
	ChessPiece(Player p, PieceType t);

	Player GetOwner() const;
	PieceType GetType() const;

	bool IsValid() const;
	
	void IncrementMoveCount();
	std::size_t GetMoveCount() const;
};

#endif // CHESSPIECE_INCLUDE_H