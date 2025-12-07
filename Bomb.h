#pragma once

#include "Point.h"
#include "Screen.h"
class Player;


class Bomb {
private:
    Point location;
    int countdown = 5;      // טיימר (מתחיל ב-5 מחזורי משחק בעצם כל סיבוב במיין)
    bool is_active = false;
    int room_index = 0;
    Screen& s;


public:
	
	Bomb(const Point& p, Screen& screen) :location(p), s(screen), countdown(5), is_active(false), room_index(0)
    {
        location.setChar(BOMB_CHAR); // '@'
    }

    void draw() const
    {
        location.draw();
    }

	void activate(const Point& drop_location, int room); //activate the bomb at position (x,y)

    void update(Player& p1, Player& p2); // למימוש במיין!! כל סיבוב

    bool isActive() const { return is_active; }
    Point getLocation() const { return location; }

private:
    void explode(Player& p1, Player& p2);
};

