#include "ConsoleMenu.h"

#include <iostream>

#include <conio.h>
#include <Windows.h>

namespace
{
	using namespace std;

	void ClearConsole();
	void SetCursorAtBottom();

	template <typename T>
	void PrintColored(WORD mask, const T& str);

	template <typename T>
	void PrintItem(const T& str);

	template <typename T>
	void PrintSelected(const T& str);
}

namespace Console
{
	Menu::Menu()
		: m_Text(), m_Items(), m_Parent(NULL), m_SelectedIndex(0), m_ShouldExitMenu(false)
	{
	}

	Menu::Menu(const string& text)
		: m_Text(text), m_Items(), m_Parent(NULL), m_SelectedIndex(0), m_ShouldExitMenu(false)
	{
	}

	Menu::Menu(const Menu* parent)
		: m_Text(), m_Items(), m_Parent(parent), m_SelectedIndex(0), m_ShouldExitMenu(false)
	{
	}

	Menu::Menu(const Menu* parent, const string& text)
		: m_Text(text), m_Items(), m_Parent(parent), m_SelectedIndex(0), m_ShouldExitMenu(false)
	{
	}

	string Menu::Text() const
	{
		return m_Text;
	}

	void Menu::Execute() const
	{
		while (!m_ShouldExitMenu && HandleMenu())
			;

		m_ShouldExitMenu = false;
	}

	void Menu::AddItem(unique_ptr<MenuItem> item)
	{
		m_Items.push_back(move(item));
	}

	void Menu::Exit() const
	{
		m_ShouldExitMenu = true;
	}

	void Menu::PrintMenu() const
	{
		ClearConsole();

		string index = m_Parent
			? m_Parent->Text() + " > " + m_Text
			: m_Text;
		PrintItem(index);

		unsigned currentIndex = 0;
		for (const auto& item : m_Items)
		{
			cout << " ";
			if (currentIndex++ == m_SelectedIndex)
				PrintSelected(item->Text());
			else
				PrintItem(item->Text());
		}

		SetCursorAtBottom();
	}

	bool Menu::HandleMenu() const
	{
		PrintMenu();

		int key = _getch();
		if (key == 27 || key == 'q' || key == '\b') // esc or backspace
			return false;

		if (key == '\r') // enter
		{
			m_Items.at(m_SelectedIndex)->Execute();
			return true;
		}

		if (key == 0 && key == 224) // escape/special key
			return true;

		int index = m_SelectedIndex;

		key = _getch();
		switch (key)
		{
			// up
		case 72:
			--index;
			break;

			// down
		case 80:
			++index;
			break;

			// right
		case 77:
			// enter
			m_Items.at(m_SelectedIndex)->Execute();
			return true;
		}

		m_SelectedIndex = index % m_Items.size();
		return true;
	}
}

namespace
{
	void ClearConsole()
	{
		static COORD topLeft = { 0, 0 };
		static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO screen;
		GetConsoleScreenBufferInfo(console, &screen);

		DWORD written;
		FillConsoleOutputCharacter(
			console,
			' ',
			screen.dwSize.X * screen.dwSize.Y,
			topLeft,
			&written);

		FillConsoleOutputAttribute(
			console,
			FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			screen.dwSize.X * screen.dwSize.Y,
			topLeft,
			&written);

		SetConsoleCursorPosition(console, topLeft);
	}

	void SetCursorAtBottom()
	{
		static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screen;
		GetConsoleScreenBufferInfo(console, &screen);

		COORD bottomLeft = { 0, screen.srWindow.Bottom };
		SetConsoleCursorPosition(console, bottomLeft);
	}

	template <typename T>
	void PrintColored(WORD mask, const T& str)
	{
		static HANDLE s_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO screenInfo;
		GetConsoleScreenBufferInfo(s_Handle, &screenInfo);

		SetConsoleTextAttribute(s_Handle, mask);
		cout << str << endl;

		SetConsoleTextAttribute(s_Handle, screenInfo.wAttributes);
	}

	template <typename T>
	void PrintItem(const T& str)
	{
		PrintColored(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED, str);
	}

	template <typename T>
	void PrintSelected(const T& str)
	{
		PrintColored(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED, str);
	}
}