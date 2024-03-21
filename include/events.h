void eventHandler( Game& Game )
{

    SDL_Event Event;

    while (SDL_PollEvent(&Event))
        {
            if ( Game.State == gameState::gameRunning )
            {
                switch (Event.type)
                {
                    case SDL_QUIT:
                        Game.State = gameState::endGame;
                        break;
                    case SDL_KEYDOWN:
                        if (Event.key.repeat == 0)
                        {
                            switch (Event.key.keysym.sym)
                            {
                                case SDLK_ESCAPE:
                                    Game.State = gameState::gamePause;
                                    Game.Button = buttonState::resume;
                                    break;
                                case SDLK_TAB:
                                    Game.controllable = Game.controllable + 1;
                                    if ( Game.controllable >= Game.Entities.Allies.size() )
                                        Game.controllable = 0;
                                    break;

                                case SDLK_w:
                                case SDLK_UP: Game.movePlayerBy.y -= constant::PLAYER_VELOCITY; break;
                                case SDLK_s:
                                case SDLK_DOWN: Game.movePlayerBy.y += constant::PLAYER_VELOCITY; break;
                                case SDLK_a:
                                case SDLK_LEFT: Game.movePlayerBy.x -= constant::PLAYER_VELOCITY; break;
                                case SDLK_d:
                                case SDLK_RIGHT: Game.movePlayerBy.x += constant::PLAYER_VELOCITY; break;
                            }
                        }
                        break;
                    case SDL_KEYUP:
                        if (Event.key.repeat == 0)
                        {
                            switch (Event.key.keysym.sym)
                            {
                                case SDLK_w:
                                case SDLK_UP: Game.movePlayerBy.y += constant::PLAYER_VELOCITY; break;
                                case SDLK_s:
                                case SDLK_DOWN: Game.movePlayerBy.y -= constant::PLAYER_VELOCITY; break;
                                case SDLK_a:
                                case SDLK_LEFT: Game.movePlayerBy.x += constant::PLAYER_VELOCITY; break;
                                case SDLK_d:
                                case SDLK_RIGHT: Game.movePlayerBy.x -= constant::PLAYER_VELOCITY; break;
                            }
                        }
                    break;
                }
            }
            else if ( Game.State == gameState::gameReplaying )
            {
                switch (Event.type)
                {
                    case SDL_QUIT:
                        Game.State = gameState::endGame;
                        break;
                    case SDL_KEYDOWN:
                        if (Event.key.repeat == 0)
                        {
                            switch (Event.key.keysym.sym)
                            {
                                case SDLK_ESCAPE:
                                    Game.State = gameState::gamePause;
                                    Game.Button = buttonState::resume;
                                    break;
                                case SDLK_TAB:
                                    Game.controllable = Game.controllable + 1;
                                    if ( Game.controllable >= Game.Entities.Allies.size() )
                                        Game.controllable = 0;
                                    break;
                            }
                        }
                        break;
                }
            }
            else if ( Game.State == gameState::mainMenuRunning )
            {
                switch (Event.type)
                {
                    case SDL_QUIT:
                        Game.State = gameState::endGame;
                        break;
                    case SDL_KEYDOWN:
                        if (Event.key.repeat == 0)
                        {
                            switch (Event.key.keysym.sym)
                            {
                                case SDLK_RETURN:
                                    switch( Game.Button )
                                    {
                                        case buttonState::play:
                                            Game.State = gameState::gameRunning;
                                            Game.movePlayerBy.y = 0;
                                            Game.movePlayerBy.x = 0;
                                            break;
                                        case buttonState::save:
                                            Game.State = gameState::saved;
                                            break;
                                        case buttonState::load:
                                            Game.State = gameState::loaded;
                                            break;
                                        case buttonState::quit:
                                            Game.State = gameState::endGame;
                                            break;
                                    }
                                    break;
                                case SDLK_DOWN:
                                    switch( Game.Button )
                                    {
                                        case buttonState::play:
                                            Game.Button = buttonState::save;
                                            break;
                                        case buttonState::save:
                                            Game.Button = buttonState::load;
                                            break;
                                        case buttonState::load:
                                            Game.Button = buttonState::quit;
                                            break;
                                        case buttonState::quit:
                                            Game.Button = buttonState::play;
                                            break;
                                    }
                                    break;
                                case SDLK_UP:
                                    switch( Game.Button )
                                    {
                                        case buttonState::play:
                                            Game.Button = buttonState::quit;
                                            break;
                                        case buttonState::save:
                                            Game.Button = buttonState::play;
                                            break;
                                        case buttonState::load:
                                            Game.Button = buttonState::save;
                                            break;
                                        case buttonState::quit:
                                            Game.Button = buttonState::load;
                                            break;
                                    }
                                    break;
                            }
                        }
                }
            }
            else if ( Game.State == gameState::gamePause )
            {
                switch (Event.type)
                {
                    case SDL_QUIT:
                        Game.State = gameState::endGame;
                        break;
                    case SDL_KEYDOWN:
                        if (Event.key.repeat == 0)
                        {
                            switch (Event.key.keysym.sym)
                            {
                                case SDLK_ESCAPE:
                                    Game.State = gameState::endGame;
                                    break;
                                case SDLK_RETURN:
                                    switch( Game.Button )
                                    {
                                        case buttonState::resume:
                                            Game.State = gameState::gameRunning;
                                            Game.movePlayerBy.y = 0;
                                            Game.movePlayerBy.x = 0;
                                            break;
                                        case buttonState::replay:
                                            Game.State = gameState::reSetup;
                                            break;
                                        case buttonState::menu:
                                            Game.State = gameState::mainMenuRunning;
                                            Game.Button = buttonState::play;
                                            break;
                                    }
                                    break;
                                case SDLK_DOWN:
                                    switch( Game.Button )
                                    {
                                        case buttonState::resume:
                                            Game.Button = buttonState::replay;
                                            break;
                                        case buttonState::replay:
                                            Game.Button = buttonState::menu;
                                            break;
                                        case buttonState::menu:
                                            Game.Button = buttonState::resume;
                                            break;
                                    }
                                    break;
                                case SDLK_UP:
                                    switch( Game.Button )
                                    {
                                        case buttonState::resume:
                                            Game.Button = buttonState::menu;
                                            break;
                                        case buttonState::replay:
                                            Game.Button = buttonState::resume;
                                            break;
                                        case buttonState::menu:
                                            Game.Button = buttonState::replay;
                                            break;
                                    }
                                    break;
                            }
                        }
                }
            }
            else if ( Game.State == gameState::saved )
            {
                switch (Event.type)
                {
                    case SDL_QUIT:
                        Game.State = gameState::endGame;
                        break;
                    case SDL_KEYDOWN:
                        if (Event.key.repeat == 0)
                        {
                            switch (Event.key.keysym.sym)
                            {
                                case SDLK_ESCAPE:
                                    Game.State = gameState::mainMenuRunning;
                                    break;
                            }
                        }
                }
            }
            else if ( Game.State == gameState::loaded )
            {
                switch (Event.type)
                {
                    case SDL_QUIT:
                        Game.State = gameState::endGame;
                        break;
                    case SDL_KEYDOWN:
                        if (Event.key.repeat == 0)
                        {
                            switch (Event.key.keysym.sym)
                            {
                                case SDLK_ESCAPE:
                                    Game.State = gameState::mainMenuRunning;
                                    break;
                            }
                        }
                }
            }

    }
}
