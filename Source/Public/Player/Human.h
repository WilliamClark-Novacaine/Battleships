#pragma once
#include "Player.h"
#include <random>

class Human : public Player
{
public:
	Human(const std::string& PlayerName, int BoardHeight, int BoardWidth);
};