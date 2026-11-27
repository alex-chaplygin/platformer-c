#include <SDL.h>
#include <math.h>
#include "tone.h"

/// Размер буфера для звука
#define AUDIO_BUFFER_SIZE 1024

float g_freq; // частота, которую сейчас играем
float g_phase;  // текущая фаза синуса
SDL_AudioDeviceID g_dev;  // открытое аудиоустройство

// Генерация синуса в буфер
static void generate(float* buf, int n, float freq, float* phase)
{
    float inc = 2.0f * (float)M_PI * freq / 44100.0f;
    for (int i = 0; i < n; i++) {
        buf[i] = 0.2f * sinf(*phase);
        *phase += inc;
        if (*phase >= 2.0f * (float)M_PI)
            *phase -= 2.0f * (float)M_PI;
    }
}

/** 
 * Функция микширования хвука
 *
 * @param ud владелец
 * @param stream буфер, который необходимо заполнить новыми данными
 * @param len длина буфера
 */
static void mixer(void* ud, Uint8* stream, int len)
{
    float* buf = (float*)stream;
    int n = len / sizeof(float);
    generate(buf, n, g_freq, &g_phase);
}

/** 
 * Инициализация аудио
 */
void audio_init()
{
    SDL_Init(SDL_INIT_AUDIO);
    SDL_AudioSpec w, h;
    SDL_zero(w);
    w.freq = 44100;
    w.format = AUDIO_F32;
    w.channels = 1;
    w.samples = AUDIO_BUFFER_SIZE;
    w.callback = mixer;
    g_dev = SDL_OpenAudioDevice(NULL, 0, &w, &h, 0);
    SDL_PauseAudioDevice(g_dev, 0);
}

void play_tone(float freq, int ms) {
    g_freq = freq;
    SDL_Delay(ms);
    g_freq = 0.0f;
    SDL_Delay(50);
}
