#include <iostream>
#include "Public/Board/Board.h"
#include "Public/Core/Utility.h"

Board::Board(const int BoardHeight = 10, const int BoardWidth = 10) : m_Height(BoardHeight), m_Width(BoardWidth), m_GameBoard(BoardHeight, std::vector<char>(BoardWidth, ' '))
{}

Board::Board(const Board& OldBoard) = default; // TF: Copy Constructor

Board::~Board() = default;

// TF: Reference
void Board::PrintPlacementBoard(const std::string& Str) const
{
	ConsoleUtility::changeColor(15);
	std::cout << "\t   " << Str << "\n";
	std::cout << "        ";
	for (int i = 0; i < m_Width; ++i) //Column Labels
	{
		std::cout << i << "   ";
	}

	PrintLine(BORDER_TOP_LEFT_CORNER, BORDER_TOP_TBAR, BORDER_TOP_RIGHT_CORNER); //Top Boarder Line
	std::cout << std::endl;

	for (int i = 0; i < m_Height; ++i) {
		std::cout << "   " << static_cast<char>(65 + i) << "  " << BORDER_VERTICAL << " ";
		for (int j = 0; j < m_Width; ++j)
		{
			if (m_GameBoard.at(i).at(j) == static_cast<char>(254))
			{
				ConsoleUtility::changeColor(12);
			}
			else if (m_GameBoard.at(i).at(j) == static_cast<char>(233))
			{
				ConsoleUtility::changeColor(8);
			}
			else if (m_GameBoard.at(i).at(j) != ' ')
			{
				ConsoleUtility::changeColor(31);
			}
			std::cout << m_GameBoard.at(i).at(j);
			ConsoleUtility::changeColor(15);
			std::cout << " " << BORDER_VERTICAL << " ";
		}
		if (i == m_Height - 1)
		{
			PrintLine(BORDER_BOTTOM_LEFT_CORNER, BORDER_BOTTOM_TBAR, BORDER_BOTTOM_RIGHT_CORNER);
		}
		else
		{
			PrintLine(BORDER_LEFT_TBAR, BORDER_INTERSECTION, BORDER_RIGHT_TBAR);
		}
		std::cout << std::endl;
	}
}

void Board::PrintFiringBoard(const std::string& Str) const
{
	ConsoleUtility::CursorGotTo(60, 0);
	std::cout << "\t   " << Str << "\n";
	ConsoleUtility::CursorGotTo(55, ConsoleUtility::CursorPos.Y +1);
	std::cout << "        ";
	for (int i = 0; i < m_Width; ++i) //Column Labels
	{
		std::cout << i << "   ";
	}
	PrintFiringBoardLine(BORDER_TOP_LEFT_CORNER, BORDER_TOP_TBAR, BORDER_TOP_RIGHT_CORNER); //Top Boarder Line
	std::cout << "\n";
	for (int i = 0; i < m_Height; ++i) {
		ConsoleUtility::CursorGotTo(55, ConsoleUtility::CursorPos.Y +1);
		std::cout << "   " << static_cast<char>(65 + i) << "  " << BORDER_VERTICAL << " ";
		for (int j = 0; j < m_Width; ++j)
		{
			if (m_GameBoard.at(i).at(j) == static_cast<char>(254))
			{
				ConsoleUtility::changeColor(12);
			}
			else if (m_GameBoard.at(i).at(j) == static_cast<char>(233))
			{
				ConsoleUtility::changeColor(8);
			}
			else if (m_GameBoard.at(i).at(j) != ' ')
			{
				ConsoleUtility::changeColor(21);
			}
			std::cout << m_GameBoard.at(i).at(j);
			ConsoleUtility::changeColor(15);
			std::cout << " " << BORDER_VERTICAL << " ";
		}
		if (i == m_Height - 1)
		{
			PrintFiringBoardLine(BORDER_BOTTOM_LEFT_CORNER, BORDER_BOTTOM_TBAR, BORDER_BOTTOM_RIGHT_CORNER);
		}
		else
		{
			PrintFiringBoardLine(BORDER_LEFT_TBAR, BORDER_INTERSECTION, BORDER_RIGHT_TBAR);
		}
		std::cout << std::endl;
	}
}

void Board::PrintAIFiringBoard(const std::string& Str) const
{
	ConsoleUtility::CursorGotTo(60, 23);
	std::cout << "\t   " << Str << "\n";
	ConsoleUtility::CursorGotTo(55, ConsoleUtility::CursorPos.Y + 1);
	std::cout << "        ";
	for (int i = 0; i < m_Width; ++i) //Column Labels
	{
		std::cout << i << "   ";
	}
	PrintFiringBoardLine(BORDER_TOP_LEFT_CORNER, BORDER_TOP_TBAR, BORDER_TOP_RIGHT_CORNER); //Top Boarder Line
	std::cout << "\n";
	for (int i = 0; i < m_Height; ++i) {
		ConsoleUtility::CursorGotTo(55, ConsoleUtility::CursorPos.Y + 1);
		std::cout << "   " << static_cast<char>(65 + i) << "  " << BORDER_VERTICAL << " ";
		for (int j = 0; j < m_Width; ++j)
		{
			if (m_GameBoard.at(i).at(j) == static_cast<char>(254))
			{
				ConsoleUtility::changeColor(12);
			}
			else if (m_GameBoard.at(i).at(j) == static_cast<char>(233))
			{
				ConsoleUtility::changeColor(8);
			}
			else if (m_GameBoard.at(i).at(j) != ' ')
			{
				ConsoleUtility::changeColor(31);
			}
			std::cout << m_GameBoard.at(i).at(j);
			ConsoleUtility::changeColor(15);
			std::cout << " " << BORDER_VERTICAL << " ";
		}
		if (i == m_Height - 1)
		{
			PrintAIFiringBoardLine(BORDER_BOTTOM_LEFT_CORNER, BORDER_BOTTOM_TBAR, BORDER_BOTTOM_RIGHT_CORNER);
		}
		else
		{
			PrintAIFiringBoardLine(BORDER_LEFT_TBAR, BORDER_INTERSECTION, BORDER_RIGHT_TBAR);
		}
		std::cout << std::endl;
	}
}

void Board::PrintLine(char First, char Middle, char Last) const
{
	std::cout << "\n      " << First;
	for (int i = 0; i < m_Height - 1; i++) {
		std::cout << BORDER_HORIZONTAL << BORDER_HORIZONTAL << BORDER_HORIZONTAL << Middle;
	}
	std::cout << BORDER_HORIZONTAL << BORDER_HORIZONTAL << BORDER_HORIZONTAL << Last;
}

void Board::PrintFiringBoardLine(char First, char Middle, char Last) const
{
	std::cout << "\n";
	ConsoleUtility::CursorGotTo(55, ConsoleUtility::CursorPos.Y + 1);
	std::cout <<"      " << First;
	for (int i = 0; i < m_Height - 1; i++) {
		std::cout << BORDER_HORIZONTAL << BORDER_HORIZONTAL << BORDER_HORIZONTAL << Middle;
	}
	std::cout << BORDER_HORIZONTAL << BORDER_HORIZONTAL << BORDER_HORIZONTAL << Last;
}

void Board::PrintAIFiringBoardLine(char First, char Middle, char Last) const
{
	std::cout << "\n";
	ConsoleUtility::CursorGotTo(55, ConsoleUtility::CursorPos.Y + 1);
	std::cout << "      " << First;
	for (int i = 0; i < m_Height - 1; i++) {
		std::cout << BORDER_HORIZONTAL << BORDER_HORIZONTAL << BORDER_HORIZONTAL << Middle;
	}
	std::cout << BORDER_HORIZONTAL << BORDER_HORIZONTAL << BORDER_HORIZONTAL << Last;
}


void Board::UpdateElement(const char Element, const int Row, const int Col)
{
	m_GameBoard.at(Row).at(Col) = Element;
}

char Board::GetElement(const int Row, const int Col) const
{
	return m_GameBoard.at(Row).at(Col);
}

bool Board::IsValidCoordinate(const char Orientation, const int Row, const int Col, const int Length) const
{
	if ( (Row < m_Height && Row >= 0) && (Col < m_Width && Col >= 0) )
	{
		if( (Orientation == 'v') || (Orientation == 'V'))
		{
			return ((Row + Length - 1) < m_Height);
		}
		else
		{
			return (Col + Length - 1) < m_Width;
		}
	}
	return false;
}

bool Board::IsPlacementAvailable(char Orientation, int Row, int Col, int Length) const
{
	for (int i = 0; i < Length; ++i)
	{
		if( (Orientation == 'v') || (Orientation == 'V'))
		{
			if (m_GameBoard.at(Row + i).at(Col) != ' ')
			{
				return false;	
			}
		}
		else
		{
			if (m_GameBoard.at(Row).at(Col + i) != ' ')
			{
				return false;
			}
		}
	}
	return true;
}
