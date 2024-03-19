enum gameState
{
    startUp,

    gameRunning,
    gamePause,

    mainMenuRunning,

    saved,
    loaded,

    endGame
};

enum buttonState
{
    play,
    resume,

    menu,

    save,
    load,

    quit,

    nothing
};

struct Game
{
    gameState State;
    buttonState Button;

    structWindow Window;

    Entity Player;
    SDL_Point movePlayerBy;
    int controllable;

    AllEntities Entities;

    std::vector<std::vector <Tile> > Forest;
    std::vector<std::pair< int , int >> CampCoordinates;
    structFireSpread FireSpread;

    structBackground Background;
    structText Text;

    FrameLimit Frames;

};
