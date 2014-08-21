#include "noisypics.h"


int main(int argc, char** argv)
{
    char** filenames = (char**)malloc(sizeof(char*));
    filenames[0] = argv[1];
    IplImage** images = loadImages(1, filenames);
    IplImage* source = images[0];

    int blockcolumns = atoi(argv[2]);
    int blockrows = atoi(argv[3]);
   // printf("%d,%d\n", blockcolumns, blockrows);

   struct imageNoteMap map;
   map.light_max = 0;
   map.light_min = 0;
   map.light_int = 0;
   
   int numblocks = blockcolumns*blockrows;
   CvScalar* colors = process_image(source,blockcolumns, blockrows, &map);
   int scale = determine_scale(source, &map);
   int* notes = generate_notes(colors, &map, numblocks);
   
   int* prunednotes = prune_notes(notes, &numblocks, 3);
   int i;
   for (i =0; i < numblocks; i++)
   {
      printf("%d ", prunednotes[i]);
   }
   printf("\n");
   

   cvNamedWindow("opencvtest",CV_WINDOW_AUTOSIZE);
   cvShowImage("opencvtest",source);
   cvWaitKey(0);
   play(prunednotes, scale, numblocks);
   cvReleaseImage(&source);
   
}

CvScalar* process_image(IplImage* source, int numColumns, int numRows, struct imageNoteMap* map)
{
    int numimages = numRows*numColumns;
    CvScalar* res = getAvgColors(getSubImages(source, numColumns, numRows), numimages); 

    printf("Got avg colors\n");
    
    CvScalar blackScalar = CV_RGB(0,0,0);
    CvScalar whiteScalar = CV_RGB(255,255,255);

    int lightminindex = findClosest(blackScalar, res, numimages);
    int lightmaxindex = findClosest(whiteScalar, res, numimages);
    map->light_min = colorDistance(blackScalar, res[lightminindex]);
    map->light_max = colorDistance(whiteScalar, res[lightmaxindex]);
    printf("Found max lightness %f\n", map->light_max);
    printf("Found min lightness %f\n", map->light_min);

    map->light_int = (map->light_max - map->light_min) / 15;

    return res;

}

int determine_scale(IplImage* source, struct imageNoteMap* map)
{
    double threshold = 128.0;
    CvScalar overall_avg = cvAvg(source, NULL);
    CvScalar blackScalar = CV_RGB(0,0,0);
    double overall_lightness = colorDistance(blackScalar, overall_avg);
    printf("Key lightness threshold %f\n", threshold);
    printf("Got overall lightness value %f\n", overall_lightness);

    if (overall_lightness <= threshold)
    {
        printf("Using minor scale\n");
        return 0;
    }
    else
    {
        printf("Using major scale\n");
        return 1;
    }
}

int* generate_notes(CvScalar* colors, struct imageNoteMap* map, int numColors)
{
    int i, index;
    double lightness;
    CvScalar blackScalar = CV_RGB(0,0,0);

    int* res = (int*)malloc(numColors*sizeof(int));

    for (i = 0; i < numColors; i++)
    {
        lightness = colorDistance(blackScalar, colors[i]);
        index = (lightness / map->light_max) * 15;
        if (index < 1)
            index = 1;
        if (index > 15)
            index = 15;

        res[i] = index;
    }
    return res;
}

int* prune_notes(int* notes, int* numNotes, int maxOccurences)
{
    int current = notes[0];
    int* res = (int*)malloc((*numNotes)*sizeof(int));
    int count = 1;
    int resindex = 0;
    int i,j;

    for (i =1; i < (*numNotes); i++)
    {
        if (notes[i] == current)
            count++;
        else
        {
            current = notes[i];
            if (count > maxOccurences)
            {
                for (j = 0; j < maxOccurences; j++)
                {
                    res[resindex] = notes[i-1];
                    resindex++;
                }
            }
            else
            {
                for (j=0; j < count; j++)
                {
                    res[resindex] = notes[i-1];
                    resindex++;
                }
            }
            count = 1;
        }

    }
    (*numNotes) = resindex+1;
    return res;
}

void play(int* notes, int scale, int numNotes)
{
    int i, index;

    start_sound();
    for (i = 0; i < numNotes; i++)
    {
        printf("PLAYING NOTE %d\n", notes[i]);
        if (scale)
            play_cmajor_note(notes[i], 500);
        else
            play_cminor_note(notes[i], 500);
    }
    stop_sound();

}
