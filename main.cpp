#include "Game.h"
#include "utils.h"

int main()
{
    hideCursor(); // מעלים את הסמן המהבהב לתצוגה נקייה יותר

    Game game;
    game.run();

    return 0;
}