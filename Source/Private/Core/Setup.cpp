#include "Public/Core/Setup.h"

#include <conio.h>

#include "Public/Player/Human.h"
#include "Public/Core/InputValidation.h"
#include <iostream>

#include "Public/AI/AIRandom.h"
#include "Public/Core/Utility.h"


void CreateHumanPlayer(const int& BoardHeight, const int& BoardWidth, const std::vector<BattleShip>& Ships, std::vector<std::unique_ptr<Player>>& Players)
{
	// Defines what 'Player Number' the user is.
	int PlayerNum;
	if (Players.empty()) //Vector array is empty, means they must be Player1, Else they must be Player2
	{
		PlayerNum = 1; 
	}
	else
	{
		PlayerNum = 2;
	}

	bool ValidName = false;
	std::string UserNameInput;
	do 
	{
		ConsoleUtility::CursorGotTo(20, 12);
		std::cout << "Player " << PlayerNum << " please enter your name: ";
		ConsoleUtility::CursorGotTo(20, 13);
		std::cout << "Username: ";
		std::getline(std::cin, UserNameInput);
		if (UserNameInput.size() >= 3)
		{
			ValidName = true;
		}
	} while (!ValidName);

	const std::string Username = "Admiral " + UserNameInput;
	ConsoleUtility::ClearScreen();
	Human PlayerInst(Username, BoardHeight, BoardWidth); // TF: Class Instance


	const bool bUseAutoSetup = ShouldGenAutoBoard();

	if (!bUseAutoSetup) // Do Manual Setup
	{
		int Col;
		int Row;
		PlayerInst.GetPlacementBoard().PrintPlacementBoard(Username + "'s Placement Board");

		/************************************************************************/
		/*                          Manual Board Setup                          */
		/************************************************************************/
		for (const auto& Ship : Ships)
		{
			char Orientation;
			do
			{
				Orientation = InputValidation::OrientateCoords(Username, Ship.GetType(), Ship.GetSize(), Row, Col, PlayerInst);
			} while (!InputValidation::IsValidPlacement(Orientation, Row, Col, Ship.GetSize(), PlayerInst.GetPlacementBoard()));
			// Place Ship On Board
			PlayerInst.PlaceShip(Ship, Orientation, Row, Col);
			// Add Ship to Map
			PlayerInst.AddShip(Ship);
			// Print Board with added Ship
			ConsoleUtility::ClearScreen();
			PlayerInst.GetPlacementBoard().PrintPlacementBoard(Username + "'s Placement Board");
		}
	}
	else
	{
		/************************************************************************/
		/*                        Automatic Board Setup                         */
		/************************************************************************/
		char Orientation;
		int Row, Col;
		for (auto& Ship : Ships)
		{
			do
			{
				Orientation = AIRandom::SelectOrientation();
				Row = PlayerInst.RandomGenSelectRow(Orientation, Ship.GetSize());
				Col = PlayerInst.RandomGenSelectCol(Orientation, Ship.GetSize());
			} while (!InputValidation::IsValidPlacement(Orientation, Row, Col, Ship.GetSize(), PlayerInst.GetPlacementBoard()));
			PlayerInst.PlaceShip(Ship, Orientation, Row, Col);
			PlayerInst.AddShip(Ship);
			if (GameControl::Debug::bDebugMode)
			{
				PlayerInst.GetPlacementBoard().PrintPlacementBoard(Username + "'s Placement Board");
			}
		}
	}
	//Push Back Player Instance to Players Array
	Players.push_back(std::make_unique<Player>(PlayerInst));
}

void CreateAIRandomPlayer(const int& BoardHeight, const int& BoardWidth, const std::vector<BattleShip>& Ships, std::vector<std::unique_ptr<Player>>& Players)
{
	int PlayerNum;
	if (Players.empty())
	{
		PlayerNum = 1;
	}
	else
	{
		PlayerNum = 2;
	}
	const std::string AIName = "HAL(CPU)";
	char Orientation;
	int Row, Col;

	AIRandom AIPlayer(AIName, BoardHeight, BoardWidth);
	//Generate All possible Coordinates for AI to Shoot.
	for (int X = 0; X < BoardHeight; X++)
	{
		for (int Y = 0; Y < BoardWidth; Y++)
		{
			AIPlayer.m_Coords.emplace_back(std::make_pair(X, Y));
		}
	}

	for (auto& Ship : Ships)
	{
		do
		{
			Orientation = AIRandom::SelectOrientation();
			Row = AIPlayer.SelectRow(Orientation, Ship.GetSize());
			Col = AIPlayer.SelectCol(Orientation, Ship.GetSize());
		} while (!InputValidation::IsValidPlacement(Orientation, Row, Col, Ship.GetSize(), AIPlayer.GetPlacementBoard()));
		AIPlayer.PlaceShip(Ship, Orientation, Row, Col);
		AIPlayer.AddShip(Ship);
		if(GameControl::Debug::bDebugMode)
		{
			AIPlayer.GetPlacementBoard().PrintPlacementBoard(AIName + "'s Placement Board");
		}
	}
	Players.push_back(std::make_unique<AIRandom>(AIPlayer));
}

bool ShouldGenAutoBoard()
{
	// Ask User if they want Automatic or Manual Board Setup
	int ColorSet[] = { 7,7,7,7,7 };
	int MenuCounter = 2;
	ConsoleUtility::CursorGotTo(20, 11);
	std::cout << "Arrow Keys to Navigate";
	ConsoleUtility::CursorGotTo(20, 12);
	std::cout << "How would you like to create your board?";
	for (int i = 0;;)
	{
		ConsoleUtility::CursorGotTo(35, 13);
		ConsoleUtility::changeColor(ColorSet[0]);
		std::cout << "Manual?";

		ConsoleUtility::CursorGotTo(35, 14);
		ConsoleUtility::changeColor(ColorSet[1]);
		std::cout << "Automatic?";

		const char InputKey = _getch();

		if (InputKey == 72 && MenuCounter == 2)
		{
			MenuCounter--;
		}
		if (InputKey == 80 && MenuCounter == 1)
		{
			MenuCounter++;
		}
		if (InputKey == '\r')//carriage return
		{
			if (MenuCounter == 1)
			{
				// if enter is click and highlight is on 1 the program will run the code here
				ConsoleUtility::changeColor(15);
				return false;
			}
			if (MenuCounter == 2)
			{
				ConsoleUtility::changeColor(15);
				return true;
			}
		}

		ColorSet[0] = 7;
		ColorSet[1] = 7;

		if (MenuCounter == 1)
		{
			ColorSet[0] = 12;
		}
		if (MenuCounter == 2)
		{
			ColorSet[1] = 12;
		}
	}
}


