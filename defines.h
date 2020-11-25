#ifndef CLOUDCHAMBER_DEFINES_H_INCLUDED
#define CLOUDCHAMBER_DEFINES_H_INCLUDED

#define DEBUG_RunClass_MESSAGES false     //if true, cout a lot of informative messages
#define DEBUG_ProcessImage_MESSAGES false //if true, cout a lot of informative messages
#define DEBUG_TrackFinding_MESSAGES false //if true, cout a lot of informative messages

#define IMAGE_WIDTH 1920  // should bet set accordingly to image dimensions
#define IMAGE_HEIGHT 1080 // should bet set accordingly to image dimensions

//IT WORKS ALSO! REPLACE IN ALL .H FILES WHICH CONTAIN THESE 2 DEFINITIONS
//#define IMAGE_WIDTH 1024  // should bet set accordingly to image dimensions
//#define IMAGE_HEIGHT 768 // should bet set accordingly to image dimensions

#define MAX_LEVEL 255 // max value of gray level
#define FORCE_THRESHOLD true // decide if we force the threshold in otsu's threshold algorithm
#define FORCED_THRESHOLD 10 // if threshold too  low, set threshold to this value; use it for images with alphas and betas

// sensitivity of detection algorithm, if less or equal than this value, the track and its list of pixels will be removed
// this value is also used to decide if a track is near an edge of the cloud chamber
#define SENSITIVITY 20
#define BETA_ENERGY 1000 // under this value of energy/distance, the track should be a beta particle, otherwise is an alpha

// structure used to describe a pixel on screen
// with two different structures we can define a rectangle
// a rectangle is used for example to define the region for otsu's algorithm


typedef struct
{
    int i; // column
    int j; // row
} screen_pixel;



#endif // CLOUDCHAMBER_DEFINES_H_INCLUDED
