#include <iostream>

#include "Public/Core/Game.h"
#include "Public/Player/Player.h"
#include "Public/AI/AI.h"
#include "Public/Core/Utility.h"

Game::Game(std::vector<std::unique_ptr<Player>>& Players) : m_PlayerArr(&Players), m_RoundTurn(0)
{}

void Game::PlayGame()
{
	/* Plays Round if the game is not over*/
	while(!IsGameOver())
	{
		PlayRound();
	}
	// Wait To Press Enter and Return Back to Main Menu
	std::cout << "Press Enter to Continue";
	std::cin.ignore();
	ConsoleUtility::ClearScreen();
}

bool Game::IsGameOver() const
{
	if (m_PlayerArr->at(0)->GetStoredShips().empty() && m_PlayerArr->at(1)->GetStoredShips().empty())
	{
		return true; // if both boards maps are empty, return true;
	}
	if (m_PlayerArr->at(0)->GetStoredShips().empty()) // If Player 1 has no ships left stored, Player 2 Wins
	{
		ConsoleUtility::ClearScreen();
		m_PlayerArr->at(0)->DisplayBoards(false);
		m_PlayerArr->at(1)->DisplayBoards(true);
		std::cout << m_PlayerArr->at(1)->GetName() << " Won!" << std::endl;
		return true;
	}
	if (m_PlayerArr->at(1)->GetStoredShips().empty()) // If Player 2 has no ships left stored, Player 1 Wins
	{
		ConsoleUtility::ClearScreen();
		m_PlayerArr->at(0)->DisplayBoards(false);
		m_PlayerArr->at(1)->DisplayBoards(true);
		std::cout << m_PlayerArr->at(0)->GetName() << " Won!" << std::endl;
		return true;
	}
	return false;
}

void Game::PlayRound()
{
	// change turns and get player input to fire at opponent
	if (m_RoundTurn == 0)
	{
		ConsoleUtility::ClearScreen();
		m_PlayerArr->at(0)->DisplayBoards(false);
		if(GameControl::Debug::bDebugMode)
		{
			m_PlayerArr->at(1)->DisplayBoards(true);
		}

		// TF: Pointer Dereferenced
		m_PlayerArr->at(0)->Attack(m_PlayerArr->at(1)->GetPlacementBoard(), *m_PlayerArr->at(1), m_PlayerArr->at(1)->GetName(),
			m_PlayerArr->at(1)->GetStoredShips());
		m_RoundTurn = 1;
	}
	else
	{
		m_PlayerArr->at(0)->DisplayBoards(false);
		if (GameControl::Debug::bDebugMode)
		{
			m_PlayerArr->at(1)->DisplayBoards(true);
		}
		m_PlayerArr->at(1)->Attack(m_PlayerArr->at(0)->GetPlacementBoard(), *m_PlayerArr->at(0),  m_PlayerArr->at(0)->GetName(),
			m_PlayerArr->at(0)->GetStoredShips());
		m_RoundTurn = 0;
	}
}
