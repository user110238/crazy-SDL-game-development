bool endGame()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_ESCAPE ] )
        return 0;
    return 1;
}

SDL_Point eventHandlerPlayer ( SDL_Point Velocity )
 {

     SDL_Event Event;
     while (SDL_PollEvent(&Event))
        {
            switch (Event.type)
            {
                case SDL_KEYDOWN:
                    if (Event.key.repeat == 0)
                    {
                        switch (Event.key.keysym.sym)
                        {
                            case SDLK_UP: Velocity.y -= constant::PLAYER_VELOCITY; break;
                            case SDLK_DOWN: Velocity.y += constant::PLAYER_VELOCITY; break;
                            case SDLK_LEFT: Velocity.x -= constant::PLAYER_VELOCITY; break;
                            case SDLK_RIGHT: Velocity.x += constant::PLAYER_VELOCITY; break;
                        }
                    }
                    break;
                case SDL_KEYUP:
                    if (Event.key.repeat == 0)
                    {
                        switch (Event.key.keysym.sym)
                        {
                            case SDLK_UP: Velocity.y += constant::PLAYER_VELOCITY; break;
                            case SDLK_DOWN: Velocity.y -= constant::PLAYER_VELOCITY; break;
                            case SDLK_LEFT: Velocity.x += constant::PLAYER_VELOCITY; break;
                            case SDLK_RIGHT: Velocity.x -= constant::PLAYER_VELOCITY; break;
                        }
                    }
                    break;
            }
        }

     return Velocity;

}
