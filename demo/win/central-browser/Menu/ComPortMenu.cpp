#include "ComPortMenu.h"

#include <functional>
#include <memory>
#include <string>

#include <Windows.h>

using namespace std;
using namespace Serial::Windows;

namespace Console
{
	ComPortMenu::ComPortMenu(const Menu* parent) 
		: Menu(parent, "Select COM Port"), m_CurrentCOM(-1)
	{
		char buf[7] = "COM"; // COM255\0
		char targetPath[32];

		for (int i = 0; i < 255; ++i)
		{
			snprintf(buf + 3, 4, "%d", i);

			if (QueryDosDevice(buf, targetPath, sizeof(targetPath)))
			{
				function<void()> func = [=]
				{
					this->OpenCom(i);
					this->Exit();
				};

				AddItem(unique_ptr<MenuItem>(make_unique<FunctionItem>(buf, func)));
			}
		}
	}

	string ComPortMenu::Text() const
	{
		return m_CurrentCOM == -1
			? "Serial Port: Disconnected"
			: string("Serial Port: COM") + to_string(m_CurrentCOM);
	}

	int ComPortMenu::GetCOMPort() const
	{
		return m_CurrentCOM;
	}

	const WindowsSerialPort& ComPortMenu::GetSerialPort() const
	{
		return *m_SerialPort;
	}

	void ComPortMenu::OpenCom(int comPort)
	{
		if (comPort == m_CurrentCOM)
			return;

		if (m_CurrentCOM != -1)
		{
			m_SerialPort->Close();
			m_SerialPort.reset();
		}

		char comBuf[12] = "\\\\.\\COM";
		snprintf(comBuf + 7, 4, "%d", comPort);

		m_SerialPort = make_unique<WindowsSerialPort>(comBuf, Serial::BAUDRATE_115200, Serial::DATABIT_8, Serial::PARITYBIT_NONE, Serial::STOPBIT_1);
		if (m_SerialPort->Open())
			m_CurrentCOM = comPort;
	}
}