//
// Created by cameronearle on 2/25/18.
//

#include "Music.hpp"
#include "Output.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Mix_Music *Music::currentSong = nullptr;

void Music::init() {
    SDL_Init(SDL_INIT_AUDIO); //Initialize audio layer
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096); //Open the audio device
}

void Music::stopAll() {
    if (currentSong != nullptr) {
        Mix_HaltMusic(); //Stop playback
        Mix_FreeMusic(currentSong); //Release current song from memory
        currentSong = nullptr;
    }
    Output::setNowPlaying("None");
}

void Music::playSong(std::string path, std::string name) {
    stopAll(); //Stop all previous music
    currentSong = Mix_LoadMUS(path.c_str()); //Load new music
    Mix_PlayMusic(currentSong, 1); //Play current song once
    Output::setNowPlaying(name);
}