#pragma once

#include "Screen.h"
#include "Player.h"
#include "Bomb.h"
#include "Door.h"
#include "Menu.h"

class Game {
private:
    Screen screen;
    Player* p1 = nullptr;
    Player* p2 = nullptr;
    Bomb* active_bomb = nullptr;
    Door* current_door = nullptr;

    bool game_running = false;
    int current_room_index = 0;

    // הגדרת מקשים לפי דרישות התרגיל (PDF)
    // Order: UP, RIGHT, DOWN, LEFT, STAY, DISPOSE

    // Player 1 (Left user): w, d, x, a, s, e
    const char keys_p1[NUM_KEYS + 1] = "wdxase";

    // Player 2 (Right user): i, l, m, j, k, o
    const char keys_p2[NUM_KEYS + 1] = "ilmjko";

public:
    Game();
    ~Game();

    void run(); // הפונקציה הראשית שמריצה את הלולאה והתפריט

private:
    void initGame();           // איתחול משחק חדש (יוצר אובייקטים)
    void initLevel(int level); // טעינת שלב ספציפי (מיקומים וציור)
    void handleInput();        // בדיקת קלט מהמשתמש
    void pauseGame();          // מסך השהייה
};