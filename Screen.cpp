#define _CRT_SECURE_NO_WARNINGS
#include "Screen.h"
#include "Player.h"


///////////////////////////////////////////


void Screen::draw(int room)
const {
	cls();
	gotoxy(0, 0);

	for (size_t i = 0; i < MAX_Y - 1; ++i) {
		cout << current_screens[room][i] << endl;
	}
	cout << current_screens[room][MAX_Y - 1];
	cout.flush();
}
/////////////////////////////////////////////////

Screen::Screen()  //size_t for index!!!!
{
	for (size_t i = 0; i < SCREENS; i++)   // we pass over all rooms maps
	{
		for (size_t j = 0; j < MAX_Y; j++) // we pass over all rows
		{
			strcpy(current_screens[i][j], templates_screens[i][j]);
		}
	}
}

//////////////////////////////////////////////////////
void Screen::setInventoryAt(const Player& my_player, int room)
{
	char player_sign = my_player.getCharacter();//witch palyer
	int i = 0;

	ItemType my_item_type = my_player.getHeldItem();   //get nam of Inventory
	//////////////////// itemtype to const char*

	const char* new_inventory = "";

	switch (my_item_type)
	{
	case ItemType::NONE:
		new_inventory = "NONE";
		break;
	case ItemType::KEY:
		new_inventory = "Key";
		break;
	case ItemType::BOMB:
		new_inventory = "Bomb";
		break;
	case ItemType::SWITCH_ON:
		new_inventory = "On";
		break;
	case ItemType::SWITCH_OFF:
		new_inventory = "Off";
		break;
	}
	//////////////////////////
	char ch = new_inventory[i];
	if (player_sign == '$')
	{
		while (ch != '\0')
		{
			current_screens[room][1][52 + i] = ch;
			i++;
			ch = new_inventory[i];//importent - loop {.................. 
		}
	}
	else
	{
		while (ch != '\0')
		{
			current_screens[room][1][65 + i] = ch;
			i++;
			ch = new_inventory[i];
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////

void Screen::delInventoryAt(const Player& my_player, int room)
{
	char player_sign = my_player.getCharacter();

	int i = 0;

	if (player_sign == '$')
	{
		char ch = current_screens[room][1][52 + i];

		while ((ch != ' ') && (ch != '&'))
		{

			current_screens[room][1][52 + i] = ' ';  //cant change to ch- only ny reference
			i++;
			ch = current_screens[room][1][52 + i];
		}
	}
	else
	{
		char ch = current_screens[room][1][65 + i];
		while ((ch != ' ') && (ch != '\0'))
		{
			current_screens[room][1][65 + i] = ' ';
			i++;
			ch = current_screens[room][1][65 + i];       //importent - loop {.................. 
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////

void Screen::setHealthAt(const Player& my_player, int room)
{
	char player_sign = my_player.getCharacter();
	char new_life_val = ((my_player.getLifeCount()) + '0');

	if (player_sign == '$')
	{
		current_screens[room][1][11] = new_life_val; //we have enough place to copy we chacked it about all items
	}
	else
	{
		current_screens[room][1][17] = new_life_val;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
void Screen::setMessageAt(int room, const char* new_str)
{
	int i = 0;

	char ch = new_str[i];
	while (ch != '\0')
	{
		current_screens[room][0][10 + i] = ch;
		i++;
		ch = new_str[i];
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
void Screen::setHintAt(int room, const char* new_str)
{
	int i = 0;
	char ch = new_str[i];
	while (ch != '\0')
	{
		current_screens[room][2][7 + i] = ch;
		i++;
		ch = new_str[i];
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
void Screen::delMessageAt(int room)
{
	int i = 0;

	{
		char ch = current_screens[room][0][10 + i];

		while ((ch != ' ') && (ch != '\0'))
		{

			current_screens[room][0][10 + i] = ' ';//cant_change_to_ch- only ny reference
			i++;
			ch = current_screens[room][0][10 + i];
		}
	}
}