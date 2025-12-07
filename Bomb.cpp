#include "Bomb.h"
#include "Player.h"

void Bomb::activate(const Point& drop_location, int room)
{
    location.setX(drop_location.getX());
    location.setY(drop_location.getY());

	room_index = room;
    is_active = true;
    countdown = 5; // 5 game loops until explosion
    location.draw();
}

void Bomb::update(Player& p1, Player& p2) { //*
    if (!is_active) //if the bomb is not active, do nothing
    {
        return;
    }

    if (countdown > 0) // every game loop, decrease countdown
    {
        countdown--;
    }

    if (countdown == 0)
    {
        explode(p1, p2); //boom!
        is_active = false; // the bomb is no longer active
    }
}

void Bomb::explode(Player& p1, Player& p2)
{
    location.draw(' '); // erase the bomb from the screen
    Point current_pos = location;
    current_pos.setChar(' ');
    s.setCharAt(current_pos, room_index);

    for (int y = -3; y <= 3; y++) {
        for (int x = -3; x <= 3; x++) {

            Point target_pos = location;
            target_pos.setX(location.getX() + x);
            target_pos.setY(location.getY() + y);

            // Check bounds
            if (target_pos.getX() < 0 || target_pos.getX() >= MAX_X ||
                target_pos.getY() < 0 || target_pos.getY() >= MAX_Y)
            {
                continue;
            }

            if (p1.isAlive() && p1.getCurrentRoomIndex() == room_index &&
                p1.getLocation().getX() == target_pos.getX() &&
                p1.getLocation().getY() == target_pos.getY())
            {
                p1.hitByBomb();
                s.setHealthAt(p1, room_index); 
            }

            if (p2.isAlive() && p2.getCurrentRoomIndex() == room_index &&
                p2.getLocation().getX() == target_pos.getX() &&
                p2.getLocation().getY() == target_pos.getY())
            {
                p2.hitByBomb();
                s.setHealthAt(p2, room_index); // עדכון מיידי של הלבבות במסך
            }

            if (x == 0 && y == 0) { // the bomb's own position
                continue;
            }

            char char_at_target = s.getCharAt(target_pos, room_index);
            //not destroy:

            if (char_at_target == ' ') { // nothing to destroy. 
                continue;
            }

            if (tolower(char_at_target) == tolower(IMMUTABLE_WALL_CHAR)) {
                continue;
            }

            if (isdigit(char_at_target)) {
                continue;
            }


            //for now, nothing to destroy.  LATER WE WILL CHANGE THEY CAN BE DESTROYED

            if (char_at_target == SWITCH_ON_CHAR || char_at_target == SWITCH_OFF_CHAR) {
                continue;
            }

            if (char_at_target == KEY_CHAR) {
                continue;
            }

            if (char_at_target == RIDDLE_CHAR) {
                continue;
            }

        
            target_pos.setChar(' ');
            s.setCharAt(target_pos, room_index);
            target_pos.draw(' ');

        }
    }

}