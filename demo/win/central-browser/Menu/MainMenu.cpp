#include "MainMenu.h"

#include <memory>
#include "BrowseServerServicesMenu.h"

using namespace std;

namespace Console
{
	MainMenu::MainMenu(const string& title) : Menu(title), m_ComPortMenu(NULL), m_BrowseServerServicesMenu(NULL)
	{
		unique_ptr<ComPortMenu> comPortMenu(make_unique<ComPortMenu>(this));
		m_ComPortMenu = comPortMenu.get();

		AddItem(unique_ptr<MenuItem>(move(comPortMenu)));
	}

	bool MainMenu::HandleMenu()
	{
		int previousCOM = m_ComPortMenu->GetCOMPort();
		if (!Menu::HandleMenu())
			return false;

		// check updated com port
		if (previousCOM != m_ComPortMenu->GetCOMPort())
		{
			// add the menu item
			if (m_BrowseServerServicesMenu == NULL)
			{
				unique_ptr<BrowseServerServicesMenu> browseServerServicesMenu = make_unique<BrowseServerServicesMenu>(this, m_ComPortMenu->GetSerialPort());
				m_BrowseServerServicesMenu = browseServerServicesMenu.get();

				AddItem(unique_ptr<MenuItem>(move(browseServerServicesMenu)));
			}

			// reloead the server services
			m_BrowseServerServicesMenu->Reload();
		}

		return true;
	}
}