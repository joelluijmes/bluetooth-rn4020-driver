#ifndef BROWSE_SERVER_SERVICES_MENU_H_
#define BROWSE_SERVER_SERVICES_MENU_H_

#include "BluetoothMenu.h"

#include <string>
#include "Serial/ISerial.h"


namespace Console
{
	class BrowseServerServicesMenu : public BluetoothMenu
	{ 
	public:
		BrowseServerServicesMenu(const Menu* parent, const Serial::ISerial& serial);
		void Reload();

	private:
	};
}

#endif // !BROWSE_SERVER_SERVICES_MENU_H_
