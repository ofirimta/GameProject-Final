#include "Game.h"
#include "Menu.h" 
#include <iostream>
#include <windows.h> // for Sleep


// בנאי
Game::Game() : p1(nullptr), p2(nullptr), active_bomb(nullptr), current_door(nullptr), game_running(false), current_room_index(0)
{
}

// מפרק (Destructor) לשחרור זיכרון
Game::~Game()
{
    if (p1) delete p1;
    if (p2) delete p2;
    if (active_bomb) delete active_bomb;
    if (current_door) delete current_door;
}

void Game::run()
{
    bool exit_program = false;
    Menu game_menu; // יצירת אובייקט התפריט

    while (!exit_program)
    {
        // ציור התפריט הראשי
        game_menu.draw(0);

        // קבלת בחירה מהמשתמש (הפונקציה במחלקה Menu מטפלת ב-8 להוראות פנימית)
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

                if (!game_running) break; // יציאה אם לחצו ESC ואז 9

                // 2. תזוזת שחקנים
                p1->move();
                if (p2->isAlive()) p2->draw(); //תיקון באג עלייה אחד על השני
                p2->move();
                if (p1->isAlive()) p1->draw();

                // 3. עדכון פצצה (טיימר ופיצוץ)
                if (active_bomb) {
                    active_bomb->update(*p1, *p2);
                }

                // 4. בדיקת ניצחון/סיום שלב
                if (p1->isFinished() && p2->isFinished())
                {
                    if (current_room_index < SCREENS - 1)
                    {
                        current_room_index++;
                        Sleep(500);
                        initLevel(current_room_index); // טעינת השלב הבא
                    }
                    else
                    {
                        // סיום המשחק כולו
                        cls();
                        gotoxy(10, 10);
                        cout << "CONGRATULATIONS! YOU FINISHED THE GAME!";
                        Sleep(3000);
                        game_running = false; // חזרה לתפריט
                    }
                }

                Sleep(200); // שליטה בקצב המשחק
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

    // יצירת האובייקטים
    Point bomb_pos(0, 0, 0, 5, '@'); // מיקום התחלתי לא משנה, זה יתעדכן כשהשחקן יזרוק
    active_bomb = new Bomb(bomb_pos, screen);

    // יצירת דלת (מספר 1)
    current_door = new Door(true, 1, screen);

    // יצירת שחקנים (מיקום התחלתי זמני, יעודכן ב-initLevel)
    Point dummy_pos(1, 1, 0, 0, ' ');
    p1 = new Player(dummy_pos, keys_p1, screen, '$', *active_bomb, current_room_index, current_door);
    p2 = new Player(dummy_pos, keys_p2, screen, '&', *active_bomb, current_room_index, current_door);

    // אתחול השלב הראשון
    initLevel(current_room_index);

    game_running = true;
}

void Game::initLevel(int level)
{
    // 1. ציור המפה
    screen.draw(level);

    int p1_x = 5, p1_y = 10;
    int p2_x = 7, p2_y = 10;

    switch (level) { //איפה להוליד את השחקנים בכל שלב ותיקון APPEAR DISAPPEAR
    case 0: // שלב ראשון
        p1_x = 24; p1_y = 10;
        p2_x = 23; p2_y = 10;
        break;
    case 1: // שלב שני
        p1_x = 53; p1_y = 18;
        p2_x = 52; p2_y = 15;
        break;
    case 2: // שלב שלישי
        p1_x = 35; p1_y = 10;
        p2_x = 37; p2_y = 10;
        break;
    }

    // עדכון מיקום ושרטוט השחקנים
    p1->setPosition(p1_x, p1_y);
    p2->setPosition(p2_x, p2_y);

    p1->appear();
    p2->appear();

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
        else if (key == -32) 
        {
            _getch();
        }
        else
        {
            // שליחת המקש לשני השחקנים - כל אחד יגיב רק למקשים שלו
            p1->handleKeyPressed(key);
            p2->handleKeyPressed(key);
        }
    }
}

void Game::pauseGame()
{
    // הצגת הודעת הפסקה בשורה תחתונה (מתחת למסך המשחק)
    gotoxy(0, MAX_Y + 1);
    cout << "Game Paused. Press ESC to continue or '9' to exit to menu.";

    while (true)
    {
        if (_kbhit())
        {
            char key = _getch();
            if (key == 27) // ESC - חזרה למשחק
            {
                // מחיקת ההודעה
                gotoxy(0, MAX_Y + 1);
                cout << "                                                           ";
                return;
            }
            if (key == '9') // יציאה לתפריט
            {
                game_running = false;
                return;
            }
        }
    }
}