#ifndef COM_PORT_MENU_H_
#define COM_PORT_MENU_H_

#include "ConsoleMenu.h"

#include <string>

namespace Console
{
	class ComPortMenu : public Menu
	{
	public:
		explicit ComPortMenu(const Menu* parent);

		std::string Text() const override;
		int GetCOMPort() const;

	private:
		int m_CurrentCOM;

		void OpenCom(int comPort);
	};
}

#endif // !COM_PORT_MENU_H_
