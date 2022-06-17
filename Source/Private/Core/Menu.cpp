#define NOMINMAX
#include "Public/Core/Menu.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <limits>
#include <cstdio>

#include "Public/Core/Game.h"
#include "Public/Core/Setup.h"
#include "Public/Core/Utility.h"

Menu::Menu()
= default;

Menu::~Menu()
= default;

void Menu::DisplayIntro()
{
	std::cout << R"(
                 _           _   _   _           _     _       
                | |         | | | | | |         | |   (_)      
                | |__   __ _| |_| |_| | ___  ___| |__  _ _ __  
                | '_ \ / _` | __| __| |/ _ \/ __| '_ \| | '_ \ 
                | |_) | (_| | |_| |_| |  __/\__ \ | | | | |_) |
                |_.__/ \__,_|\__|\__|_|\___||___/_| |_|_| .__/ 
                                      by William Clark  | |    
                                                        |_|


                            Press Enter To Start...

                                     # #  ( )
                                  ___#_#___|__
                              _  |____________|  _
                       _=====| | |            | | |==== _
                 =====| |.---------------------------. | |====
   <--------------------'   .  .  .  .  .  .  .  .   '--------------/
     \                                                             /
      \_______________________________________________WWS_________/
  wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
   wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	)";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	ConsoleUtility::ClearScreen();
    DisplayMainMenu();
}

void Menu::DisplayMainMenu()
{
	std::cout << R"(
                 _           _   _   _           _     _       
                | |         | | | | | |         | |   (_)      
                | |__   __ _| |_| |_| | ___  ___| |__  _ _ __  
                | '_ \ / _` | __| __| |/ _ \/ __| '_ \| | '_ \ 
                | |_) | (_| | |_| |_| |  __/\__ \ | | | | |_) |
                |_.__/ \__,_|\__|\__|_|\___||___/_| |_|_| .__/ 
                                      by William Clark  | |    
                                                        |_|
				Menu Navigation:
						**Use Arrow Keys to Navigate
						**Press Enter to Select
	)" << std::endl;
	// TF: Array
	int ColorSet[] = { 7,7,7,7,12};
	int MenuCounter = 5;

	for (int i = 0;;)
	{
		ConsoleUtility::CursorGotTo(35, 13);
		ConsoleUtility::changeColor(ColorSet[0]);
		std::cout << "1. Play";

		ConsoleUtility::CursorGotTo(35, 14);
		ConsoleUtility::changeColor(ColorSet[1]);
		std::cout << "2. Rules";

		ConsoleUtility::CursorGotTo(35, 15);
		ConsoleUtility::changeColor(ColorSet[2]);
		if (GameControl::Debug::bDebugMode)
		{
			std::cout << "3. Debug Mode [ON]";
		}
		else std::cout << "3. Debug Mode [OFF]";

		ConsoleUtility::CursorGotTo(35, 16);
		ConsoleUtility::changeColor(ColorSet[3]);
		std::cout << "4. Credits";

		ConsoleUtility::CursorGotTo(35, 17);
		ConsoleUtility::changeColor(ColorSet[4]);
		std::cout << "5. Quit";

		const char InputKey = _getch();

		if (InputKey == 72 && (MenuCounter >= 2 && MenuCounter <= 5))
		{
			MenuCounter--;
		}
		if (InputKey == 80 && (MenuCounter >= 1 && MenuCounter <= 4))
		{
			MenuCounter++;
		}
		if (InputKey == '\r')//carriage return
		{
			if (MenuCounter == 1)
			{
				// if enter is click and highlight is on 1 the program will run the code here
				ConsoleUtility::changeColor(15);
				InitGameSetup();
			}
			if (MenuCounter == 2)
			{;
				ConsoleUtility::changeColor(15);
				DisplayRules();
			}
			if (MenuCounter == 3)
			{
				ConsoleUtility::changeColor(15);
				DebugMode();
			}
			if (MenuCounter == 4)
			{
				ConsoleUtility::changeColor(15);
				DisplayCredits();
			}
			if (MenuCounter == 5)
			{
				ConsoleUtility::changeColor(15);
				exit(0);
			}
		}

		ColorSet[0] = 7;
		ColorSet[1] = 7;
		ColorSet[2] = 7;
		ColorSet[3] = 7;
		ColorSet[4] = 7;

		if (MenuCounter == 1)
		{
			ColorSet[0] = 12;
		}
		if (MenuCounter == 2)
		{
			ColorSet[1] = 12;
		}
		if (MenuCounter == 3)
		{
			ColorSet[2] = 12;
		}
		if (MenuCounter == 4)
		{
			ColorSet[3] = 12;
		}
		if (MenuCounter == 5)
		{
			ColorSet[4] = 12;
		}
	}
}

void Menu::InitGameSetup()
{
	ConsoleUtility::ClearScreen();
	srand(static_cast<unsigned int>(std::time(nullptr))); //Seed All Random Function
	std::vector<std::unique_ptr<Player>> PlayerArr; //Creates Dynamic Array of Players
	std::vector<BattleShip> Ships = {};	//Array of Ships we want placed on the Board;
	std::map<char, int> ShipStorage;
	constexpr char ShipTypes[5] = { 'A','B','D','S','P' };
	constexpr int ShipLengths[5] = { 5, 4, 3, 3, 2 };

	for (int i = 0; i < 5; ++i)
	{
		char ShipType = ShipTypes[i];
		int ShipLength = ShipLengths[i];

		ShipStorage.insert({ ShipType, ShipLength });
	}

	Ships.reserve(ShipStorage.size());
	for (auto& i : ShipStorage)
	{
		Ships.emplace_back(i.first, i.second);
	}

	constexpr int BoardWidth = 10;
	constexpr int BoardHeight = 10;

	//Create Player
	CreateHumanPlayer(BoardHeight, BoardWidth, Ships, PlayerArr);
	//Create AI Player
	CreateAIRandomPlayer(BoardHeight, BoardWidth, Ships, PlayerArr);
	ConsoleUtility::ClearScreen();
	if(GameControl::Debug::bDebugMode)
	{
		//Resize Console For Debug Mode
		ConsoleUtility::ResizeConsole(900, 900);
	}
	// TF: Dynamic Memory
	const auto GameLoop = new Game(PlayerArr); //Creates Game Object
	GameLoop->PlayGame();
	//Game Finishes, Go Back to main Menu
	DisplayMainMenu();
}

void Menu::DisplayCredits()
{
	system("CLS");
	std::cout << R"(
                      ____                       __             __              
                     /\  _`\                    /\ \     __    /\ \__           
                     \ \ \/\_\   _ __     __    \_\ \   /\_\   \ \ ,_\    ____  
                      \ \ \/_/_ /\`'__\ /'__`\  /'_` \  \/\ \   \ \ \/   /',__\ 
                       \ \ \L\ \\ \ \/ /\  __/ /\ \L\ \  \ \ \   \ \ \_ /\__, `\
                        \ \____/ \ \_\ \ \____\\ \___,_\  \ \_\   \ \__\\/\____/
                         \/___/   \/_/  \/____/ \/__,_ /   \/_/    \/__/ \/___/ )" << std::endl << std::endl;
	std::cout << "\t\t\t\t"; std::cout << "Version: ";ConsoleUtility::changeColor(11); std::cout << "1.0.5" << std::endl; ConsoleUtility::changeColor(15); // Version
	std::cout << "\t\t\t\t"; std::cout << "Date: "; ConsoleUtility::changeColor(13); std::cout << "16 / 06 / 2022" << std::endl; ConsoleUtility::changeColor(15); // Date
	std::cout << "\t\t\t\t"; std::cout << "Author: "; ConsoleUtility::changeColor(14); std::cout << "William Clark" << std::endl; // Author
	std::cout << "\t\t\t\t"; std::cout << "Media Design School Cohort 22021 (2022)" << std::endl;
	std::cout << "\t\t\t\t"; std::cout << "BSE GD1P01" << std::endl << std::endl;
	ConsoleUtility::changeColor(15);
	Sleep(3000);
	std::cout << "\t\t\t\t"; std::cout << "Returning to main menu shortly..." << std::endl << std::endl;
	Sleep(5000);
	system("CLS");
	DisplayMainMenu();
}

void Menu::DebugMode()
{
	ConsoleUtility::ClearScreen();
	if(!GameControl::Debug::bDebugMode)
	{
		GameControl::Debug::bDebugMode = true;
	}
	else
	{
		GameControl::Debug::bDebugMode = false;
	}
	DisplayMainMenu();
}

void Menu::DisplayRules()
{
	system("CLS");
	std::cout << R"(
	                 ____                 ___                      
	                /\  _`\              /\_ \                     
	                \ \ \L\ \    __  __  \//\ \       __     ____  
	                 \ \ ,  /   /\ \/\ \   \ \ \    /'__`\  /',__\ 
	                  \ \ \\ \  \ \ \_\ \   \_\ \_ /\  __/ /\__, `\
	                   \ \_\ \_\ \ \____/   /\____\\ \____\\/\____/
	                    \/_/\/ /  \/___/    \/____/ \/____/ \/___/ )" << std::endl << std::endl;
	std::cout << " ** There are 5 Ships: Aircraft Carrier (5), Battleship (4), Destroyer(3), Submarine(3), Patrol Boat(2)" << std::endl;
	std::cout << " ** Each player places the 5 ships somewhere on their board." << std::endl;
	std::cout << " ** The ships can only be placed vertically or horizontally." << std::endl;
	std::cout << " ** Player's take turns at shooting by guessing the coordinates, of the opponents ships." << std::endl;
	std::cout << " ** The shot is either a 'Hit' or 'Miss'" << std::endl;
	std::cout << " ** Once a ship has all its coordinates hit, the Ship is Sunk" << std::endl;
	std::cout << " ** Once all ships on a player's board are sunk. The game is over." << std::endl;
	Sleep(3000);
	std::cout << "\t\t\t\t"; std::cout << "Returning to main menu shortly..." << std::endl << std::endl;
	/*
		  To play, place a bet.
		  Three values in the range 2 to 7 will be randomly selected.
		  If two are the same, you win 3x the bet.
		  If all three are the same, you win 5x the bet.
		  If all three are 7, you win 10x the bet.
		  If none of these events occur, you lose the bet.
	 */
	Sleep(5000);
	system("CLS");
	DisplayMainMenu();
}
