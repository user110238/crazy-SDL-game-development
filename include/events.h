 void eventHandler ( bool& state, Player& player )
 {

     SDL_Event Event;

     while (SDL_PollEvent(&Event))
        {
            switch (Event.type)
            {
                case SDL_QUIT:
                    state = false;
                    break;
                case SDL_KEYDOWN:
                    if (Event.key.repeat == 0)
                    {
                        switch (Event.key.keysym.sym)
                        {
                            case SDLK_UP: player.Velocity.y -= constant::PLAYER_VELOCITY; break;
                            case SDLK_DOWN: player.Velocity.y += constant::PLAYER_VELOCITY; break;
                            case SDLK_LEFT: player.Velocity.x -= constant::PLAYER_VELOCITY; break;
                            case SDLK_RIGHT: player.Velocity.x += constant::PLAYER_VELOCITY; break;

                            case SDLK_ESCAPE: state = false; break;
                        }
                    }
                    break;
                case SDL_KEYUP:
                    if (Event.key.repeat == 0)
                    {
                        switch (Event.key.keysym.sym)
                        {
                            case SDLK_UP: player.Velocity.y += constant::PLAYER_VELOCITY; break;
                            case SDLK_DOWN: player.Velocity.y -= constant::PLAYER_VELOCITY; break;
                            case SDLK_LEFT: player.Velocity.x += constant::PLAYER_VELOCITY; break;
                            case SDLK_RIGHT: player.Velocity.x -= constant::PLAYER_VELOCITY; break;
                        }
                    }
                    break;
            }
        }

}
