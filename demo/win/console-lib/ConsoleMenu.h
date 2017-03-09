#ifndef CONSOLE_MENU_H_
#define CONSOLE_MENU_H_

#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace Console
{
	class MenuItem
	{
	public:
		virtual ~MenuItem() { }

		virtual std::string Text() const = 0;
		virtual void Execute() = 0;
	};

	class Menu : public MenuItem
	{
	public:
		Menu();
		explicit Menu(const std::string& text);
		explicit Menu(const Menu* parent);
		Menu(const Menu* parent, const std::string& text);

		std::string Text() const override;

		void Execute() override;

		void AddItem(std::unique_ptr<MenuItem> item);

	protected:
		virtual bool HandleMenu();
		void Exit();

	private:
		std::string m_Text;
		std::vector<std::unique_ptr<MenuItem>> m_Items;
		const Menu* m_Parent;

		unsigned m_SelectedIndex;
		bool m_ShouldExitMenu;

		void PrintMenu() const;
		
	};

	class EmptyItem : public MenuItem
	{
	public:
		explicit EmptyItem(const std::string& str) : m_Str(str) {}

		std::string Text() const override
		{
			return m_Str;
		}

		void Execute() override
		{
		}

	private:
		std::string m_Str;
	};

	class FunctionItem : public MenuItem
	{
	public:
		FunctionItem(const std::string& str, const std::function<void()>& func) 
			: m_Str(str), m_Function(func) {}

		   std::string Text() const override
		   {
			   return m_Str;
		   }

		   void Execute() override
		   {
			   m_Function();
		   }

	private:
		std::string m_Str;
		std::function<void()> m_Function;
	};
}

#endif // !CONSOLE_MENU_H_
