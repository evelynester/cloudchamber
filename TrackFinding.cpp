//Author: Evelyn Ester
#include "TrackFinding.h"
#include <map>
#include <iterator>
#include <vector>

TrackFinding::TrackFinding()
{

    number_of_objects=0;
    objects.clear();
    objects_list.clear();

}


TrackFinding::~TrackFinding()
{
    objects.clear();
    objects_list.clear();
}

int TrackFinding::get_number_of_objects()
{
    return number_of_objects;
}

int TrackFinding::make_map_of_objects(BMP *Output)
{
    int object_number=-1; // first seen object(track) number should be 0
     // nearest neighbors algorithm into a map of pixel objects
    for( int j=1 ; j <= Output->TellHeight()-2 ; j++)
    {
        for( int i=1 ; i <= Output->TellWidth()-2 ; i++)
        {

          if((Output->GetPixel(i,j).Red!=0)&&(objects.find(std::make_pair(i,j)) == objects.end())) // if it is foreground pixel and not already in the map(already processed)
          {
            if(DEBUG_TrackFinding_MESSAGES)
            std::cout << "Pixel: " << i << "," << j << std::endl;
            // test if this is a new object(track) by looking at its neighbours
            if ( (objects.find(std::make_pair(i-1,j-1)) == objects.end()) && (objects.find(std::make_pair(i,j-1)) == objects.end()) &&
                (objects.find(std::make_pair(i+1,j-1)) == objects.end()) && (objects.find(std::make_pair(i-1,j)) == objects.end()))

                // && (objects.find(make_pair(ii+1,jj)) == objects.end()))  // new pixel,new object in list
            {
                object_number++; // a new object
                if(DEBUG_TrackFinding_MESSAGES)
                std::cout << std::endl << "New object at: " << "(" << i << "," << j << ")" << " with number " << object_number << std::endl;

            }
            objects[std::make_pair(i,j)]=object_number;
            insert_neighbours(Output,i,j,object_number); // call nearest neighbours algorithm
          }
        }
    }
    number_of_objects=object_number; // store the number of objects for later use
    return object_number;
}

void TrackFinding::insert_neighbours(BMP* Output,int i,int j, int object_number)
{
    int pixel_count=1;
    int m,n;
    while(pixel_count>0) // while  we added at least one pixel as neighbour
    {
        pixel_count=0;
        std::map<std::pair<int, int>, int>::iterator it = objects.begin();
        // we look at all 8 neighbours of a pixel
        while(it != objects.end())
        {
            if(it->second!=object_number)
            {
                it++;
                continue;
            }
            m=it->first.first;
            n=it->first.second;
            if((m>1)&&(n>1))
            {
                if( (Output->GetPixel(m-1,n-1).Red!=0 ) && (objects.find(std::make_pair(m-1,n-1)) == objects.end())) // no such object in map
                {
                    objects[std::make_pair(m-1,n-1)]=object_number;
                    if(DEBUG_TrackFinding_MESSAGES)
                    std::cout << "Add: (" << m-1 << "," << n-1 << "," << object_number << ")" << std::endl;
                    pixel_count++;
                    break;

                }
            }
            if(n>1)
            {
                if( (Output->GetPixel(m,n-1).Red!=0 ) && (objects.find(std::make_pair(m,n-1)) == objects.end())) // no such object in map
                {
                    objects[std::make_pair(m,n-1)]=object_number;
                    if(DEBUG_TrackFinding_MESSAGES)
                    std::cout << "Add: (" << m << "," << n-1 << "," << object_number << ")" << std::endl;
                    pixel_count++;
                    break;

                }
            }
            if((m<Output->TellWidth()-1)&&(n>1))
            {
                if( (Output->GetPixel(m+1,n-1).Red!=0 ) && (objects.find(std::make_pair(m+1,n-1)) == objects.end())) // no such object in map
                {
                    objects[std::make_pair(m+1,n-1)]=object_number;
                    if(DEBUG_TrackFinding_MESSAGES)
                    std::cout << "Add: (" << m+1 << "," << n-1 << "," << object_number << ")" << std::endl;
                    pixel_count++;
                    break;

                }
            }
            if(m>1)
            {
                if( (Output->GetPixel(m-1,n).Red!=0 ) && (objects.find(std::make_pair(m-1,n)) == objects.end())) // no such object in map
                {
                    objects[std::make_pair(m-1,n)]=object_number;
                    if(DEBUG_TrackFinding_MESSAGES)
                    std::cout << "Add: (" << m-1 << "," << n << "," << object_number << ")" << std::endl;
                    pixel_count++;
                    break;

                }
            }
            if(m<Output->TellWidth()-1)
            {
                if( (Output->GetPixel(m+1,n).Red!=0 ) && (objects.find(std::make_pair(m+1,n)) == objects.end())) // no such object in map
                {
                    objects[std::make_pair(m+1,n)]=object_number;
                    if(DEBUG_TrackFinding_MESSAGES)
                    std::cout << "Add: (" << m+1 << "," << n << "," << object_number << ")" << std::endl;
                    pixel_count++;
                    break;

                }
            }
            if((m>1)&&(n<Output->TellHeight()-1))
            {
                if( (Output->GetPixel(m-1,n+1).Red!=0 ) && (objects.find(std::make_pair(m-1,n+1)) == objects.end())) // no such object in map
                {
                    objects[std::make_pair(m-1,n+1)]=object_number;
                    if(DEBUG_TrackFinding_MESSAGES)
                    std::cout << "Add: (" << m-1 << "," << n+1 << "," << object_number << ")" << std::endl;
                    pixel_count++;
                    break;

                }
            }
            if(n<Output->TellHeight()-1)
            {
                if( (Output->GetPixel(m,n+1).Red!=0 ) && (objects.find(std::make_pair(m,n+1)) == objects.end())) // no such object in map
                {
                    objects[std::make_pair(m,n+1)]=object_number;
                    if(DEBUG_TrackFinding_MESSAGES)
                    std::cout << "Add: (" << m << "," << n+1 << "," << object_number << ")" << std::endl;
                    pixel_count++;
                    break;

                }
            }
            if((m<Output->TellWidth()-1)&&(n<Output->TellHeight()-1))
            {
                if( (Output->GetPixel(m+1,n+1).Red!=0 ) && (objects.find(std::make_pair(m+1,n+1)) == objects.end())) // no such object in map
                {
                    objects[std::make_pair(m+1,n+1)]=object_number;
                    if(DEBUG_TrackFinding_MESSAGES)
                    std::cout << "Add: (" << m+1 << "," << n+1 << "," << object_number << ")" << std::endl;
                    pixel_count++;
                    break;

                }
            }
            it++;
            //cout << endl;
            //cout << "( " << it->first.first << ", " << it->first.second << " ): " << it->second << std::endl;
        }
    }
}
void TrackFinding::extract_tracks_from_map()
{
    int count,i;
    // extract from map of pixels and populate list of pixels for every object, then
    // put head of object into vector of vectors
    if(DEBUG_TrackFinding_MESSAGES)
    {
        std::cout << std::endl << "*****************************************" << std::endl;
        std::cout << "Extract from map and push into vectors of tracks" << std::endl;
    }
    for(i=0;i<=number_of_objects;i++)
    {
        count=0;
        std::vector<pixel_of_object> object;  // a new vector
        //object.clear(); // is it necessary?
        for (std::map<std::pair<int, int>, int>::iterator it = objects.begin(); it != objects.end(); ++it)
        {
            if(DEBUG_TrackFinding_MESSAGES)
            std::cout << "(" << it->first.first << "," << it->first.second << "," << it->second << ")" << std::endl;
            if (it->second == i) // for object(track) i
            {
                    pixel_of_object p(it->first.first,it->first.second,i);
                    object.push_back(p);
                    count++;
            }
        }
        objects_list.push_back(object);
        if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "Object number: " << i << " has number of pixels: " << count << std::endl;
    }
    if(DEBUG_TrackFinding_MESSAGES)
    {
        std::cout << "Total number of objects:" << number_of_objects << std::endl;
        std::cout << "*****************************************" << std::endl;
    }
}


void TrackFinding::remove_tracks_too_small(BMP *Output)
{
    // delete to small objects
    // attention! after deletion of an iterated object, the iterator is invalidated!
    if(DEBUG_TrackFinding_MESSAGES)
    {
        std::cout << "*****************************************" << std::endl;
        std::cout << "Deleting too small tracks..." << std::endl;
    }
    int count=0;
    std::vector<std::vector<pixel_of_object>>::iterator iter = objects_list.begin();

    while(iter != objects_list.end())
    {
        int count_per_object=0;

        if((*iter).size() <= SENSITIVITY) // if track is smaller than sensitivity
        {
          if(DEBUG_TrackFinding_MESSAGES)
            std::cout << "Size of vector at position " << iter-objects_list.begin() << " is: " << (*iter).size() << std::endl;
          for (std::vector<pixel_of_object>::iterator innerIt = iter->begin(); innerIt != iter->end(); ++innerIt)
          {
            count_per_object++;
            RGBApixel p;
            p.Red=0;
            p.Green=0;
            p.Blue=0;
            Output->SetPixel(innerIt->Get_i(),innerIt->Get_j(),p); // black all removed pixels in output image
          }
          count++;
          if(DEBUG_TrackFinding_MESSAGES)
            std::cout << "erasing track: " << iter-objects_list.begin() << " with: " << count_per_object << " pixels" << std::endl;
          iter=objects_list.erase(iter); // erase objects with less than 20 pixels = sensitivity
          // erase() makes the passed iterator invalid
          // But returns the iterator to the next of deleted element
        }
        else iter++;
    }
    if(DEBUG_TrackFinding_MESSAGES)
    {
        std::cout << std::endl;
        std::cout << "Total erased tracks: " << count << std::endl;
        std::cout << "Track list has size: " << objects_list.size() << std::endl;
        std::cout << "*****************************************" << std::endl;
    }
}



int TrackFinding::energy_of_object_in_list(BMP* input,std::vector<std::vector<pixel_of_object>>::iterator iter)
{
    int i1,j1;
    RGBApixel p;

    int total=0;
    int length=iter->size();
    if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "size of vector: " << length << std::endl;
    for(int i=0;i<length;i++)
    {
      i1=iter->at(i).Get_i();
      j1=iter->at(i).Get_j();
      p=input->GetPixel(i1,j1);
      total= total + p.Red; // sum all the pixels values from ORIGINAL image
    }
    if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "Energy: " << total << std::endl;
   return total;
}


double TrackFinding::maximum_distance_in_list(std::vector<std::vector<pixel_of_object>>::iterator iter,screen_pixel *start,screen_pixel *stop)
{
    int i1,i2,j1,j2;
    int tempi1,tempi2,tempj1,tempj2;
    //vector<pixel_of_object>::iterator m = iter->begin();
    //vector<pixel_of_object>::iterator n = iter->begin();
    double distance=0;
    double max_distance=0;
    int length=iter->size();
    if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "size of vector: " << length << std::endl;
    // generate all pixel combinations
    if(length<2) return 0;
    for(int i=0;i<length;i++)
      for(int j=i+1;j<length;j++)
       if(i!=j)
       {

           i1=iter->at(i).Get_i();
           j1=iter->at(i).Get_j();
           i2=iter->at(j).Get_i();
           j2=iter->at(j).Get_j();

           distance=sqrt((i2-i1)*(i2-i1) + (j2-j1)*(j2-j1));
           if(distance>max_distance)
           {
             max_distance=distance;
             tempi1=i1;
             tempj1=j1;
             tempi2=i2;
             tempj2=j2;
           }

       }
    if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "Max distance is between: " << tempi1 << "," << tempj1 << " and " << tempi2 << "," << tempj2 << std::endl;
    start->i=tempi1;
    start->j=tempj1;
    stop->i=tempi2;
    stop->j=tempj2;
    return max_distance;
}

// this routine is not currently used
double TrackFinding::minimum_distance_between_lists(std::vector<std::vector<pixel_of_object>>::iterator iter1,std::vector<std::vector<pixel_of_object>>::iterator iter2)
{
    int i1,i2,j1,j2;
    int tempi1,tempi2,tempj1,tempj2;
    //vector<pixel_of_object>::iterator m = iter1->begin();
    //vector<pixel_of_object>::iterator n = iter2->begin();
    double distance=0;
    double min_distance=std::numeric_limits<double>::max();
    int length1=iter1->size();
    int length2=iter2->size();
    if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "size of vectors: " << length1 << " and " << length2 << std::endl;
    // generate all pixel combinations
    for(int i=0;i<length1;i++)
      for(int j=i+1;j<length2;j++)
       {
           if(i!=j)
           {
            i1=iter1->at(i).Get_i();
            j1=iter1->at(i).Get_j();
            i2=iter2->at(j).Get_i();
            j2=iter2->at(j).Get_j();

            distance=sqrt((i2-i1)*(i2-i1) + (j2-j1)*(j2-j1));
            if(distance<min_distance)
            {
                min_distance=distance;
                tempi1=i1;
                tempj1=j1;
                tempi2=i2;
                tempj2=j2;
            }
           }
       }
    if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "Min distance is between: " << tempi1 << "," << tempj1 << " and " << tempi2 << "," << tempj2 << std::endl;
    return min_distance;
}
// this is used as a safety measure, to check the correctness of nearest neighbour algorithm
bool TrackFinding::check_vectors()
{
    std::vector<std::vector<pixel_of_object>>::iterator iter = objects_list.begin();
    int count=-1;
    while(iter != objects_list.end())
    {
     count++;
     for (std::vector<pixel_of_object>::iterator innerIt = iter->begin(); innerIt != iter->end(); ++innerIt)
     {
       if(innerIt->GetObjectNumber()!=count)
       {
         if(DEBUG_TrackFinding_MESSAGES)
         std::cout << "FOUND DIFFERRENT OBJECT NUMBER AT POSITION " << count << " " << innerIt->GetObjectNumber() << std::endl;
         return false;
       }
       if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "(" << innerIt->Get_i() << "," << innerIt->Get_j() << "," << innerIt->GetObjectNumber() << ") " << std::endl;
     }
    iter++;
    }
    return true;
}

// this extracts important values for detected tracks
void TrackFinding::report_tracks(BMP* Input)
{
    int count=0;
    screen_pixel start,stop;
    // compute various values for tracks
    for (std::vector<std::vector<pixel_of_object>>::iterator iter = objects_list.begin(); iter != objects_list.end();iter++)
    {
        int count_per_object=0;
        count++;
        double max_distance=0;
        int energy; // energy is an integer because is the sum of values of pixels of a track
        for (std::vector<pixel_of_object>::iterator innerIt = iter->begin(); innerIt != iter->end(); ++innerIt)
        {
            count_per_object++;
            //cout << "(" << innerIt->Get_i() << "," << innerIt->Get_j() << "," << innerIt->GetObjectNumber() << ") ";
        }

        std::cout << std::endl;
        max_distance=maximum_distance_in_list(iter,&start,&stop);
        energy=energy_of_object_in_list(Input,iter);
        std::cout << "Track: " << count << " has: " << count_per_object << " pixels" << std::endl;
        std::cout << "Maximum distance between pixels into track: " << max_distance << " pixels" << std::endl;
        std::cout << "Object located between: " << "(" << start.i << "," << start.j << ")->(" << stop.i << "," << stop.j << ")" << std::endl;
        std::cout << "Total energy as sum of all pixel values: " << energy << std::endl;
        std::cout << "Total energy/max_distance: " << energy/max_distance << std::endl;
        std::cout << "Total energy/nr. of pixels: " << ((double) energy)/((double)count_per_object) << std::endl;
        double angle=atan2(((double)(start.j-stop.j)),abs(((double)(start.i-stop.i))))*180.0/3.14159265358979;
        if(angle<0) angle=angle+180.0;
        std::cout << "Track direction is: " << angle << " degrees" << std::endl;
        if(energy/max_distance < BETA_ENERGY)
            std::cout << "This is a Beta particle" << std::endl;
        else
            std::cout << "This is an Alpha particle" << std::endl;
        if(check_if_touches_upper(iter))
            std::cout << "Track touches upper edge of the chamber" << std::endl;
        if(check_if_touches_lower(iter))
            std::cout << "Track touches lower edge of the chamber" << std::endl;
        if(check_if_touches_left(iter))
            std::cout << "Track touches left edge of the chamber" << std::endl;
        if(check_if_touches_right(iter))
            std::cout << "Track touches right edge of the chamber" << std::endl;
    }
    std::cout << std::endl << "Total number of tracks in list of tracks:" << count << std::endl;
}

void TrackFinding::write_output_tracks_into_image(BMP* Output)
{
   for (std::vector<std::vector<pixel_of_object>>::iterator iter = objects_list.begin(); iter != objects_list.end();iter++)
   {
     for (std::vector<pixel_of_object>::iterator innerIt = iter->begin(); innerIt != iter->end(); ++innerIt)
     {

       RGBApixel p;
       p.Red = 0;
       p.Green = 0;
       p.Blue = 0;
       int nr=innerIt->GetObjectNumber();
       // change color value for tracks
       if((nr%3)==0) p.Red=255;
       if((nr%3)==1) p.Green=255;
       if((nr%3)==2) p.Blue=255;
       Output->SetPixel(innerIt->Get_i(), innerIt->Get_j(), p);
     }
  }
}

bool TrackFinding::check_if_touches_upper(std::vector<std::vector<pixel_of_object>>::iterator iter)
{
    int m,n;
    int length=iter->size();
    bool touch=false;
    if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "size of vector: " << length << std::endl;
    for(int i=0;i<length;i++)
    {
      m=iter->at(i).Get_i();
      n=iter->at(i).Get_j();
      if((n-SENSITIVITY)<=0) //distance between j coordinate(height) and upper edge lower than sensitivity
      {
          touch=true;
          break;
      }
    }
    if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "Track touches upper at: " << "(" << m << "," << n << ")" << std::endl;
    return touch;
}


bool TrackFinding::check_if_touches_lower(std::vector<std::vector<pixel_of_object>>::iterator iter)
{
    int m,n;
    int length=iter->size();
    bool touch=false;
    if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "size of vector: " << length << std::endl;
    for(int i=0;i<length;i++)
    {
      m=iter->at(i).Get_i();
      n=iter->at(i).Get_j();
      if((IMAGE_HEIGHT-n-SENSITIVITY)<=0) //distance between j coordinate(height) and lower edge lower than sensitivity
      {
          touch=true;
          break;
      }
    }
    if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "Track touches lower at: " << "(" << m << "," << n << ")" << std::endl;
    return touch;
}

bool TrackFinding::check_if_touches_left(std::vector<std::vector<pixel_of_object>>::iterator iter)
{
    int m,n;
    int length=iter->size();
    bool touch=false;
    if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "size of vector: " << length << std::endl;
    for(int i=0;i<length;i++)
    {
      m=iter->at(i).Get_i();
      n=iter->at(i).Get_j();
      if((m-SENSITIVITY)<=0) //distance between i coordinate(width) and left edge lower than sensitivity
      {
          touch=true;
          break;
      }
    }
    if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "Track touches left at: " << "(" << m << "," << n << ")" << std::endl;
    return touch;
}

bool TrackFinding::check_if_touches_right(std::vector<std::vector<pixel_of_object>>::iterator iter)
{
    int m,n;
    int length=iter->size();
    bool touch=false;
    if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "size of vector: " << length << std::endl;
    for(int i=0;i<length;i++)
    {
      m=iter->at(i).Get_i();
      n=iter->at(i).Get_j();
      if((IMAGE_WIDTH-m-SENSITIVITY)<=0) //distance between i coordinate(width) and right edge lower than sensitivity
      {
          touch=true;
          break;
      }
    }
    if(DEBUG_TrackFinding_MESSAGES)
        std::cout << "Track touches right at: " << "(" << m << "," << n << ")" << std::endl;

    return touch;
}


