#include "Public/AI/AI.h"

AI::AI(const std::string& PlayerName, const int BoardHeight, const int BoardWidth) : Player(PlayerName, BoardHeight, BoardWidth)
{}

char AI::SelectOrientation()
{
	// TF: Pseudo Random Number
	const int Num = rand() % 100 - 1;
	char Orientation;
	if (Num >= 50)
	{
		Orientation = 'H';
	}
	else
	{
		Orientation = 'V';
	}
	return Orientation;
}

int AI::SelectRow(char Orientation, int ShipLength) const
{
	int Num;
	if (Orientation == 'H')
	{
		Num = rand() % m_BoardHeight;
	}
	else
	{
		Num = rand() % (m_BoardHeight - ShipLength +  1);
	}
	return Num;
}

int AI::SelectCol(char Orientation, int ShipLength) const
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
