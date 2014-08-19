#include "scalegenerator.h"

void play_cmajor_note(int index, int duration)
{
    clock_t start = clock();
    clock_t stop = start + (duration * (CLOCKS_PER_SEC / 1000));
    buzzer_set_freq(cmajor_freq[index-1]);
    while (clock() < stop) {}
}


void play_cmajor_scale()
{
    int i;

    for ( i = 1; i <= 15; i++)
    {
        play_cmajor_note(i, 500); 
    }

}


void play_cminor_note(int index, int duration)
{
    clock_t start = clock();
    clock_t stop = start + (duration * (CLOCKS_PER_SEC / 1000));
    buzzer_set_freq(cminor_freq[index-1]);
    while (clock() < stop) {}
}

void play_cminor_scale()
{
    int i;

    for ( i = 1; i <= 15; i++)
    {
        play_cminor_note(i, 500); 
    }

}

void start_sound()
{
    if (!buzzer_init)
    {
        buzzer_start();
        buzzer_init = 1;
    }
}

void stop_sound()
{
    if (buzzer_init)
    {
        buzzer_stop();
        buzzer_init = 0;
    }
}

