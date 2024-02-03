
Player* player;

Game::Game()
{
    _window = nullptr;
    _renderer = nullptr;
    _surface = nullptr;

    _screen_width = 1600;
    _screen_height = 900;

    _game_running = true;

    Player player;

}

Game::~Game()
{

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();

}

void Game::run()
{

    init( NULL , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screen_width, _screen_height, SDL_WINDOW_SHOWN);

    gameLoop();

}

void Game::init(const char* title, int x, int y, int w, int h, Uint32 flags)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow(title, x, y, w, h, flags);
    _renderer = SDL_CreateRenderer(_window, -1, 0);
    _surface = SDL_GetWindowSurface( _window );

    player = new Player();

}

void Game::gameLoop()
{
    while ( _game_running == 1 )
    {

        handleEvents();
        render();

    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);

    SDL_RenderClear(_renderer);

    SDL_RenderPresent(_renderer);
}

void Game::handleEvents()
{
    SDL_Event e;
    SDL_PollEvent(&e);

    const Uint8* keyboard = SDL_GetKeyboardState(nullptr);

    if (keyboard[SDL_SCANCODE_ESCAPE])
    {
        _game_running = 0;
    }

    switch (e.type)
    {
        player.handleEvent( e );

        case SDL_QUIT:
            _game_running = 0;
            break;
    }
}
