#pragma once
#include <vector>
#include <memory>

class Player;

class Game
{
public:
	explicit Game(std::vector<std::unique_ptr<Player>>& Players);
	Game() = delete;
	void PlayGame();
private:
	[[nodiscard]] bool IsGameOver() const;
	void PlayRound();

	std::vector<std::unique_ptr<Player>>* m_PlayerArr;
	int m_RoundTurn;

};
