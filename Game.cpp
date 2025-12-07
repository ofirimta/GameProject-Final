#include "Game.h"
#include <iostream>
#include <windows.h> // for Sleep

// בנאי
Game::Game() : p1(nullptr), p2(nullptr), active_bomb(nullptr), current_door(nullptr), active_switch(nullptr), game_running(false), current_room_index(0)
{
}

// מפרק (Destructor) לשחרור זיכרון בסוף המשחק
Game::~Game()
{
    if (p1) delete p1;
    if (p2) delete p2;
    if (active_bomb) delete active_bomb;
    if (current_door) delete current_door;
    if (active_switch) delete active_switch;
}

void Game::run()
{
    bool exit_program = false;
    Menu game_menu;

    while (!exit_program)
    {
        // ציור התפריט הראשי
        game_menu.draw(0);

        // קבלת בחירה מהמשתמש
        int choice = game_menu.user_choice();

        switch (choice)
        {
        case 1: // התחלת משחק חדש
            initGame();

            // לולאת המשחק (Game Loop)
            while (game_running)
            {
                // 1. קלט מהמשתמש
                handleInput();

                if (!game_running) break; // יציאה אם ביקשו לצאת

                // 2. תזוזת שחקנים + תיקון מחיקה ויזואלית
                // התיקון: אחרי ששחקן אחד זז, אנחנו מציירים את השני בכוח
                // למקרה שהראשון "דרס" אותו ויזואלית.

                p1->move();
                if (p2->isAlive()) p2->draw();

                p2->move();
                if (p1->isAlive()) p1->draw();

                // 3. עדכון פצצה
                if (active_bomb)
                {
                    active_bomb->update(*p1, *p2);
                }

                // 4. בדיקת מעבר שלב
                // בודקים אם current_room_index השתנה.
                // השינוי קורה בתוך Player -> Door -> משנה את המשתנה ב-Reference
                static int last_frame_room = current_room_index;

                if (current_room_index != last_frame_room)
                {
                    // זיהינו מעבר חדר!
                    if (current_room_index < SCREENS) // בדיקת גבולות
                    {
                        Sleep(400); // השהייה קטנה למעבר חלק
                        initLevel(current_room_index); // טעינת השלב החדש
                        last_frame_room = current_room_index;
                    }
                }

                // בדיקת סיום משחק (אם הגענו למסך האחרון)
                if (current_room_index == SCREENS - 1 && p1->isFinished() && p2->isFinished())
                {
                    // סיום המשחק כולו (ניצחון)
                    cls();
                    gotoxy(10, 10);
                    cout << "CONGRATULATIONS! YOU FINISHED THE GAME!";
                    Sleep(3000);
                    game_running = false; // חזרה לתפריט
                }

                Sleep(100); // קצב המשחק
            }
            break;

        case 9: // יציאה מהתוכנית
            exit_program = true;
            break;
        }
    }

    cls();
    gotoxy(0, 0);
    cout << "Goodbye!" << endl;
}

void Game::initGame()
{
    current_room_index = 0;

    // ניקוי שאריות ממשחק קודם אם יש
    if (p1) { delete p1; p1 = nullptr; }
    if (p2) { delete p2; p2 = nullptr; }
    if (active_bomb) { delete active_bomb; active_bomb = nullptr; }
    if (current_door) { delete current_door; current_door = nullptr; }
    if (active_switch) { delete active_switch; active_switch = nullptr; }

    // יצירת האובייקטים
    Point bomb_pos(0, 0, 0, 5, '@');
    active_bomb = new Bomb(bomb_pos, screen);

    // יצירת דלת ומתג ראשוניים (יוחלפו מיד ב-initLevel)
    current_door = new Door(true, 1, screen);
    Point switch_pos(1, 1, 0, 0, '?');
    active_switch = new Switch(switch_pos, screen, current_room_index);

    // יצירת שחקנים
    Point dummy_pos(1, 1, 0, 0, ' ');
    p1 = new Player(dummy_pos, keys_p1, screen, '$', *active_bomb, current_room_index, current_door, active_switch);
    p2 = new Player(dummy_pos, keys_p2, screen, '&', *active_bomb, current_room_index, current_door, active_switch);

    // טעינת הנתונים האמיתיים של שלב 0
    initLevel(current_room_index);

    game_running = true;
}

void Game::initLevel(int level)
{
    // 1. ניהול דלתות ומתגים לכל שלב (מוחקים ישן ויוצרים חדש)
    if (current_door) delete current_door;
    if (active_switch) delete active_switch;

    // הגדרות ספציפיות לכל שלב (מיקומי מתגים, מספרי דלתות)
    bool need_key = true;
    int door_num = 1;
    Point switch_p(0, 0, 0, 0, ' ');

    if (level == 0) { // חדר 1
        door_num = 1;
        switch_p = Point(75, 20, 0, 0, '\\');
    }
    else if (level == 1) { // חדר 2
        door_num = 2;
        switch_p = Point(40, 8, 0, 0, '\\');
    }
    else { // חדר סיום (לא משנה כרגע)
        need_key = false;
        door_num = 99;
    }

    current_door = new Door(need_key, door_num, screen);
    active_switch = new Switch(switch_p, screen, level);

    // 2. עדכון השחקנים באובייקטים החדשים (קריטי!!)
    p1->setDoor(current_door);
    p1->setSwitch(active_switch);
    p2->setDoor(current_door);
    p2->setSwitch(active_switch);

    // 3. ציור המפה והאובייקטים
    // הערה: אם הדלת כבר ציירה את המפה ב-changeRoom, הציור הזה "יחזק" את זה.
    screen.draw(level);
    if (level < 2) active_switch->draw(); // ציור המתג

    // 4. קביעת מיקום התחלתי לשחקנים (Spawn Points)
    int p1_x = 5, p1_y = 10;
    int p2_x = 7, p2_y = 10;

    switch (level) {
    case 0: // שלב ראשון
        p1_x = 5; p1_y = 5;
        p2_x = 7; p2_y = 5;
        break;
    case 1: // שלב שני - מיקום חדש!
        p1_x = 2; p1_y = 20; // שיניתי שיהיה בטוח בתוך הקירות של שלב 2
        p2_x = 3; p2_y = 20;
        break;
    case 2: // שלב שלישי
        p1_x = 35; p1_y = 10;
        p2_x = 37; p2_y = 10;
      
        break;
    }

    // איפוס ויזואלי ולוגי של השחקנים למיקום החדש
    p1->resetLevelpos(p1_x, p1_y);
    p2->resetLevelpos(p2_x, p2_y);

    // עדכון תצוגה עליונה (חיים, חפצים)
    screen.setHealthAt(*p1, level);
    screen.setHealthAt(*p2, level);
    screen.setInventoryAt(*p1, level);
    screen.setInventoryAt(*p2, level);
}

void Game::handleInput()
{
    if (_kbhit())
    {
        char key = _getch();

        if (key == 27) // ESC
        {
            pauseGame();
        }
        else if (key == -32) // מקשים מיוחדים
        {
            _getch();
        }
        else
        {
            // שליחת המקש לשני השחקנים
            p1->handleKeyPressed(key);
            p2->handleKeyPressed(key);
        }
    }
}

void Game::pauseGame()
{
    gotoxy(0, MAX_Y + 1);
    cout << "Game Paused. Press ESC to continue or '9' to exit to menu.";

    while (true)
    {
        if (_kbhit())
        {
            char key = _getch();
            if (key == 27) // ESC - חזרה
            {
                gotoxy(0, MAX_Y + 1);
                cout << "                                                      ";
                return;
            }
            if (key == '9') // יציאה
            {
                game_running = false;
                return;
            }
        }
    }
}