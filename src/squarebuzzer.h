#ifndef  __SQUAREBUZZER_H__
#define __SQUAREBUZZER_H__

#include <stdio.h>
#include <math.h>
#include "portaudio.h"
#include <stdint.h>


#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER  (64)

typedef struct
{
    uint32_t total_count;
    uint32_t up_count;

    uint32_t counter;
    double prev_freq;
    double freq;
} paTestData;

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData );



static PaStream *stream;
static paTestData data;

void buzzer_set_freq(double frequency);

void buzzer_beep(double frequency, int msecs);

int buzzer_start(void);

int buzzer_stop();


#endif
