#include "Public/AI/AIRandom.h"
#include <string>
#include <iostream>

#include "Public/Core/Utility.h"

AIRandom::AIRandom(const std::string& PlayerName, const int BoardHeight, const int BoardWidth): AI(PlayerName, BoardHeight, BoardWidth){}

void AIRandom::Attack(Board& OpponentBoard, Player& Opponent, const std::string& OpponentName, std::map<char, int>& OpponentShips)
{
	int Row, Col;
	char Element;
	do
	{
		do
		{
			srand(static_cast<unsigned int>(time(nullptr)));
			const int Index = rand() % m_Coords.size();
			Row = m_Coords[Index].first;
			Col = m_Coords[Index].second;

			m_Coords.erase(m_Coords.begin() + Index); //Remove a Coord that has been generated before
		} while (!OpponentBoard.IsValidCoordinate('V', Row, Col, 1));
		Element = OpponentBoard.GetElement(Row, Col);

		//If element is NOT, a HIT'▓' or a MISS 'Φ'; It must be a Ship
		if(Element != ' ' && Element != static_cast<char>(254) && Element != static_cast<char>(233)) 
		{
			/******************************************************************************/
			/*  Ship Found, Search Next Cell For Rest of Ship and Store For Later Memory  */
			/******************************************************************************/
			// Unused, Was going to be used for a Smart AI Player
			char NextElement;
			if (Col - 1 >= 0) {
				NextElement = OpponentBoard.GetElement(Row, Col - 1);
				if (NextElement != static_cast<char>(254) && NextElement != static_cast<char>(233)) {
					m_ListedCoords.emplace_back(std::make_pair(Row, Col - 1));
				}
			}
			if (Row - 1 >= 0) {
				NextElement = OpponentBoard.GetElement(Row - 1, Col);
				if (NextElement != static_cast<char>(254) && NextElement != static_cast<char>(233)) {
					m_ListedCoords.emplace_back(std::make_pair(Row - 1, Col));
				}
			}
			if (Col + 1 < m_BoardWidth) {
				NextElement = OpponentBoard.GetElement(Row, Col + 1);
				if (NextElement != static_cast<char>(254) && NextElement != static_cast<char>(233)) {
					m_ListedCoords.emplace_back(std::make_pair(Row, Col + 1));
				}
			}
			if (Row + 1 < m_BoardHeight) {
				NextElement = OpponentBoard.GetElement(Row + 1, Col);
				if (NextElement != static_cast<char>(254) && NextElement != static_cast<char>(233)) {
					m_ListedCoords.emplace_back(std::make_pair(Row + 1, Col));
				}
			}
		}
	} while (Element == static_cast<char>(254) || Element == static_cast<char>(233));

	/********************************************************************************/
	/*					Was Shot a Hit Or a Miss? Did it Destroy?					*/
	/********************************************************************************/
	if (Element != ' ')
	{
		UpdateFiringBoard(static_cast<char>(254), Row, Col);
		OpponentBoard.UpdateElement(static_cast<char>(254), Row, Col);
		std::cout << "\t\t\t\t\t" << m_UserName << " Hit " << OpponentName << "'s " << Utility::LookUpTables::ShipTypeString(Element) << "!" << std::endl;
		OpponentShips[Element]--; //Remove a 1 from the length of ship
		if (OpponentShips[Element] == 0) // If length of element ship == 0 the ship is destroyed
		{
			std::cout << "\t\t\t\t\t" << m_UserName << " Destroyed " << OpponentName << "'s " << Utility::LookUpTables::ShipTypeString(Element) << "!" << std::endl;
		}
		std::cout << std::endl;
		Sleep(5000);
		ConsoleUtility::ClearScreen();
	}
	else // Shot Element was Empty, Declare Miss
	{
		UpdateFiringBoard(static_cast<char>(233), Row, Col);
		OpponentBoard.UpdateElement(static_cast<char>(233), Row, Col);
		std::cout << "\t\t\t\t\t" << m_UserName << " Missed " << OpponentName << std::endl;
		Sleep(5000);
		ConsoleUtility::ClearScreen();
	}
}
