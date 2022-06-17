#pragma once
#include <memory>

#include "Public/Board/Battleship.h"
#include "Public/Player/Player.h"
#include "Public/AI/AI.h"

void CreateHumanPlayer(const int& BoardHeight, const int& BoardWidth, const std::vector<BattleShip>& Ships, std::vector<std::unique_ptr<Player>>& Players);
void CreateAIRandomPlayer(const int& BoardHeight, const int& BoardWidth, const std::vector<BattleShip>& Ships, std::vector<std::unique_ptr<Player>>& Players);
bool ShouldGenAutoBoard();