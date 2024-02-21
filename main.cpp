#include <iostream>
#include "classes/Game.h"

int main()
{
    //Init random seed
    srand(static_cast<unsigned>(time(nullptr)));

    //Init game object
    Game game;

    //Game loop
    while (game.running())
    {
        game.update();
        game.render();
    }

    //End of app
    return 0;
}