#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "audio.h"

SDL_AudioDeviceID audio_device;

int audio_init()
{
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
    return 0;
}

int audio_quit()
{
    Mix_CloseAudio();
    Mix_Quit();
    return 0;

}