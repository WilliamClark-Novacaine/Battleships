#pragma once
#include <vector>
#include <utility>
#include <random>
#include "Public/Player/Player.h"
#include "Public/Board/Board.h"

class AI : public Player
{
public:
	AI(const std::string& PlayerName, int BoardHeight, int BoardWidth);
	std::vector<std::pair<int, int>> m_Pair;

	static char SelectOrientation();
	[[nodiscard]] int SelectRow(char Orientation, int ShipLength) const;
	[[nodiscard]] int SelectCol(char Orientation, int ShipLength) const;
};
