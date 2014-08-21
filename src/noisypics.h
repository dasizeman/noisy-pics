#include "imageutils.h"
#include "scalegenerator.h"

/**
* Holds information about how we are mapping the image data to notes
**/
struct imageNoteMap{
    double light_max; // The maximum lightness in the current image
    double light_min; // The minimum "                            "
    double light_int; // The lightness interval.  This is determined by dividing the lightness range by
                      // the total number of notes we are going to use
};

/**
* This does a few things.  It splits an image into an array of subimages, and creates a list of the average colors of these subimages.
* It also populates an imageNoteMap with the correct information based on the image
* @param source The image to process
* @param numColumns The number of columns to split the image into
* @param numRows The number of rows "                           "
* @param map The imageNoteMap struct to populate
* @return An array of color scalars representing the color averages of the subimages
**/
CvScalar* process_image(IplImage* source, int numColumns, int numRows, struct imageNoteMap* map);

/**
* This takes a color average of an entire picture and determines if a major or minor scale should be used,
* based on its lightness
* @param source The image to process
* @param map The note map to use
* @return 0 if minor should be used, 1 if major should be used
**/
int determine_scale(IplImage* source, struct imageNoteMap* map);

/**
* Generate a sequence of note indices based on the lightness of colors
* @param colors The list of colors to use
* @param map The note mapping information to use
* @param numColors The number of colors in the array
**/
int* generate_notes(CvScalar* colors, struct imageNoteMap* map, int numColors);

/**
* Filters note data so that no note can appear consecutively more than a certain amount of times
* NOTE THAT NUMNOTES GETS SET TO THE PRUNED AMOUNT HERE
* @param notes The note data to filter
* @param numNotes The number of notes in the array
* @param maxOccurences
* @return The pruned array
**/
int* prune_notes(int* notes, int* numNotes, int maxOccurences);

/**
* Generate a unique series of tones based on a list of colors
* @param colors The colors to use
* @param map The note mapping information to use
* @param scale An integer representing the scale to use (0 for minor, 1 for major)
* @param numNotes The number of notes in the array
**/
void play(int* notes, int scale, int numNotes);
