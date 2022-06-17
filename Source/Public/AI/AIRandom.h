#pragma once
#include "AI.h"
#include "Public/Board/Board.h"
#include <vector>
#include <utility>

class AIRandom : public AI
{
public:
	AIRandom(const std::string& PlayerName, int BoardHeight, int BoardWidth);
	void Attack(Board& OpponentBoard, Player& Opponent, const std::string& OpponentName, std::map<char, int>& OpponentShips) override;
	std::vector<std::pair<int, int>> m_Coords;
	std::vector<std::pair<int, int>> m_ListedCoords;
};