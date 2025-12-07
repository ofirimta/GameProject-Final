#pragma once
///////////////////////////////////////////////////////////

#include "Screen.h"
#include "Enums.h"
#include <conio.h>  //for _getch()

//what we want is to do return with fanction - 1/9 to the main. 
//in the main we have if- if we got 9 we do beake to main loop after we say goodbay to the
// user

////////////////////////////////////////////////////////////////

class Menu
{
	const char* menu_screens[2][MAX_Y] =
	{
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"                                                                                ", // 0 the index in arr screen
			"                                                                                ", // 1  //messege - "You found a.." for example
			"                                                                                ", // 2  //levels = SCREEN-2 (menu+last room).
			"                                                                                ", // 3
			"                                                                                ", // 4
			"                           Start a new game (1)                                 ", // 5   //door (1) Start a new game
			"                                                                                ", // 6
			"                                                                                ", // 7
			"                                                                                ", // 8 //riddle
			"                                                                                ", // 9
			"                                                                                ", // 10
			"                           Present instructions and keys (8)                    ", // 11
			"                                                                                ", // 12
			"                                                                                ", // 13
			"                                                                                ", // 14
			"                                                                                ", // 15
			"                                                                                ", // 16
			"                           EXIT  (9)                                            ", // 17  //key
			"                                                                                ", // 18
			"                                                                                ", // 19  //bomb
			"                                                                                ", // 20
			"                                                                                ", // 21
			"                                                                                ", // 22
			"                                                                                ", // 23
			"                                                                                "  // 24
		,
		"                                                                                ", // 0 the index in arr screen
			"                                                                                ", // 1  //messege - "You found a.." for example
			"                                                                                ", // 2  //levels = SCREEN-2 (menu+last room).
			"                                                                                ", // 3
			"                                                                                ", // 4
			"                                                                                ", // 5   //door (1) Start a new game
			"                                                                                ", // 6
			"                                                                                ", // 7
			"                                    settings....                                ", // 8 //riddle
			"                                                                                ", // 9
			"                                                                                ", // 10
			"                                                                                ", // 11
			"                                                                                ", // 12
			"                                                                                ", // 13
			"                                                                                ", // 14
			"                                                                                ", // 15
			"                                                                                ", // 16
			"                                                                                ", // 17  //key
			"                                                                                ", // 18
			"                                                                                ", // 19  //bomb
			"                                                                                ", // 20
			"                                                                                ", // 21
			"                                                                                ", // 22
			"                                                                                ", // 23
			"                                                                                "  // 24

	};
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	void draw(int room) const;

	//////////////////////////////////////////////////

	int user_choice();
};