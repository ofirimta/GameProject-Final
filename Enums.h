#pragma once

////////////////////////////////////////////////
#include <iostream>

/////////////////////////////////////////////////

using std::cout, std::endl;

//////////////////////////////////////////////////

enum class Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT,
	STAY

}; //up=0 right=1..... stay=4

//////////////////////////////////////////////////////////
enum { MAX_X = 80, MAX_Y = 25, SCREENS = 3 };
/// its in the class , i and ofir need to discuse where we want the enum and acording id to do class_name::max_x

///////////////////////////////////////////////////////////

enum special_nums_for_menu { NINE = 27, ONE = 49, EIGHT = 56 };  /// the value in ascii   

///////////////////////////////////////////////////////////

enum class ItemType
{
	NONE,
	KEY,
	BOMB,
	RIDDLE,
	SWITCH_ON,
	SWITCH_OFF
};

///////////////////////////////////////////////////////
// Define characters used in the game

const char RIDDLE_CHAR = '?';
const char BOMB_CHAR = '@';
const char KEY_CHAR = 'K';
const char SWITCH_ON_CHAR = '/';
const char SWITCH_OFF_CHAR = '\\';
const char IMMUTABLE_WALL_CHAR = 'i';

///////////////////////////////////////////////////////
const int NUM_KEYS = 6;  //keys for up, right, down, left, stay, dispose