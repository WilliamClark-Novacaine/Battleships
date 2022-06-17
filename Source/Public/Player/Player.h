#pragma once
#include <map>
#include <string>
#include "Public/Board/Board.h"
#include "Public/Board/Battleship.h"
class Player // TF: Class
{
public: // TF: Access Specifier
	Player(std::string PlayerName, int BoardHeight, int BoardWidth);
	virtual ~Player();
	Player() = delete; //remove standard constructor
	[[nodiscard]] std::string GetName() const;
	[[nodiscard]] Board& GetPlacementBoard();
	[[nodiscard]] int RandomGenSelectRow(char Orientation, int ShipLength) const;
	[[nodiscard]] int RandomGenSelectCol(char Orientation, int ShipLength) const;
	std::map<char, int>& GetStoredShips();
	void PlaceShip(BattleShip Ship, char Orientation, int Row, int Col);
	virtual void Attack(Board& OpponentBoard, Player& Opponent, const std::string& OpponentName, std::map<char, int>& OpponentShips);
	void AddShip(BattleShip Ship);
	void DisplayBoards(bool bIsAI) const;
	void UpdateFiringBoard(char Symbol, int Row, int Col);
	Board m_PlacementBoard;
	Board m_FiringBoard;
protected: //Access Only to Children of class
	int m_BoardHeight;
	int m_BoardWidth;
	std::string m_UserName;
private:
	void GetTarget(int& Row, int& Col) const;
	std::map<char, int> m_StoreShips;
};
