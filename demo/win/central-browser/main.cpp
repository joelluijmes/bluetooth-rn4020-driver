// user libraries
#include "Menu/MainMenu.h"

int main()
{
	Console::MainMenu menu("Central Browser");

	// blocks until user exit
	menu.Execute();

	return 0;
}
