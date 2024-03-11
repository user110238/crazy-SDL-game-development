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
                                    break;

                                case SDLK_w:
                                case SDLK_UP: Game.Player.Velocity.y -= constant::PLAYER_VELOCITY; break;
                                case SDLK_s:
                                case SDLK_DOWN: Game.Player.Velocity.y += constant::PLAYER_VELOCITY; break;
                                case SDLK_a:
                                case SDLK_LEFT: Game.Player.Velocity.x -= constant::PLAYER_VELOCITY; break;
                                case SDLK_d:
                                case SDLK_RIGHT: Game.Player.Velocity.x += constant::PLAYER_VELOCITY; break;
                            }
                        }
                        break;
                    case SDL_KEYUP:
                        if (Event.key.repeat == 0)
                        {
                            switch (Event.key.keysym.sym)
                            {
                                case SDLK_w:
                                case SDLK_UP: Game.Player.Velocity.y += constant::PLAYER_VELOCITY; break;
                                case SDLK_s:
                                case SDLK_DOWN: Game.Player.Velocity.y -= constant::PLAYER_VELOCITY; break;
                                case SDLK_a:
                                case SDLK_LEFT: Game.Player.Velocity.x += constant::PLAYER_VELOCITY; break;
                                case SDLK_d:
                                case SDLK_RIGHT: Game.Player.Velocity.x -= constant::PLAYER_VELOCITY; break;
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
                                case SDLK_BACKSPACE:
                                    Game.State = gameState::gameRunning;
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
                                    Game.State = gameState::gameRunning;
                                    Game.Player.Velocity.y = 0;
                                    Game.Player.Velocity.x = 0;
                                    break;
                            }
                        }
                }
            }
    }
}
