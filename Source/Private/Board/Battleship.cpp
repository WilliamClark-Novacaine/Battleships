#include "Public/Board/Battleship.h"

BattleShip::BattleShip(const char ShipType, const int Length) : m_Identifier(ShipType), m_Size(Length)
{}

char BattleShip::GetType() const
{
	return m_Identifier;
}

int BattleShip::GetSize() const
{
	return m_Size;
}
