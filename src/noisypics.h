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
}

/**
* Determines the "lightness" of an image.  In this context we are defining lightness as euclidean distance
* from black
**/
double get_lightness(IplImage* image);
