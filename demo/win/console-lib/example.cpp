#include "ConsoleMenu.h"

using namespace Console;
using namespace std;

int main()
{
	Menu menu("Main");

	unique_ptr<Menu> subMenu1(new Menu("SubMenu1"));
	subMenu1->AddItem(unique_ptr<MenuItem>(new EmptyItem("SubItem1 1")));
	subMenu1->AddItem(unique_ptr<MenuItem>(new EmptyItem("SubItem1 2")));
	menu.AddItem(move(subMenu1));

	unique_ptr<Menu> subMenu2(new Menu("SubMenu2"));
	subMenu2->AddItem(unique_ptr<MenuItem>(new EmptyItem("SubItem2 1")));
	subMenu2->AddItem(unique_ptr<MenuItem>(new EmptyItem("SubItem2 2")));
	menu.AddItem(move(subMenu2));

	menu.AddItem(unique_ptr<MenuItem>(new EmptyItem("Item 1")));
	menu.AddItem(unique_ptr<MenuItem>(new EmptyItem("Item 2")));

	menu.Execute();
}