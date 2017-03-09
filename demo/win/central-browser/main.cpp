// user libraries
#include "ConsoleMenu.h"

// std libraries
#include <memory>
#include <iostream>

#include <Windows.h>

using namespace Console;
using namespace std;

void StartScan()
{

}

class ComPortMenu : public Menu
{
public:
	explicit ComPortMenu(const Menu* parent)
		: Menu(parent, "Select COM Port"), m_ComPort(-1)
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
					Exit();
				};

				AddItem(unique_ptr<MenuItem>(make_unique<FunctionItem>(buf, func)));
			}
		}
	}

	string Text() const override
	{
		return m_ComPort == -1
			? "Serial Port: Disconnected"
			: string("Serial Port: COM") + to_string(m_ComPort);
	}

private:
	int m_ComPort;

	void OpenCom(int comPort)
	{
		m_ComPort = comPort;
	}
};

void ListComPorts()
{
	char buf[7] = "COM"; // COM255\0
	char targetPath[32];

	for (int i = 0; i < 255; ++i)
	{
		snprintf(buf + 3, 4, "%d", i);

		if (QueryDosDevice(buf, targetPath, sizeof(targetPath)))
			cout << buf << endl;
	}
}

int main()
{
	Menu menu("Central Browser");	
	menu.AddItem(unique_ptr<MenuItem>(make_unique<ComPortMenu>(&menu)));


	// blocks until user exit
	menu.Execute();

	return 0;
}