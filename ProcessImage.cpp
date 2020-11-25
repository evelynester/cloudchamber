//Author: Evelyn Ester
#include "ProcessImage.h"

ProcessImage::ProcessImage()
{
    // initialize histogram vector
    for(int i=0;i<MAX_LEVEL;i++) histogram[i]=0;
}

ProcessImage::~ProcessImage()
{
    //dtor
}

bool ProcessImage::load_image(std::string filename)
{
    SetEasyBMPwarningsOff();  // disable warnings comming from EasyBMP
    //image_filename=filename;
    if(image.ReadFromFile(filename.c_str()))
     return true;
    else
    return false; // error
}
bool ProcessImage::load_background_image(std::string filename)
{
    SetEasyBMPwarningsOff();
    //background_filename=filename;
    if(background_image.ReadFromFile(filename.c_str()))
     return true;
    else
    return false; // error

}


void ProcessImage::subtract_background()
{
    int temp=0;
    for( int j=0 ; j < image.TellHeight() ; j++)
    {
        for( int i=0 ; i < image.TellWidth() ; i++)
        {

                temp=image(i,j)->Red - background_image(i,j)->Red;
                if(temp<0)
                {
                    image(i,j)->Red=0;
                    image(i,j)->Green=0;
                    image(i,j)->Blue=0;
                }
                else
                {
                    image(i,j)->Red=temp;
                    image(i,j)->Green=temp;
                    image(i,j)->Blue=temp;
                }
        }
    }
}

bool ProcessImage::denoise_with_median_filter(int neighbours)
{
    int window[9];
    if(DEBUG_ProcessImage_MESSAGES)
    std::cout << "denoise with median filter " <<  neighbours << " neighbours"  << std::endl;
    if((neighbours!=4)||(neighbours!=8)) return false;
    if(neighbours==8)
    { // 8 neighbours
        for( int j=1 ; j < image.TellHeight()-1 ; j++)
        {
            for( int i=1 ; i < image.TellWidth()-1 ; i++)
            {
                window[0] = image(i,j-1)->Red;
                window[1] = image(i,j+1)->Red;
                window[2] = image(i,j)->Red;
                window[3] = image(i-1,j)->Red;
                window[4] = image(i+1,j)->Red;
                window[5] = image(i-1,j-1)->Red;
                window[6] = image(i+1,j-1)->Red;
                window[7] = image(i-1,j+1)->Red;
                window[8] = image(i+1,j+1)->Red;
                //sort window array
                std::vector<int> myvector(window, window+9);
                std::sort(myvector.begin(), myvector.end());
                image(i,j)->Red = myvector[4];
                image(i,j)->Green = myvector[4];
                image(i,j)->Blue = myvector[4];
                image(i,j)->Alpha=0;
            }
        }
        return true;
    }
    else
    { // 4 neighbours
        for( int j=1 ; j < image.TellHeight()-1 ; j++)
        {
            for( int i=1 ; i < image.TellWidth()-1 ; i++)
            {
                window[0] = image(i,j-1)->Red;
                window[1] = image(i,j+1)->Red;
                window[2] = image(i,j)->Red;
                window[3] = image(i-1,j)->Red;
                window[4] = image(i+1,j)->Red;
                //sort window array
                std::vector<int> myvector(window, window+5);
                std::sort(myvector.begin(), myvector.end());
                image(i,j)->Red = myvector[2];
                image(i,j)->Green = myvector[2];
                image(i,j)->Blue = myvector[2];
                image(i,j)->Alpha=0;
            }
        }
        return true;
    }
    if(DEBUG_ProcessImage_MESSAGES)
    std::cout << "end denoise with median filter with " << neighbours << " neighbours" << std::endl;
}



bool ProcessImage::denoise_with_mean_filter(int neighbours)
{
    if(DEBUG_ProcessImage_MESSAGES)
    std::cout << "denoise with mean filter " <<  neighbours << " neighbours"  << std::endl;
    if((neighbours!=4)||(neighbours!=8)) return false;
    if(neighbours==8)
    { // 8 neighbours
        for( int j=1 ; j < image.TellHeight()-1 ; j++)
        {
            for( int i=1 ; i < image.TellWidth()-1 ; i++)
            {
              int temp= (image(i,j-1)->Red +
                         image(i,j+1)->Red +
                         image(i,j)->Red +
                         image(i-1,j)->Red +
                         image(i+1,j)->Red +
                         image(i-1,j-1)->Red +
                         image(i+1,j-1)->Red +
                         image(i-1,j+1)->Red +
                         image(i+1,j+1)->Red)/9;

              image(i,j)->Red =temp;
              image(i,j)->Green = temp;
              image(i,j)->Blue = temp;
              image(i,j)->Alpha=0;
            }
        }
        return true;
    }
    else
    { // 4 neighbours
        for( int j=1 ; j < image.TellHeight()-1 ; j++)
        {
            for( int i=1 ; i < image.TellWidth()-1 ; i++)
            {
                int temp= (image(i,j-1)->Red +
                           image(i,j+1)->Red +
                           image(i,j)->Red +
                           image(i-1,j)->Red +
                           +image(i+1,j)->Red)/5;

                image(i,j)->Red =temp;
                image(i,j)->Green = temp;
                image(i,j)->Blue = temp;
                image(i,j)->Alpha=0;
            }
        }
        return true;
    }
    if(DEBUG_ProcessImage_MESSAGES)
    std::cout << "end denoise with mean filter with " << neighbours << " neighbours" << std::endl;
}

void ProcessImage::make_histogram_image(screen_pixel *start,screen_pixel *stop)
{
  // this routine computes the histogram for a given region defined by start and stop coordinates

  // Compute number of pixels
  int pixels = (stop->i-start->i)*(stop->j-start->j);
  int i = 0;
  if(DEBUG_ProcessImage_MESSAGES)
  {
    std::cout << "In make_histogram..." << std::endl;
    std::cout << "Start: (" << start->i << "," << start->j << ")" << std::endl;
    std::cout << "Stop : (" << stop->i << "," << stop->j << ")" << std::endl;
  }
  // zeros in histogram array
  for(i = 0; i <= MAX_LEVEL; i++) histogram[i] = 0;

  for( int j=start->j ; j < stop->j ; j++)
    {
        for( int i=start->i ; i < stop->i ; i++)
        {

           histogram[image(i,j)->Red]++; // get value from red, G,B have same values
        }
    }
  if(DEBUG_ProcessImage_MESSAGES)
  std::cout << "Number of pixels: " << pixels << std::endl;
}


void ProcessImage::segment_image(BMP *Output,int threshold,screen_pixel *start,screen_pixel *stop)
{
  if(DEBUG_ProcessImage_MESSAGES)
  {
    std::cout << "In segment_image..." << std::endl;
    std::cout << "Start: (" << start->i << "," << start->j << ")" << std::endl;
    std::cout << "Stop : (" << stop->i << "," << stop->j << ")" << std::endl;
    std::cout << "Threshold is: " << threshold << std::endl;
  }
  RGBApixel p; // working pixel in BMP
  for( int j=start->j ; j < stop->j ; j++) // for every line
  {
   for( int i=start->i ; i < stop->i; i++)
   {
     int value=image(i,j)->Red;
     if(value > threshold)
     {
       p.Red=255;
       p.Green=255;
       p.Blue=255;
       Output->SetPixel(i,j,p);
      }
      else
      {
        p.Red=0;
        p.Green=0;
        p.Blue=0;
        Output->SetPixel(i,j,p);
      }
   }
  }
}


void ProcessImage::make_otsus_segmentation(BMP *Output, int manual_threshold, screen_pixel *start,screen_pixel *stop)
{
   // computes a threshold for given region defined by start and stop structures for an Input image
   // of class BMP as reference. The image result will be stored in Output BMP given as a pointer.
   // Output BMP has to be written by the caller of this function in a file
   // with manual_threshold we can override the obtained threshold with a given one.
   // usually we call this function with manual_threshold=0.
   // use BMP images!

  if(DEBUG_ProcessImage_MESSAGES)
  {
   std::cout << "In make_otsus_segmentation..." << std::endl;
   std::cout << "Start: (" << start->i << "," << start->j << ")" << std::endl;
   std::cout << "Stop : (" << stop->i << "," << stop->j << ")" << std::endl;
  }
  // Compute total number of pixels
  int pixels = (stop->i-start->i)*(stop->j-start->j);
  int threshold = 0;

  if (manual_threshold != 0)
  {
    // If threshold was manually entered
    threshold = manual_threshold;
    segment_image(Output, threshold,start,stop);
    return;
  }
   // Compute threshold
   // Init variables
    double sum = 0;
    double sum_B = 0; // for background pixels
    double max_variance = 0; // max variance
    int p1 = 0;
    int p2 = 0;

    //used for computing mean for foreground
    for (int i = 0; i <= MAX_LEVEL; i++)
    {
      sum = sum+(i*histogram[i]);
    }

    for (int i = 0 ; i <= MAX_LEVEL ; i++)
    {

      p1 = p1 + histogram[i]; // how many pixels for background at each step
      if (p1 == 0) continue; // we can't divide by zero

      p2 = pixels - p1; // how many pixels for foreground at each step

      if (p2 == 0) break; // no foreground pixels, we can't divide by zero
      // Compute mean_B and mean_F
      sum_B = sum_B + (double) (i * ((int)histogram[i])); // for background
      double mean_B = sum_B / p1; // mean for background
      double mean_F = (sum - sum_B) / p2; // mean for foreground
      double variance = (double) p1 * (double) p2 * (mean_B - mean_F) * (mean_B - mean_F); // total variance
      if (variance > max_variance)
      {
        max_variance = variance; // new max variance
        threshold = i; // threshold is at position i in histogram of image
      }
    }
  if(DEBUG_ProcessImage_MESSAGES)
  std::cout << "Threshold is: " << threshold << std::endl;
  //ATENTION!!!
  if(FORCE_THRESHOLD)
  {
    if(threshold<FORCED_THRESHOLD)
    {
      threshold=FORCED_THRESHOLD; // if threshold is too low, we get too much tracks from background
      std::cout << "Computed threshold too low, force threshold to " << FORCED_THRESHOLD << std::endl;
    }
  }

  // perform image segmentation into Output for zone defined by start and stop
  segment_image(Output, threshold,start,stop);
}

void ProcessImage::perform_segmentation(BMP* Output,int manual_threshold, int steps_i,int steps_j,int width_i,int height_j)
{
    int i,j;
    screen_pixel start,stop;
    for(j=0;j<steps_j;j++) // steps_i in vertical direction
    {
        for(i=0;i<steps_i;i++)
        {
         start.i=i*width_i;
         start.j=j*height_j;
         stop.i=start.i+width_i;
         stop.j=start.j+height_j;
         if(DEBUG_ProcessImage_MESSAGES)
         std::cout << "(" << start.i << "," << start.j << ")->(" << stop.i << "," << stop.j << ") " << std::endl;
         make_histogram_image(&start,&stop);
         make_otsus_segmentation(Output, manual_threshold, &start,&stop);
        }
    }
}
