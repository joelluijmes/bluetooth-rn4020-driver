#include "MainMenu.h"

#include <memory>
#include "BrowseServerServicesMenu.h"

using namespace std;

namespace Console
{
	MainMenu::MainMenu(const string& title) : Menu(title), m_ComPortMenu(NULL), m_Connected(false)
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
		if (previousCOM != m_ComPortMenu->GetCOMPort() && !m_Connected)
		{
			AddItem(unique_ptr<MenuItem>(make_unique<BrowseServerServicesMenu>(this, m_ComPortMenu->GetSerialPort())));

			m_Connected = true;
		}

		return true;
	}
}