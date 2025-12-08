#pragma once
#include "Enums.h"
#include "Point.h"
#include "Screen.h"
#include <iostream>

class Switch {
private:
    Point location;
    bool is_active;
    Screen& screen; 
    int room_index;
   

    Switch** linked_switches = nullptr;
    int num_switches = 0;
    int required_value = 0;

public:
    // בנאי שמקבל מיקום ומסך
    Switch(const Point& pos, Screen& the_screen, int the_room_index);

    void draw() const;

    // הפעולה שהשחקן עושה - משנה מצב
    void switchMode();

    
    bool isOn() const 
    { return is_active; }

    Point getLocation() const 
    { return location; }

    void setSwitchLogic(Switch** switches, int num, int code_val);

    bool CodeMatch() const;
};
