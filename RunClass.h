//Author: Evelyn Ester
#ifndef CLOUDCHAMBER_RUNCLASS_H
#define CLOUDCHAMBER_RUNCLASS_H

#include <fstream>
#include <iostream>
#include "EasyBMP.h"
#include "defines.h"

#include "ProcessImage.h"
#include "TrackFinding.h"

class RunClass : public ProcessImage, public TrackFinding
{
    public:

        RunClass();

        ~RunClass();

        int get_steps_i();
        int get_steps_j();
        int get_width_i();
        int get_height_j();
        int get_threshold();

        std::string get_image_filename();
        std::string get_output_filename();
        std::string get_background_image_filename();
        BMP* get_input_image_pointer();
        BMP* get_output_image_pointer();

        void set_steps_i(int value);
        void set_steps_j(int value);
        void set_width_i(int value);
        void set_height_j(int value);
        void set_threshold(int value);
        void set_number_of_steps();

        std::string set_image_filename(std::string s);
        std::string set_output_filename(std::string s);
        std::string set_background_image_filename(std::string s);

        bool check_if_file_exists(const std::string& name);
        bool check_width(const int width); // check if width is ok
        bool check_height(const int height); // check if height is ok
        bool check_threshold(const int threshold); // check if threshold is between 0 and 255

        bool check_if_image_ok(); // check if image is grayscale
        bool check_if_background_image_ok(); // check if image is grayscale

        void PrintDetails(); // displays parameters for the image processing job

        void prepare_output_image(); // makes black all pixels of the image
        void write_output_image(); // writes output image to choosen file name from command line options
        void write_output_image(std::string name); // writes output image given a file name
        void reverse_output_image(); // revers pixels to better see the output image
        bool load_scene(std::string filename);


    private:
        BMP *Input; // this will keep original image
        BMP *Subtract; // this will keep background image to be subtracted from original image
        BMP *Output; // output image for detected tracks
        screen_pixel start,stop; // for window of otsu's segmentation

        int steps_i; // how many steps in i(horizontal) direction
        int steps_j; // how many steps in j(vertical) direction

        int width_i; //  =atoi(argv[4]); width of otsu's algo
        int height_j;//  =atoi(argv[5]); height of otsu's algo
        int threshold; //=atoi(argv[6]); manual threshold of otsu's algo

        std::string image_filename;
        std::string background_image_filename;
        std::string output_filename;

};

#endif // CLOUDCHAMBER_RUNCLASS_H
