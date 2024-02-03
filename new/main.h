



void init( SDL_Window* window , SDL_Renderer* renderer , SDL_Surface* surface , int w , int h )
{

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow( NULL , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , w , h , SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer(window, -1, 0);
    surface = SDL_GetWindowSurface( window );


}
