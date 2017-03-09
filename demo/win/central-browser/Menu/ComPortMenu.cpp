#include "ComPortMenu.h"

#include <functional>
#include <memory>
#include <string>

#include <Windows.h>

using namespace std;

namespace Console
{
	ComPortMenu::ComPortMenu(const Menu* parent) : Menu(parent, "Select COM Port"), m_CurrentCOM(-1)
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

	void ComPortMenu::OpenCom(int comPort)
	{
		if (comPort == m_CurrentCOM)
			return;

		m_CurrentCOM = comPort;
	}
}