#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include <math.h>
#include <stdio.h>
#include <ctime>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>

#include "include/namespaces.h"
#include "include/window.h"
#include "include/math.h"

#include "include/texture_loading.h"
#include "include/events.h"
#include "include/frame_limiting.h"

#include "include/forest.h"
#include "include/river.h"

#include "include/player.h"

#include "include/entity.h"
#include "include/enemy.h"
#include "include/allies.h"

#include "include/background.h"
#include "include/text.h"

#include "include/game.h"
#include "include/render.h"

#include "include/entity_logic.h"
#include "include/main.h"

int main(int argc, char* args[])
{
    Game Game;
    setup( Game );
    gameLoop( Game );

    return 0;
}
