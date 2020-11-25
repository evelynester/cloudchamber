//Author: Evelyn Ester
#ifndef CLOUDCHAMBER_TRACKFINDING_H
#define CLOUDCHAMBER_TRACKFINDING_H
#include <algorithm>
#include <vector>
#include <map>
#include <list>
#include <iterator>
#include "pixel_of_object.h"
#include "ProcessImage.h"
#include "EasyBMP.h"
#include "defines.h"


class TrackFinding
{
    public:

        TrackFinding();
        ~TrackFinding();
        int make_map_of_objects(BMP *Output); // put all pixels into a map by track(object) number


        void extract_tracks_from_map(); // extract tracks from map into a vector of vectors of tracks by track number
        bool check_vectors();

        int get_number_of_objects();

        void remove_tracks_too_small(BMP *Output);

        int energy_of_object_in_list(BMP* input,std::vector<std::vector<pixel_of_object>>::iterator iter);
        double maximum_distance_in_list(std::vector<std::vector<pixel_of_object>>::iterator iter,screen_pixel *start,screen_pixel *stop);
        //double minimum_distance_in_list(std::vector<std::vector<pixel_of_object>>::iterator iter,screen_pixel* start,screen_pixel* stop);
        double minimum_distance_between_lists(std::vector<std::vector<pixel_of_object>>::iterator iter1,std::vector<std::vector<pixel_of_object>>::iterator iter2);
        void report_tracks(BMP* Input); // report measured values for detected tracks
        void insert_neighbours(BMP *Output,int i,int j, int object_number);
        void write_output_tracks_into_image(BMP* Output);

        bool check_if_touches_upper(std::vector<std::vector<pixel_of_object>>::iterator iter);
        bool check_if_touches_lower(std::vector<std::vector<pixel_of_object>>::iterator iter);
        bool check_if_touches_left(std::vector<std::vector<pixel_of_object>>::iterator iter);
        bool check_if_touches_right(std::vector<std::vector<pixel_of_object>>::iterator iter);


    protected:

    private:

    int number_of_objects; // total number of detected tracks
    std::map<std::pair<int, int>, int> objects; // map of pixels and object(track) numbers
    std::vector<std::vector<pixel_of_object>> objects_list; // vector of vector of pixels for each detected object(track)

};

#endif // CLOUDCHAMBER_TRACKFINDING_H
