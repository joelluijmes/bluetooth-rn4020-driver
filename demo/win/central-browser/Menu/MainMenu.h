#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include "ConsoleMenu.h"
#include "ComPortMenu.h"
#include "BrowseServerServicesMenu.h"

#include <string>


namespace Console
{
	class MainMenu : public Menu
	{
	public:
		explicit MainMenu(const std::string& title);

		bool HandleMenu() override;

	private:
		ComPortMenu* m_ComPortMenu;
		BrowseServerServicesMenu* m_BrowseServerServicesMenu;
	};
}

#endif // !MAIN_MENU_H_
