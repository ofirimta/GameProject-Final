#include "Switch.h"

Switch::Switch(const Point& pos, Screen& the_screen, int the_room_index)
    : location(pos), screen(the_screen), is_active(false), room_index(the_room_index)
{
    location.setChar(SWITCH_OFF_CHAR);
}

void Switch::draw() const
{
    location.draw(); 
}

void Switch::switchMode()
{
    is_active = !is_active;
    char new_char; 

    if (is_active) 
    {
        new_char = SWITCH_ON_CHAR;
    }
    else 
    {
        new_char = SWITCH_OFF_CHAR;
    }

    location.setChar(new_char);
    draw();
    screen.setCharAt(location, room_index);
    
}

void Switch::setSwitchLogic(Switch** switches, int num, int code_val)
{
    linked_switches = switches;
    num_switches = num;
    required_value = code_val;
}

bool Switch::CodeMatch() const
{
    if (linked_switches != nullptr && num_switches > 0)
    {
        int current_sum = 0;

        for (int i = 0; i < num_switches; i++)
        {
            if (linked_switches[i]->isOn())
            {
                current_sum = current_sum + (int)pow(2, i);
            }
        }

        if (current_sum != required_value)
        {
            return false;
        }
    }
	return true;
}