struct FrameLimit
{
    int FPS;
    int FrameDelay;
    Uint32 FrameStart;
    int FrameTime;
};

void setFrameLimit ( FrameLimit& Frames , int x )
{
    Frames.FPS = x;
    Frames.FrameDelay = 1000 / Frames.FPS;
}
