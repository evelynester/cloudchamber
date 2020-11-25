//Author: Evelyn Ester
#ifndef CLOUDCHAMBER_PROCESSIMAGE_H
#define CLOUDCHAMBER_PROCESSIMAGE_H
#include "EasyBMP.h"
#include <string>
#include <vector>
#include <algorithm>
#include "pixel_of_object.h"
#include "defines.h"

class ProcessImage
{
    public:

        ProcessImage();

        ~ProcessImage();

        bool load_image(std::string filename); // true = success, loads the image to be analyzed
        bool load_background_image(std::string filename); // true = success, loads the background image

        void subtract_background(); // perform subtraction of background image from image to be analyzed

        bool denoise_with_median_filter(int neighbours); // performs denoising with median filter, with 4 or 8 neighbours
        bool denoise_with_mean_filter(int neighbours); // performs denoising with meean filter, with 4 or 8 neighbours
        void make_histogram_image(screen_pixel *start,screen_pixel *stop); // make histogram for a rectangle inside the input image

        // make image segmentation for a rectangle inside the input image, given the threshold and position of rectangle
        // it turns pixels with values above threshold into white, and those under threshold into black
        // the change is performed into the image given as a pointer from RunClass
        void segment_image(BMP *Output,int threshold,screen_pixel *start,screen_pixel *stop);
        // determine the threshold for background and foreground pixels, or the threshold is forced by value of manual_threshold
        // for images with beta and alfa particles, usually the computed value of threshold is less than 6
        // if the computed threshold is less than 10, we force the threshold to 10, thus allowing
        // the other routines to detect alfa and beta particles in the same image
        void make_otsus_segmentation(BMP *Output, int manual_threshold, screen_pixel *start,screen_pixel *stop);
        // performs image segmentation for the whole observation image
        void perform_segmentation(BMP *Output,int manual_threshold, int steps_i,int steps_j,int width_i,int height_j);


    private:
    BMP image; // keeps observation image
    BMP background_image; // keeps background image

    int histogram[MAX_LEVEL+1]; //  vector to store histogram values for this image
    screen_pixel start,stop; // working structures

};

#endif // CLOUDCHAMBER_PROCESSIMAGE_H
