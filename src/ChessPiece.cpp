#include "ChessPiece.h"

ChessPiece::ChessPiece(Player player, PieceType type)
	: owner(player), type(type), moveCount(0)
{
}

Player ChessPiece::GetOwner() const
{
	return owner;
}

PieceType ChessPiece::GetType() const
{
	return type;
}

bool ChessPiece::IsValid() const
{
	return (owner != PlayerNone) && (type != PieceTypeNone);
}

bool ChessPiece::IsFriendly(const ChessPiece &other) const
{
	return owner == other.GetOwner();
}

void ChessPiece::IncrementMoveCount()
{
	moveCount++;
}

std::size_t ChessPiece::GetMoveCount() const
{
	return moveCount;
}