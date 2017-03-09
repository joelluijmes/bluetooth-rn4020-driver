#ifndef COM_PORT_MENU_H_
#define COM_PORT_MENU_H_

#include "ConsoleMenu.h"

#include "WindowsSerialPort.h"

#include <memory>
#include <string>


namespace Console
{
	class ComPortMenu : public Menu
	{
	public:
		explicit ComPortMenu(const Menu* parent);

		std::string Text() const override;
		int GetCOMPort() const;
		const Serial::Windows::WindowsSerialPort& GetSerialPort() const;

	private:
		int m_CurrentCOM;
		std::unique_ptr<Serial::Windows::WindowsSerialPort> m_SerialPort;

		void OpenCom(int comPort);
	};
}

#endif // !COM_PORT_MENU_H_
