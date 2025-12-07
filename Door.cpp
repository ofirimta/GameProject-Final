#include "Door.h"

////////////////////////////////////////////////////////////////


Door::Door(bool if_need_a_key, int my_door_num, Screen& screen)
	: my_screen(screen), need_key(if_need_a_key), num_of_door(my_door_num)
{

}

// i need to configer all doors that i have in main

//////////////////////////////////////////////////////////////////

void Door::openDoor(Player my_player, int room)
{
	door_is_open = 1;

	my_screen.delInventoryAt(my_player, room);
	const char* my_str = "Next_door_is_open,_and_you_can_pass_through.";   //have to add const!!!!!
	my_screen.setMessageAt(room, my_str);
}
/////////////////////////////////////////////////////////////////////////////

void Door::changeRoom(Player& my_character, int& room)   //calling only if door is open!!!!
{
	this->addOneToCounter();   //if player standing on the door 

	static int last_door_pass = 1; //chaking wrong passing  //sarting sri=om 1 because this is the first door!!
	static int count_passes_in_room = 0; //chaking wrong passing  //first player who pass from the room


	if ((this->showCounter()) % 2 == 0)  //if 2 players passed

	{
		my_screen.delMessageAt(room);  //when we pass a room message will delete

		if (room < (this->getNumDoor()))  //because if we pass to next room  door num is more then room index num
		{
			room++;
			my_screen.draw(room);
			///players need show on
		}
		else
		{
			room--;
			my_screen.draw(room);
			///players need show on
		}
		count_passes_in_room = 0;
	}
	else
	{
		if (count_passes_in_room == 0)
		{
			last_door_pass = this->getNumDoor();
			my_character.disappear();   //if just on player pass- he will disappear and screen not change
			count_passes_in_room = 1; //one of player pass from this room
		}

		else if (last_door_pass != (this->getNumDoor()))
		{
			my_screen.delMessageAt(room);
			const char* new_message = "Both_players_must_use_the_same_door_to_proceed.";
			my_screen.setMessageAt(room, new_message);
		}
	}
}