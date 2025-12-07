#pragma once
///////////////////////////////////////////////
#include "Point.h" 
#include "Enums.h"
#include "utils.h"

class Player;

#include <cstring> //for consractor- 
//I use strcpy in screen.cpp. this is the library  
////////////////////////////////////////////////////

class Screen
{
	const char* templates_screens[SCREENS][MAX_Y] =
	{
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789

			"Messages: x                                                                     ", // 0 the index in arr screen
			"Health: $: 3  &: 3     Level: 1/3      Inventory: $:           &:               ", // 1  //messege - "You found a.." for example
			"Hints: x                                                                        ", // 2  //levels = SCREEN-2 (menu+last room).
			"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii", // 3
			"iwwwwwwwwwwwwwww                                                               i", // 4
			"iwwww                                                                          i", // 5
			"iwwww                                                   wwwwwwwwww             i", // 6
			"iwwwwwwwwwwwwwwwwwwww                wwwwww             ww       w      wwwwwwwi", // 7
			"i       ?          ww                wwwwww             ww         w    w    wwi", // 8   //riddle
			"i                  ww                                   ww      ?    wwww    wwi", // 9  //riddle
			"i                  ww                                   ww           wwww    wwi", // 10
			"i                  ww                                   ww                   wwi", // 11
			"i          wwwwwwwwww                                   ww                   wwi", // 12
			"i                               wwwwww                  ww                   wwi", // 13
			"i                               wwwwww                  wwwww                wwi", // 14
			"i                               wwwwww                  wwwww                  i", // 15
			"iwwww                                                                          i", // 16
			"iwwww                                                                          i", // 17
			"iwwww                                                                          i", // 18
			"iwww                                          www                              i", // 19
			"iww                    wwwwww                 www             www       ////   1", // 20   ////door  //switch - i think that we need use one answer from this riddels in next room
			"i                      wwwwww                 www             www              i", // 21
			"iww                    wwwwww                 www       ?     www              i", // 22  //riddle
			"iww                                           www             www              i", // 23
			"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"  // 24
			,

			"Messages: x                                                                     ", // 0 the index in arr screen
			"Health: $: 3  &: 3     Level: 2/3      Inventory: $:           &:               ", // 1  //messege - "You found a.." for example
			"Hints: x                                                                        ", // 2  //levels = SCREEN-2 (menu+last room).
			"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii", // 3
			"i                                w                   w                         i", // 4
			"i                                w                   wwwwwwwwwwwww             2", // 5   //door
			"i                           wwwwww                               w             i", // 6
			"iwwwwwwwwwwwwwwww           w                 w                  w             i", // 7
			"i                           w                 wwwwwwwwwwww?wwwwwwwwwwwwww      i", // 8 //riddle
			"i                           w                 w                  w             i", // 9
			"i         wwwwwwwwwwwwwwwwwww                 w                  w             i", // 10
			"i                                    wwwwwwwwww                  w             i", // 11
			"i                                    w                           w             i", // 12
			"i                                    w                           w             i", // 13
			"iwwwwwwwwwwwww                       w                      wwwwwwwwww         i", // 14
			"i            w      wwwwwwwwwwwwwwwwwwwwwwwwwwwwwww              w             i", // 15
			"i            w                       w                           w             i", // 16
			"i            w                       wwwwww                wwwwwww      K      i", // 17  //key
			"i            wwwwwwwww                    wwwwwwww         w                   i", // 18
			"i            w                                   w   @     w                   i", // 19  //bomb
			"1            w                  w                w         w          wwwwwwwwwi", // 20
			"i            wwwwwwwww          w        wwwwwwwwwwwwwwwwwww                   i", // 21
			"i                               w                          w                   i", // 22
			"i                               w                          w                   i", // 23
			"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"  // 24
		,
			"Messages: Good Job!!!                                                           ", // 0 the index in arr screen
			"Health: $: 3  &: 3     Level: 3/3      Inventory: $:           &:               ", // 1  //messege - "You found a.." for example
			"Hints: x                                                                        ", // 2  //levels = SCREEN-2 (menu+last room).
			"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii", // 3
			"i                                                                              i", // 4
			"2                                                                              i", // 5   //door
			"i                                                                              i", // 6
			"i                                                                              i", // 7
			"i                                                                              i", // 8 //riddle
			"i                                                                              i", // 9
			"i                                                                              i", // 10
			"i                                                                              i", // 11
			"i                                                                              i", // 12
			"i                                                                              i", // 13
			"i                                                                              i", // 14
			"i                                                                              i", // 15
			"i                                                                              i", // 16
			"i                                                                              i", // 17  //key
			"i                                                                              i", // 18
			"i                                                                              i", // 19  //bomb
			"i                                                                              i", // 20
			"i                                                                              i", // 21
			"i                                                                              i", // 22
			"i                                                                              i", // 23
			"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"  // 24
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:

	char current_screens[SCREENS][MAX_Y][MAX_X + 1];
	///// same and not const and the last var is to copy the strings with cpycopy + i added +1 to the last var 
	//because i count the string munuel and i need to add '\0'.
	/////////////////////////////////////////////

	Screen();  /// constrector to copy 

	////////////////////////////////////////////

	void draw(int room) const;

	////////////////////////////////////////////

	char getCharAt(const Point& p, int room) const  //const in right side tell that we dont change the  classs members in this file class.
	{
		return current_screens[room][p.getY()][p.getX()];
	}
	////////////////////////////////////////////

	void setCharAt(const Point& p, int room)  //function to change the char in the current screen
	{
		current_screens[room][p.getY()][p.getX()] = p.getChar();
	}
	/////////////////////////////////////////////

	void setHealthAt(const Player& my_player, int room);

	/////////////////////////////////////////////////

	void setInventoryAt(const Player& my_player, int room);

	//////////////////////////////////////////////////

	void delInventoryAt(const Player& my_player, int room);

	/////////////////////////////////////////////////

	void setMessageAt(int room, const char* new_str); //we managing the massages so we managing the meomery!!!!/////////////////

	//////////////////////////////////////////////////
	void delMessageAt(int room);

	///////////////////////////////////////////////////

	void setHintAt(int room, const char* new_str); //we managing the massages so we managing the meomery!!!!/////////////////

	//we have 2 similar function but we dont marge them to one because its more readable and every function can recieve different size of string.
	//we dont need function theat chacking if we write because other function delete until ' '. and id place empty the function no enter to the loops


};
