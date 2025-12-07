
#pragma once

////////////////////////////////////////////////

#include "Point.h"
#include "Enums.h"
#include "Bomb.h"
#include "Screen.h"


class Screen;
class Door;
////////////////////////////////////////////////

class Player {


    Point location;   //location of the player on the screen
    char keys[NUM_KEYS];
    Screen& screen;
    Bomb& active_bomb;
    const char character;  // $ or &
    ItemType held_item;   // held item type
    int &current_room_index; // index of the current room the player is in
	bool is_finished_level = false; // indicates if the player has finished the level
	int life_count = 3; // number of lives the player has
    Door* pDoor;

private:
    char char_under_player = ' ';

//////////////////////////////////////////////////////////////////

public:

    Player(const Point& point, const char(&the_keys)[NUM_KEYS + 1], Screen& theScreen, char character, Bomb& bomb_ref, int& current_room, Door* current_room_door);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    void draw();
    ///////////////////////////////////////////////////////////
    void move();
    ///////////////////////////////////////////////////////////
    void handleKeyPressed(char key);
    ///////////////////////////////////////////////////////////
    void disposeItem();
    ///////////////////////////////////////////////////////////
    void setHeldItem(ItemType type);
    ///////////////////////////////////////////////////////////
    ItemType getHeldItem() const 
    {
        return held_item;
    }
    ///////////////////////////////////////////////////////////
    void handleCollision(int component_char);

	////UPDATES////

    bool isFinished() const { return is_finished_level; }

    void disappear();

    void appear();

    int getCurrentRoomIndex() const  
    {
        return current_room_index;
    }
   
    char getCharacter() const
    {
        return character;
    }

    int getLifeCount() const 
    {
        return life_count;
	}

    void hitByBomb()
    {
        life_count--;
        if (life_count <= 0)
        {
            disappear();
        }
	}

    bool isAlive() const
    {
        return life_count > 0;
    }


    ////

    ItemType getDisposeKey() const
    {
        return held_item;
    }

    Point getLocation() const
    {
        return location;
    }

    void setPosition(int x, int y)
    {
        location.setX(x);
        location.setY(y);
        location.setDirection(Direction::STAY);
    }
};
