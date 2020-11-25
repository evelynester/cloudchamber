//Author: Evelyn Ester
#include "EasyBMP.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <list>
#include <iterator>
#include <cmath>
#include "pixel_of_object.h"
#include "RunClass.h"

using namespace std;

int main( int argc, char* argv[] )
{
    if( argc != 7 )
    {
        cout << "Usage: CloudChamber <input_filename> <background_filename> <output_filename> <width> <height> <manual_threshold>" << endl;
        cout << "input_filename is the name of the image to be processed" << endl;
        cout << "background_filename is the name of the image to be subtracted from image to be processed" << endl;
        cout << "output_filename is the name of the image to be saved containing detected tracks" << endl;
        cout << "width is the width of the window of otsu's algorithm to be applied" << endl;
        cout << "height is the height of the window of otsu's algorithm to be applied" << endl;
        cout << "manual_threshold overrides the detected threshold of otsu's algorithm, it's used mainly for beta particles" << endl;

        return 1;
    }
    // get a new run class
    RunClass run;
    //check if image exists
    if(!run.check_if_file_exists(argv[1]))
    {
        cout << "Image file: " << argv[1] << " does not exist, exiting" << endl;
        return 1;
    }
    else
      run.set_image_filename(argv[1]); // set image file name
    //check if background to be subtracted exists
    if(!run.check_if_file_exists(argv[2]))
    {
        cout << "Background file: " << argv[2] << " does not exist, exiting" << endl;
        return 1;
    }
    else
        run.set_background_image_filename(argv[2]); //set background image file name

    run.set_output_filename(argv[3]); // set output filename, it will be created

    // check window width for otsu's algorithm
    if(!run.check_width(atoi(argv[4])))
    {
        cout << "Window width for Otsu's algorithm is wrong: " << argv[4] << " ,exiting" << endl;
        return 1;
    }
    else
        run.set_width_i(atoi(argv[4])); // set width
    // check window height for otsu's algorithm
    if(!run.check_height(atoi(argv[5])))
    {
        cout << "Window height for Otsu's algorithm is wrong: " << argv[5] << " ,exiting" << endl;
        return 1;
    }
    else
        run.set_height_j(atoi(argv[5]));
    //check manual threshold for otsu's algorithm
    if(!run.check_threshold(atoi(argv[6])))
    {
        cout << "Manual threshold for Otsu's algorithm is wrong: " << argv[6] << " ,exiting" << endl;
        return 1;
    }
    else
        run.set_threshold(atoi(argv[6])); // may be zero, which means that we don't set a manual threshold

    if(!run.check_if_image_ok())
    {
        cout << "Input image is not ok,exiting" << endl;
        return 1;
    }
    else
        cout << "Input image is ok, continue processing" << endl;

    if(!run.check_if_background_image_ok())
    {
        cout << "Input image is not ok,exiting" << endl;
        return 1;
    }
    else
        cout << "Background image is ok, continue processing" << endl;
    run.set_number_of_steps(); // compute number of steps for otsu's algorithm
    run.prepare_output_image(); // make an empty output image, all pixels black
    run.PrintDetails(); // display run details

    /*
    // use this if you did not use check_if_image_ok()
    if(!run.load_scene(run.get_image_filename()))
    {
      cout << "Could not load image: " << run.get_image_filename() << " exiting" << endl;
      return 1;
    }
    */
    if(!run.load_image(run.get_image_filename()))
    {
      cout << "Could not load image: " << run.get_image_filename() << " exiting" << endl;
      return 1;
    }
    if(!run.load_background_image(run.get_background_image_filename()))
    {
      cout << "Could not load background image: " << run.get_background_image_filename() << " exiting" << endl;
      return 1;
    }

    run.subtract_background();
    run.denoise_with_median_filter(8);
    run.perform_segmentation(run.get_output_image_pointer(),run.get_threshold(),run.get_steps_i(),run.get_steps_j(),run.get_width_i(),run.get_height_j());

    run.make_map_of_objects(run.get_output_image_pointer()); // make nearest neighbour algorithm
    run.extract_tracks_from_map(); // put all tracks into appropriate vector

    if(!run.check_vectors()) // check if list of tracks is ok
    {
      cout << "Error! Object with different number into another list. Exiting" << endl;
      return 1;
    }

    run.remove_tracks_too_small(run.get_output_image_pointer());
    run.report_tracks(run.get_input_image_pointer());


    run.reverse_output_image(); // reverse pixels to better see the output image
    run.write_output_image(("temp_"+run.get_output_filename()).c_str()); // write output image as an example after performing otsu' segmentation

    run.prepare_output_image(); // make all pixels black in output image
    run.reverse_output_image(); // reverse pixels to see output
    run.write_output_tracks_into_image(run.get_output_image_pointer());
    run.write_output_image(run.get_output_filename()); // write output image as an example after performing otsu' segmentation

    return 0;


}
