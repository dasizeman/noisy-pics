#include "noisypics.h"


int main(int argc, char** argv)
{
    char** filenames = (char**)malloc(sizeof(char*));
    filenames[0] = argv[1];
    IplImage** images = loadImages(1, filenames);
    IplImage* source = images[0];

    int blockcolumns = atoi(argv[1]);
    int blockrows = atoi(argv[2]);

   struct imageNoteMap map;
   map.light_max = 0;
   map.light_min = 0;
   map.light_int = 0;
   
   int numblocks = blockcolumns*blockrows;
   CvScalar* colors = process_image(source,blockcolumns, blockrows, &map);
   int scale = determine_scale(source, &map);
   int* notes = generate_notes(colors, &map, numblocks);

   int i;
   for (i =0; i < numblocks; i++)
   {
       printf("%d\n", notes[i]);
   }
}

CvScalar* process_image(IplImage* source, int numColumns, int numRows, struct imageNoteMap* map)
{
    int numimages = numRows*numColumns;
    CvScalar* res = getAvgColors(getSubImages(source, numColumns, numRows), numimages); 
    
    CvScalar blackScalar = CV_RGB(0,0,0);
    CvScalar whiteScalar = CV_RGB(255,255,255);

    int lightminindex = findClosest(blackScalar, res, numimages);
    int lightmaxindex = findClosest(whiteScalar, res, numimages);
    map->light_min = colorDistance(blackScalar, res[lightminindex]);
    map->light_max = colorDistance(whiteScalar, res[lightmaxindex]);

    map->light_int = (map->light_max - map->light_min) / 15;

    return res;

}

int determine_scale(IplImage* source, struct imageNoteMap* map)
{
    double threshold = (map->light_max - map->light_min) / 2;
    CvScalar overall_avg = cvAvg(source, NULL);
    CvScalar blackScalar = CV_RGB(0,0,0);
    double overall_lightness = colorDistance(blackScalar, overall_avg);

    if (overall_lightness <= threshold)
        return 0;
     else return 1;
}

int* generate_notes(CvScalar* colors, struct imageNoteMap* map, int numColors)
{
    int i, lightness, index;
    CvScalar blackScalar = CV_RGB(0,0,0);

    int* res = (int*)malloc(numColors*sizeof(int));

    for (i = 0; i < numColors; i++)
    {
        lightness = colorDistance(blackScalar, colors[i]);
        index = lightness / map->light_int;
        if (index < 1)
            index = 1;
        if (index > 15)
            index = 15;

        res[i] = index;
    }
    return res;
}

void play(int* notes, int scale, int numNotes)
{
    int i, index;

    start_sound();
    for (i = 0; i < numNotes; i++)
    {
        if (scale)
            play_cmajor_note(notes[i], 500);
        else
            play_cminor_note(notes[i], 500);
    }
    stop_sound();

}
