class Texture
{

    SDL_Texture *_texture;
    int Width;
    int Height;


    public:

    Texture();
    ~Texture();

    void loadFromFile( std::string path );

};

void Texture::loadFromFile( std::string path )
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    newTexture = SDL_CreateTextureFromSurface( _renderer, loadedSurface );



}
