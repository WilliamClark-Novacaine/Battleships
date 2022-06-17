#include "Public/Core/InputValidation.h"

#include <iostream>
#include <map>
#include <sstream>

#include "Public/Core/Utility.h"

char InputValidation::OrientateCoords(const std::string& UserName, const char ShipType, const int ShipSize, int& Row, int& Col, Player& PlayerInst)
{
	char Orientation;
	bool bIsValidCoords;
	do
	{
		Orientation = GetShipOrientation(UserName, ShipType, PlayerInst);
		ConsoleUtility::ClearScreen();
		PlayerInst.GetPlacementBoard().PrintPlacementBoard(UserName + "'s Placement Board");
		bIsValidCoords = InputPlacementCoords(UserName, ShipType, ShipSize, Row, Col);
	} while (!bIsValidCoords);
	return Orientation;
}

char InputValidation::GetShipOrientation(const std::string& UserName, const char ShipType, Player& PlayerInst)
{
	const std::vector<char> GoodValues = { 'h', 'H', 'v', 'V' };
	char Orientation;
	do {
		Orientation = InputOrientation(UserName, ShipType, PlayerInst);
	} while (!IsValidOrientation(GoodValues, Orientation));
	return Orientation;
}

char InputValidation::InputOrientation(const std::string& UserName, const char ShipType, Player& PlayerInst)
{
	std::string InputLine;
	while (true)
	{
		ConsoleUtility::ClearScreen();
		PlayerInst.GetPlacementBoard().PrintPlacementBoard(UserName + "'s Placement Board");
		ConsoleUtility::CursorGotTo(50, 8);
		std::cout << "====================================================" ;
		ConsoleUtility::CursorGotTo(50, 9);
		const std::string ShipString = Utility::LookUpTables::ShipTypeString(ShipType);
		std::cout << UserName << ", do you want to place your " << ShipString;
		ConsoleUtility::CursorGotTo(50, 10);
		std::cout << "Horizontally or Vertically?";
		ConsoleUtility::CursorGotTo(50, 11);
		std::cout << "Enter h for horizontal or v for vertical";
		ConsoleUtility::CursorGotTo(50, 12);
		std::cout << "Your Choice: ";
		ConsoleUtility::CursorGotTo(50, 13);
		std::cout << "====================================================";
		ConsoleUtility::CursorGotTo(63, 12);
		
		std::getline(std::cin, InputLine); // grabs the entire line
		std::stringstream Line2Parse(InputLine);
		std::string Word;
		Line2Parse >> Word;
		if (Line2Parse) { // if I was able to read the word
			std::string WhatIsLeft;
			Line2Parse >> WhatIsLeft;
			if (not Line2Parse) { // if there is nothing left we will fail to read it
				if (Word.size() == 1) {
					return Word.at(0);
				}
			}
		}
		ConsoleUtility::CursorGotTo(52, 14);
		ConsoleUtility::changeColor(12);
		std::cout << "Invalid Orientation";
		ConsoleUtility::changeColor(15);
		Sleep(1000);
	}
}

bool InputValidation::InputPlacementCoords(const std::string& UserName, const char ShipType, const int ShipSize, int& Row, int& Col)
{
	std::string CoordInput;
	bool bIsValidCoords = false;
	int CoordCol = -1; //Init Value to something off Grid, as we loop until we gain a valid Column Coord

	const std::string ShipString = Utility::LookUpTables::ShipTypeString(ShipType);
	// Get Coordinate
	ConsoleUtility::CursorGotTo(50, 8);
	std::cout << "====================================================";
	ConsoleUtility::CursorGotTo(50, 9);
	std::cout << UserName << ", Where should " << ShipString << " be placed?";
	ConsoleUtility::CursorGotTo(50, 10);
	std::cout << "Length of " << ShipString << "= " << ShipSize << " Squares";
	ConsoleUtility::CursorGotTo(50, 11);
	std::cout << "Please Input in the format [Row][Column] ";
	ConsoleUtility::CursorGotTo(50, 12);
	std::cout << "Input: ";
	ConsoleUtility::CursorGotTo(50, 13);
	std::cout << "====================================================";
	ConsoleUtility::CursorGotTo(57, 12);
	std::getline(std::cin, CoordInput); //Grabs entire Line
	if (CoordInput.size() == 2)
	{
		// Check if the first element of an the input string is either a char 'A'-'J' || 'a'-'J'
		if ((CoordInput[0] >= static_cast<char>(65) && CoordInput[0] <= static_cast<char>(74)) /*UpperCase*/ ||
			(CoordInput[0] >= static_cast<char>(97) && CoordInput[0] <= static_cast<char>(106)) /*LowerCase*/)
		{
			if (CoordInput[1] == '1' || CoordInput[1] == '2' || CoordInput[1] == '3' || CoordInput[1] == '4' || CoordInput[1] == '5' || CoordInput[1] == '6' || CoordInput[1] == '7' || CoordInput[1] == '8' || CoordInput[1] == '9' || CoordInput[1] == '0')
			{
				// Convert second element Char to Int. char '0' - '9' ==> int 0 - 9
				try // std::Stoi() Exception Handling
				{
					CoordCol = std::stoi(&CoordInput[1]);
					bIsValidCoords = true;
				}
				catch (std::invalid_argument&)
				{
					//std::cout << "Stoi() Invalid Arg \n";
				}
				catch (std::out_of_range&)
				{
					//std::cout << "Stoi() Out of Range \n";
				}
			}
			else
			{
				ConsoleUtility::CursorGotTo(57, 14);
				ConsoleUtility::changeColor(12);
				std::cout << "Invalid Col Input \n";
				ConsoleUtility::changeColor(15);
			}
		}
		else
		{
			ConsoleUtility::CursorGotTo(57, 14);
			ConsoleUtility::changeColor(12);
			std::cout << "Invalid Row Input \n";
			ConsoleUtility::changeColor(15);
		}
	}
	else
	{
		ConsoleUtility::CursorGotTo(57, 14);
		ConsoleUtility::changeColor(12);
		if (CoordInput.size() > 2)
		{
			std::cout << "Input is too large";
		}
		else
		{
			std::cout << " than or shorter than 2 characters";
		}
		ConsoleUtility::changeColor(15);
	}
	Sleep(1000);

	//Has Valid Coordinates, Pass back Row & Col by reference
	//Generate Lookup Table
	if (bIsValidCoords)
	{
		Row = Utility::LookUpTables::RowCoordLUT.at(CoordInput[0]);
		Col = CoordCol;
	}
	return bIsValidCoords;
}

bool InputValidation::IsValidPlacement(const char Orientation, const int Row, const int Col, const int ShipSize, const Board& UserBoard)
{
	if (UserBoard.IsValidCoordinate(Orientation, Row, Col, ShipSize) && UserBoard.IsPlacementAvailable(Orientation, Row, Col, ShipSize))
	{
		return true;
	}
	ConsoleUtility::CursorGotTo(57, 14);
	ConsoleUtility::changeColor(12);
	std::cout << "Invalid Placement";
	ConsoleUtility::changeColor(15);
	Sleep(1000);
	return false;
}

bool InputValidation::IsValidOrientation(const std::vector<char>& Values, const char Value)
{
	if(std::find(Values.begin(), Values.end(), Value) != Values.end())
	{
		return true;
	}
	ConsoleUtility::CursorGotTo(52, 14);
	ConsoleUtility::changeColor(12);
	std::cout << "Invalid Orientation\n";
	ConsoleUtility::CursorGotTo(52, 15);
	Sleep(1000);
	return false;
}
