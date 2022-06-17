#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib>

#include "Public/Core/Game.h"
#include "Public/Core/Menu.h"
#include "Public/Core/Setup.h"
#include "Public/Core/Utility.h"
#include "Public/Player/Player.h"

int main()
{
	ConsoleUtility::ResizeConsole(880, 480);
	// TF: Pointer Initialised
	auto* Opening = new Menu;
	Opening->DisplayIntro();
	return 0;
}
