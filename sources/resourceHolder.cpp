#include "resourceHolder.hpp"

#if SAM_XCODE
#include "ResourcePath.hpp"
#else
std::string resourcePath()
{
    return "media/";
}
#endif

ResourceHolder::ResourceHolder()
{
    font.loadFromFile(resourcePath() + "FiraSans-Light.otf");
    icon.loadFromFile(resourcePath() + "icon.jpeg");
    ballSoundBuffer.loadFromFile(resourcePath() + "ball.wav");
    
    music.openFromFile(resourcePath() + "fantasy.ogg");
    music.setVolume(50);
    music.setLoop(true);
    music.play();
}

