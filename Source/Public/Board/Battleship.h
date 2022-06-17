#pragma once
class BattleShip
{
public:
	BattleShip(char ShipType, int Length);
	BattleShip() = delete;

	[[nodiscard]] char GetType() const;
	[[nodiscard]] int GetSize() const;

private:
	char m_Identifier;
	int m_Size;
};