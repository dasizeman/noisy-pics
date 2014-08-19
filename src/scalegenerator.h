#ifndef __SCALEGENERATOR_H__
#define __SCALEGENERATOR_H__

#include "squarebuzzer.h"
#include <time.h>

static int buzzer_init=0;

/**
* The frequencies in the middle two octaves of c major
**/
static double cmajor_freq[] = {261.63, 293.66, 329.63, 349.23, 392, 440, 493.88, 523.25, 587.32, 659.26, 698.46, 784, 880, 987.76, 1046.5};

/**
* The frequencies in the middle two octaves of c minor
**/
static double cminor_freq[] = {261.63, 293.66, 311.13, 349.23, 392, 415.30, 466.16, 523.25, 587.32, 622.26, 698.46, 784, 830.6, 932.32, 1046.5};

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
* Plays the notes in the c minor scale, one second apart
**/
void play_cminor_scale();

/**
* Plays a specified note in the c minor scale for the specified duration
* @param index The index from 1-8 of the note in the scale
* @param duration The duration to hold the note, in ms
**/
void play_cminor_note(int index, int duration);

/**
* Starts the synth
**/
void start_sound();

/**
* Stops the synth
*/
void stop_sound();

#endif
