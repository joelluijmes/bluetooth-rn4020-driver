#ifndef CONSOLE_MENU_H_
#define CONSOLE_MENU_H_

#include <string>
#include <vector>
#include <memory>

namespace Console
{
	class MenuItem
	{
	public:
		~MenuItem() { }

		virtual std::string Text() const = 0;
		virtual void Execute() const = 0;
	};

	class Menu : public MenuItem
	{
	public:
		Menu(const std::string& text);

		std::string Text() const override
		{
			return m_Text;
		}

		void Execute() const override;

		void AddItem(std::unique_ptr<MenuItem> item);

	private:
		std::string m_Text;
		std::vector<std::unique_ptr<MenuItem>> m_Items;

		mutable unsigned m_SelectedIndex;

		void PrintMenu() const;
		bool HandleMenu() const;
	};

	class EmptyItem : public MenuItem
	{
	public:
		EmptyItem(const std::string& str) : m_Str(str) {}

		std::string Text() const override
		{
			return m_Str;
		}

		void Execute() const override
		{
		}

	private:
		std::string m_Str;
	};
}

#endif // !CONSOLE_MENU_H_
