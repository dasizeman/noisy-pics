#ifndef __SCALEGENERATOR_H__
#define __SCALEGENERATOR_H__

#include "squarebuzzer.h"
#include <time.h>

static int buzzer_init=0;

/**
* The frequencies in the middle octave of cmajor
**/
static double cmajor_freq[] = {261.63, 293.66, 329.63, 349.23, 392, 440, 493.88, 523.25};

/**
* Plays the notes in the c major scale, one second apart
**/
void play_cmajor_scale();

/**
* Plays a specified note in the c major scale for the specified duration
* @param index The index from 1-8 of the note in the scale
* @param duration The duration to hold the note, in ms
**/
void play_cmajor_note(int index, int duration);

/**
* Starts the synth
**/
void start_sound();

/**
* Stops the synth
*/
void stop_sound();

#endif
