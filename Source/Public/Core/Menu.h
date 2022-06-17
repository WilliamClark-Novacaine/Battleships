#pragma once
class Menu
{
public:
	Menu();
	~Menu();

	void DisplayIntro();	// Displays Classic Arcade "Press Start To Play" Screens
private:
	void DisplayMainMenu();	// Displays User Choices of 2 Players, or Human VS AI
	void InitGameSetup();	// Starts Setup and Initializes all variable before game starts
	void DisplayCredits();	// Displays Author Credits
	void DebugMode();
	void DisplayRules();	// Displays Game Rules
};