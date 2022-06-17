#include <iostream>
#include "Public/Player/Player.h"

#include "Public/Core/Utility.h"

// TF: Default Parameter
// TF: Constructor
Player::Player(std::string PlayerName, const int BoardHeight = 10, const int BoardWidth = 10) : m_PlacementBoard(Board(BoardHeight, BoardWidth)), m_FiringBoard(Board(BoardHeight, BoardWidth)), m_BoardHeight(BoardHeight), m_BoardWidth(BoardWidth), m_UserName(std::move(PlayerName))
{}

// TF: Destructor
Player::~Player() = default;

std::string Player::GetName() const
{
	return m_UserName;
}

Board& Player::GetPlacementBoard()
{
	return m_PlacementBoard;
}

// TF: Constant
int Player::RandomGenSelectRow(char Orientation, int ShipLength) const
{
	// TF: Variable Type
	int Num;
	if (Orientation == 'H') // TF: Relational Operator
	{
		// TF: Arithmetic Operator
		Num = rand() % m_BoardHeight;
	}
	else
	{
		Num = rand() % (m_BoardHeight - ShipLength + 1);
	}
	return Num;
}

int Player::RandomGenSelectCol(char Orientation, int ShipLength) const
{
	int Num;
	if (Orientation == 'H')
	{
		Num = rand() % (m_BoardWidth - ShipLength + 1);
	}
	else
	{
		Num = rand() % m_BoardWidth;
	}
	return Num;
}

std::map<char, int>& Player::GetStoredShips()
{
	return m_StoreShips;
}

void Player::PlaceShip(const BattleShip Ship, const char Orientation, const int Row, const int Col)
{
	// TF: Iteration Structure
	for (int i = 0; i < Ship.GetSize(); ++i)
	{
		// TF: Conditional Statement
		if (Orientation == 'v' || Orientation == 'V')
		{
			m_PlacementBoard.UpdateElement(Ship.GetType(), Row + i, Col);
		}
		else
		{
			m_PlacementBoard.UpdateElement(Ship.GetType(), Row, Col + i);
		}
	}
}

void Player::Attack(Board& OpponentBoard, Player& Opponent, const std::string& OpponentName, std::map<char, int>& OpponentShips)
{
	int Row, Col;
	char Element;
	do 
	{
		do 
		{
			GetTarget(Row, Col);
			ConsoleUtility::ClearScreen();
			DisplayBoards(false);
			if (GameControl::Debug::bDebugMode)
			{
				Opponent.DisplayBoards(true);
			}
		} while (!OpponentBoard.IsValidCoordinate('V', Row, Col, 1));
		Element = OpponentBoard.GetElement(Row, Col);
		if (Element == static_cast<char>(254) || Element == static_cast<char>(233))
		{
			ConsoleUtility::changeColor(12);
			std::cout << "\t\t\t\t\tYou Have Already Shot Here!" << std::endl;
			ConsoleUtility::changeColor(15);
			Sleep(2000);
			ConsoleUtility::ClearScreen();
			DisplayBoards(false);
			if (GameControl::Debug::bDebugMode)
			{
				Opponent.DisplayBoards(true);
			}
		}
	} while (Element == static_cast<char>(254) || Element == static_cast<char>(233));
	// static_cast<char>(254) == HIT == '▓'
	// static_cast<char>(233) == MISS == 'Φ'
	if (Element != ' ')
	{
		UpdateFiringBoard(static_cast<char>(254), Row, Col);
		OpponentBoard.UpdateElement(static_cast<char>(254), Row, Col);
		std::cout << "\t\t\t\t\t" << m_UserName << " HIT " << OpponentName << "'s" << Utility::LookUpTables::ShipTypeString(Element) << "!" << std::endl;
		OpponentShips[Element]--;
		if (OpponentShips[Element] == 0)
		{
			std::cout << "\t\t\t\t\t" << m_UserName << " destroyed " << OpponentName << "'s " << Utility::LookUpTables::ShipTypeString(Element) << "!" << std::endl;
			OpponentShips.erase(Element);
		}
		std::cout << std::endl;
		Sleep(5000);
		ConsoleUtility::ClearScreen();
	}
	else
	{
		//if it is square is empty, update element with a miss
		UpdateFiringBoard(static_cast<char>(233), Row, Col);
		OpponentBoard.UpdateElement(static_cast<char>(233), Row, Col);
		std::cout << "\t\t\t\t\t" << m_UserName << " Missed " << OpponentName << std::endl << std::endl;
		Sleep(5000);
		ConsoleUtility::ClearScreen();
	}
}

void Player::AddShip(const BattleShip Ship)
{
	m_StoreShips.insert({ Ship.GetType(), Ship.GetSize() });
}

void Player::DisplayBoards(bool bIsAI) const
{
	if (bIsAI)
	{
		std::string BoardName = m_UserName + "'s Placement Board";
		m_PlacementBoard.PrintPlacementBoard(BoardName);
		BoardName = m_UserName + "'s Firing Board";
		m_FiringBoard.PrintAIFiringBoard(BoardName);
	}
	else
	{
		std::string BoardName = m_UserName + "'s Placement Board";
		m_PlacementBoard.PrintPlacementBoard(BoardName);
		BoardName = m_UserName + "'s Firing Board";
		m_FiringBoard.PrintFiringBoard(BoardName);
	}
}

void Player::UpdateFiringBoard(const char Symbol, const int Row, const int Col)
{
	m_FiringBoard.UpdateElement(Symbol, Row, Col);
}

void Player::GetTarget(int& Row, int& Col) const
{
	std::string CoordInput;
	bool bIsValidCoords = false;
	int CoordCol = -1;
	// Get Coordinate
	std::cout << "\t\t\t   " << m_UserName << ", where would you like to fire?" << std::endl;
	std::cout << "\t\t\t   " << "Enter your attack coordinate in the form row col: ";
	std::getline(std::cin, CoordInput); //Grabs entire Line
	if (CoordInput.size() == 2)
	{
		// TF: Logical Operator
		// Check if the first element of an the input string is either a char 'A'-'J' || 'a'-'J'
		if ((CoordInput[0] >= static_cast<char>(65) && CoordInput[0] <= static_cast<char>(74)) /*UpperCase*/ ||
			(CoordInput[0] >= static_cast<char>(97) && CoordInput[0] <= static_cast<char>(106)) /*LowerCase*/)
		{
			// Convert second element Char to Int. char '0' - '9' ==> int 0 - 9
			if (CoordInput[1] == '1' || CoordInput[1] == '2' || CoordInput[1] == '3'|| CoordInput[1] == '4' || CoordInput[1] == '5' || CoordInput[1] == '6' || CoordInput[1] == '7' || CoordInput[1] == '8' || CoordInput[1] == '9' || CoordInput[1] == '0')
			{
				try // std::Stoi() Exception Handling
				{
					CoordCol = std::stoi(&CoordInput[1]);
					bIsValidCoords = true;
				}
				catch (std::invalid_argument&)
				{
					//std::cout << "\n Stoi() Invalid Arg";
					ConsoleUtility::changeColor(12);
					std::cout << "\n \t\t\t\tInvalid Column Input: Please Enter a Valid Column";
					ConsoleUtility::changeColor(15);
					Sleep(2000);
					ConsoleUtility::ClearScreen();

				}
				catch (std::out_of_range&)
				{
					//std::cout << "\n Stoi() Invalid Arg";
					ConsoleUtility::changeColor(12);
					std::cout << "\n \t\t\t\tInvalid Column Input: Please Enter a Valid Column";
					ConsoleUtility::changeColor(15);
					Sleep(2000);
					ConsoleUtility::ClearScreen();
				}
			}
			else
			{
				ConsoleUtility::changeColor(12);
				std::cout << "\n \t\t\t\tInvalid Column Input: Please Enter a Valid Column";
				ConsoleUtility::changeColor(15);
				Sleep(2000);
				ConsoleUtility::ClearScreen();
			}
		}
		else
		{
			ConsoleUtility::changeColor(12);
			std::cout << "\n \t\t\t\tInvalid Row Input:  Please Enter a Valid Row";
			ConsoleUtility::changeColor(15);
			Sleep(2000);
			ConsoleUtility::ClearScreen();
			DisplayBoards(false);
		}
	}
	else
	{
		if (CoordInput.size() > 2)
		{
			ConsoleUtility::changeColor(12);
			std::cout << "\n \t\t\t\tInput is too large: Please input two characters.";
			ConsoleUtility::changeColor(15);
		}
		else
		{
			ConsoleUtility::changeColor(12);
			std::cout << "\n \t\t\t\tInput is too small: Please input two characters.";
			ConsoleUtility::changeColor(15);
		}
		Sleep(2000);
		ConsoleUtility::ClearScreen();
	}
	//Has Valid Coordinates, Pass back Row & Col by reference
	if(bIsValidCoords)
	{
		ConsoleUtility::ClearScreen();
		Row = Utility::LookUpTables::RowCoordLUT.at(CoordInput[0]);
		Col = CoordCol;
	}
}