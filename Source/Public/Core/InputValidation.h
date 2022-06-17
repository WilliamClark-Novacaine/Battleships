#pragma once
#include <string>

#include "Public/Board/Board.h"
#include "Public/Player/Player.h"

namespace InputValidation
{
	char OrientateCoords(const std::string& UserName, char ShipType, int ShipSize, int& Row, int& Col, Player& PlayerInst);
	char GetShipOrientation(const std::string& UserName, char ShipType, Player& PlayerInst);
	char InputOrientation(const std::string& UserName, char ShipType, Player& PlayerInst);
	bool InputPlacementCoords(const std::string& UserName, char ShipType, int ShipSize, int& Row, int& Col);
	bool IsValidPlacement(char Orientation, int Row, int Col, int ShipSize, const Board& UserBoard);
	bool IsValidOrientation(const std::vector<char>& Values, char Value);
}
