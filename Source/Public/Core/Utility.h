#pragma once
#include <map>
#include <Windows.h>
#include <string>
namespace ConsoleUtility
{
inline HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
static COORD CursorPos;
	inline void changeColor(const int Color)
	{
		SetConsoleTextAttribute(ConsoleHandle, Color);
	}

	inline void CursorGotTo(const int X, const int Y)
	{
		CursorPos.X = X;
		CursorPos.Y = Y;
		SetConsoleCursorPosition(ConsoleHandle, CursorPos);
	}

	inline void ClearScreen()
	{
		system("CLS");
	}

	inline void ResizeConsole(short X, short Y)
	{
		MoveWindow(GetConsoleWindow(), 0, 0, X, Y, false);
	}
}

namespace GameControl::Debug
{
	inline bool bDebugMode = false;
}

namespace Utility::LookUpTables
{
	//Generate Lookup Table
	static std::map<char, int> RowCoordLUT =
	{
		{'a', 0}, {'A', 0},
		{'b', 1}, {'B', 1},
		{'c', 2}, {'C', 2},
		{'d', 3}, {'D', 3},
		{'e', 4}, {'E', 4},
		{'f', 5}, {'F', 5},
		{'g', 6}, {'G', 6},
		{'h', 7}, {'H', 7},
		{'i', 8}, {'I', 8},
		{'j', 9}, {'J', 9}
	};

	static std::string ShipTypeString(const char ShipType)
	{
		std::string ShipString;
		switch (ShipType)
		{
		case 'A': ShipString = "Aircraft Carrier"; break;
		case 'B': ShipString = "Battleship"; break;
		case 'D': ShipString = "Destroyer"; break;
		case 'P': ShipString = "Patrol Boat"; break;
		case 'S': ShipString = "Submarine"; break;
		default: break;
		}
		return ShipString;
	}
}
