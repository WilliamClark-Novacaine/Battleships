/*****************************************************************//**
 * \file   Board.h
 * \brief  Board class definition, prints grid and stores grid values
 * 
 * \author William Clark
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <vector>

//EXTENDED UNICODE ASCII CHARS
//Was MACRO Hence Caps
constexpr char BORDER_RIGHT_TBAR = static_cast<char>(185);					   //'╣'
constexpr char BORDER_VERTICAL = static_cast<char>(186);					   //'║'
constexpr char BORDER_TOP_RIGHT_CORNER = static_cast<char>(187);			   //'╗'
constexpr char BORDER_BOTTOM_RIGHT_CORNER = static_cast<char>(188);			   //'╝'
constexpr char BORDER_BOTTOM_LEFT_CORNER = static_cast<char>(200);			   //'╚'
constexpr char BORDER_TOP_LEFT_CORNER = static_cast<char>(201);				   //'╔'
constexpr char BORDER_BOTTOM_TBAR = static_cast<char>(202);					   //'╩'
constexpr char BORDER_TOP_TBAR = static_cast<char>(203);					   //'╦'
constexpr char BORDER_LEFT_TBAR = static_cast<char>(204);					   //'╠'
constexpr char BORDER_HORIZONTAL = static_cast<char>(205);					   //'═'
constexpr char BORDER_INTERSECTION = static_cast<char>(206);				   //'╬'

class Board
{
public:
	Board(int BoardHeight, int BoardWidth); //Constructor
	Board(const Board& OldBoard); // TF: Copy Constructor
	~Board();
	void PrintPlacementBoard(const std::string& Str) const;
	void PrintFiringBoard(const std::string& Str) const;
	void PrintAIFiringBoard(const std::string& Str) const;
	void UpdateElement(char Element, int Row, int Col);
	[[nodiscard]] char GetElement(int Row, int Col) const;
	[[nodiscard]] bool IsValidCoordinate(char Orientation, int Row, int Col, int Length) const;
	[[nodiscard]] bool IsPlacementAvailable(char Orientation, int Row, int Col, int Length) const;
	
	int m_Height{}, m_Width{};
private:
	std::vector<std::vector<char>> m_GameBoard; //Dynamic Array (Not to be confused with Physics Vector)

	void PrintLine(char First, char Middle, char Last) const;
	void PrintFiringBoardLine(char First, char Middle, char Last) const;
	void PrintAIFiringBoardLine(char First, char Middle, char Last) const;
};

