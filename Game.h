#pragma once
#include "Screen.h"
#include "Player.h"
#include "Bomb.h"
#include "Door.h"
#include "Switch.h"
#include "Menu.h"

class Game {
private:
	Screen screen;

	// מצביעים (Pointers) לאובייקטים הדינאמיים
	Player* p1;
	Player* p2;
	Bomb* active_bomb;
	Door* current_door;
	Switch* active_switch;

	int current_room_index;
	bool game_running;

	// הגדרת המקשים כשדות במחלקה
	const char keys_p1[7] = "wdxase";
	const char keys_p2[7] = "ilmjko";

public:
	Game();
	~Game(); // Destructor - חיוני לשחרור הזיכרון
	void run();

private:
	void initGame();
	void initLevel(int level);
	void handleInput();
	void pauseGame();
};