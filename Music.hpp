//
// Created by cameronearle on 2/25/18.
//

#ifndef CARTDS_MUSIC_HPP
#define CARTDS_MUSIC_HPP


#include <string>
#include <SDL2/SDL_mixer.h>

class Music {
public:
    static void init();
    static void playSong(std::string path, std::string name);
    static void stopAll();
private:
    static Mix_Music *currentSong;
};


#endif //CARTDS_MUSIC_HPP
