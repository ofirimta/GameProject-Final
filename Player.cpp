#include "Player.h"
#include "Door.h"

///////////////////////////////////////////////////////////////////

Player::Player(const Point& point, const char(&the_keys)[NUM_KEYS + 1], Screen& theScreen, char symbol, Bomb& bomb_ref, int& current_room, Door* current_room_door, Switch* switch_obj)
	: location(point), screen(theScreen), character(symbol), active_bomb(bomb_ref), pDoor(current_room_door), current_room_index(current_room), pSwitch(switch_obj)
{

	memcpy(keys, the_keys, NUM_KEYS * sizeof(keys[0]));
	location.setChar(symbol);
	setHeldItem(ItemType::NONE);
}
/////////////////////////////////////////////////////////////////

void Player::draw()
{
	if (!is_finished_level) // draw only if the player has not finished the level
	{
		location.draw();
	}
}

/////////////////////////////////////////////////////////////////

void Player::handleKeyPressed(char key_pressed)
{
	size_t index = 0;
	//KEYS = UP, RIGHT, DOWN, LEFT, STAY
	for (char k : keys)
	{
		if (tolower(k) == tolower(key_pressed)) {

			if (index < MOVE_KEYS_COUNT)
			{
				location.setDirection((Direction)index);
			}
			else
			{
				disposeItem();
			}
			return;
		}
		++index;
	}
}
/////////////////////////////////////////////////////////////////////


void Player::handleCollision(int component_char)
{
	Point next_pos = location.nextPos();
	switch (component_char)
	{

	case WALL_CHAR:
	case IMMUTABLE_WALL_CHAR:
		location.setDirection(Direction::STAY);
		break;

	case SWITCH_ON_CHAR:
	case SWITCH_OFF_CHAR:
		pSwitch->switchMode();
		break;

	case RIDDLE_CHAR: // (?)

		location.setDirection(Direction::STAY);
		break;

	case BOMB_CHAR: // (@)
		if (active_bomb.isActive())
		{
			return;
		}

		if (getHeldItem() != ItemType::NONE)
		{
			disposeItem();
		}
		
		setHeldItem(ItemType::BOMB);
		screen.setInventoryAt(*this, current_room_index);
		next_pos.setChar(' ');
		screen.setCharAt(next_pos, current_room_index);
		break;

	case KEY_CHAR:  // (K)

		if (getHeldItem() != ItemType::NONE)
		{
			disposeItem();
		}

		setHeldItem(ItemType::KEY);
		pDoor->setThisKey(1);
		screen.setInventoryAt(*this, current_room_index);

		next_pos.setChar(' ');
		screen.setCharAt(next_pos, current_room_index);
		
		break;


	default:
		// unhandled object - do nothing
		break;
	}
}

/////////////////////////////////////////////////////////////////////////

void Player::handleDoor(char char_on_screen)
{
		if (pDoor->isDoorOpen()) //if the door is open
		{
			location.draw(char_under_player);
			char_under_player = char_on_screen;
			location.move();
			location.draw();

			std::cout.flush();
		

			pDoor->changeRoom(*this, current_room_index);
			char_under_player = ' ';
			return;
		}

		else if (getHeldItem() == ItemType::KEY && (pDoor->itsAMatch()) == 1)
		{
			pDoor->openDoor(*this, current_room_index);//to be update
			setHeldItem(ItemType::NONE);
			screen.delInventoryAt(*this, current_room_index);

			location.draw(char_under_player);
			char_under_player = char_on_screen;
			location.move();
			location.draw();

			cout.flush();
			Sleep(400);

			pDoor->changeRoom(*this, current_room_index);
			char_under_player = ' ';
			return;
		}
		else
		{
			location.setDirection(Direction::STAY);
			return;
		}
	
}
//////////////////////////////////////////////////////////////////////

void Player::setHeldItem(ItemType type)
	{
		this->held_item = type;
	}
	/////////////////////////////////////////////////////////////////////////

void Player::disposeItem()
{
	if (getHeldItem() == ItemType::NONE)
	{
		return; // the player is not holding any item
	}

	Point drop_location = location.prevPos();
	char disposed_char = ' ';

	switch (held_item)
	{
	case ItemType::BOMB:
		active_bomb.activate(drop_location, current_room_index);
		disposed_char = BOMB_CHAR; // '@'
		break;

	case ItemType::KEY:
		disposed_char = KEY_CHAR; // 'K'

		//עדכון הדלת שהמפתח כבר לא מוחזק
		if (pDoor != nullptr) {
			pDoor->setThisKey(false);
		}
		break;

	default:
		break;
	}

	if (disposed_char != ' ')
	{
		drop_location.setChar(disposed_char);
		screen.setCharAt(drop_location, current_room_index);
		drop_location.draw();
	}

	screen.delInventoryAt(*this, current_room_index);
	setHeldItem(ItemType::NONE);


}
	///////////////////////////////////////////////////////////////////////////

void Player::move()
	{
		if (is_finished_level)
		{
			location.setDirection(Direction::STAY);
			return;
		}

		Point next_pos = location.nextPos();

		char char_on_screen = screen.getCharAt(next_pos, current_room_index);

		if (isdigit(char_on_screen))
		{
			handleDoor(char_on_screen);
			return;
		}

		handleCollision(char_on_screen);

		char updated_char_at_dest = screen.getCharAt(next_pos, current_room_index);

		if (location.getdiffX() != 0 || location.getdiffY() != 0) //if there is a movement - כדי שהשחקן לא ירצד על המקום
		{
			location.draw(char_under_player);
			if (updated_char_at_dest == SWITCH_ON_CHAR || updated_char_at_dest == SWITCH_OFF_CHAR)
			{
				char_under_player = updated_char_at_dest;
			}
			else
			{
				char_under_player = ' ';
			}
			location.move();	
			location.draw();
		}
	}

	/////UPDATES////

void Player::disappear()
	{
		char background_char = screen.getCharAt(location, current_room_index);
		location.draw(background_char);
		this->is_finished_level = true;

	}

void Player::appear()
{
	this->is_finished_level = false;
	location.draw();
}

void Player::resetLevelpos(int x, int y)
{
	location.setX(x);
	location.setY(y);
	location.setDirection(Direction::STAY);

	char_under_player = screen.getCharAt(location, current_room_index);
	appear();
}

