#ifndef BLUETOOTH_MENU_H_
#define BLUETOOTH_MENU_H_

#include "ConsoleMenu.h"
#include "Serial/ISerial.h"
#include "Drivers/RN4020Device.h"

namespace Console
{
	class BluetoothMenu : public Menu
	{
	public:
		BluetoothMenu(const Menu* parent, const std::string title, const Serial::ISerial& serial)
			: Menu(parent, title), m_Serial(serial), m_Device(serial)
		{
			
		}
		
	protected:
		const Serial::ISerial& m_Serial;
		const Bluetooth::RN4020Device m_Device;
	};
}
#endif // !BLUETOOTH_MENU_H_
