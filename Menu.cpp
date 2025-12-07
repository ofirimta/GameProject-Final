#include "Menu.h"

///////////////////////////////////////////////////////////////////////////////

void Menu::draw(int room)
const {
	cls();
	gotoxy(0, 0);

	for (size_t i = 0; i < MAX_Y - 1; ++i)
	{
		cout << menu_screens[room][i] << endl;
	}
	cout << menu_screens[room][MAX_Y - 1];
	cout.flush();
}

//////////////////////////////////////////////////////////////////////////////

int Menu::user_choice()
{
	while (true)
	{
		char key = _getch();  ////we wating to char ( we dont need  _kbhit() because now screen is ststic)

		//we dont need here get char if no onw of keys. the loop just start from begining
		if (key == special_nums_for_menu::EIGHT)
		{
			draw(1);
			key = _getch();  //push- and every char go to menu
			draw(0);
		}
		else if (key == special_nums_for_menu::ONE)
		{
			return 1;
		}
		else if (key == special_nums_for_menu::NINE)

		{
			return 9;  //dont need break!!!!
		}

	}
}