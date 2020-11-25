//Author: Evelyn Ester
#include "RunClass.h"

RunClass::RunClass()
{
    //ctor , initialize with defaults
    Input = new BMP();
    Subtract = new BMP();
    Output = new BMP();

    steps_i=1; // how many steps in i(horizontal) direction
    steps_j=1; // how many steps in j(vertical) direction

    width_i=IMAGE_WIDTH; //  =atoi(argv[4]); width of otsu's algo
    height_j=IMAGE_HEIGHT;//  =atoi(argv[5]); height of otsu's algo
    threshold=0; //=atoi(argv[6]); manual threshold of otsu's algo
}

RunClass::~RunClass()
{
    //dtor
    //free BMP image pointers
    delete Input;
    delete Subtract;
    delete Output;

}

bool RunClass::check_if_file_exists(const std::string& name)
{
    if(DEBUG_RunClass_MESSAGES)
    std::cout << "Name: " << name << std::endl;

    std::ifstream file(name.c_str());
    return file.good();
}


bool RunClass::check_width(const int width)
{
  if(DEBUG_RunClass_MESSAGES)
  std::cout << "Width: " << width << std::endl;
  if((width>2) && ( width<=IMAGE_WIDTH))
    return true;
  else
    return false;
}

bool RunClass::check_height(const int height)
{
  if(DEBUG_RunClass_MESSAGES)
  std::cout << "Height: " << height << std::endl;

  if((height>2) && ( height<=IMAGE_HEIGHT))
    return true;
  else
    return false;
}



bool RunClass::check_threshold(const int threshold)
{
  if(DEBUG_RunClass_MESSAGES)
  std::cout << "Threshold: " << threshold << std::endl;

  if((threshold>=0) && ( threshold<=MAX_LEVEL))
    return true;
  else
    return false;
}
void RunClass::set_steps_i(int value)
{
    steps_i=value;
}

void RunClass::set_steps_j(int value)
{
    steps_j=value;
}
void RunClass::set_width_i(int value)
{
    width_i=value;
}
void RunClass::set_height_j(int value)
{
    height_j=value;
}
void RunClass::set_threshold(int value)
{
    threshold=value;
}

int RunClass::get_steps_i()
{
    return steps_i;
}
int RunClass::get_steps_j()
{
    return steps_j;
}
int RunClass::get_width_i()
{
    return width_i;
}
int RunClass::get_height_j()
{
    return height_j;
}
int RunClass::get_threshold()
{
    return threshold;
}

bool RunClass::check_if_image_ok()
{
    int count=0; //check if gray image

    Input->ReadFromFile( image_filename.c_str());
    if(Input->TellHeight()!=IMAGE_HEIGHT)
    {
        if(DEBUG_RunClass_MESSAGES)
        std::cout << "Vertical size of the image is not ok" <<  std::endl;
        return false;
    }

    if(Input->TellWidth()!=IMAGE_WIDTH)
    {
        if(DEBUG_RunClass_MESSAGES)
        std::cout << "Horizontal size of the image is not ok" <<  std::endl;
        return false;
    }

    for( int j=0 ; j < Input->TellHeight() ; j++)
    {
        for( int i=0 ; i < Input->TellWidth() ; i++)
        {
            if(((*Input)(i,j)->Red != (*Input)(i,j)->Green) || ((*Input)(i,j)->Red != (*Input)(i,j)->Blue) || ((*Input)(i,j)->Green != (*Input)(i,j)->Blue))
                count++;
        }
    }
    if(count>0)
    {
        if(DEBUG_RunClass_MESSAGES)
        std::cout << "Number of pixels not gray: " << count << std::endl;
        return false;
    }
    else
      return true;
    // subtract background image
}

bool RunClass::check_if_background_image_ok()
{
    int count=0; //check if gray image
    Subtract->ReadFromFile( background_image_filename.c_str());

    if(Subtract->TellHeight()!=IMAGE_HEIGHT)
    {
        if(DEBUG_RunClass_MESSAGES)
        std::cout << "Vertical size of the background is not ok" <<  std::endl;
        return false;
    }

    if(Subtract->TellWidth()!=IMAGE_WIDTH)
    {
        if(DEBUG_RunClass_MESSAGES)
        std::cout << "Horizontal size of the background is not ok" <<  std::endl;
        return false;
    }

    for( int j=0 ; j < Subtract->TellHeight() ; j++)
    {
        for( int i=0 ; i < Subtract->TellWidth() ; i++)
        {
            if(((*Subtract)(i,j)->Red != (*Subtract)(i,j)->Green) || ((*Subtract)(i,j)->Red != (*Subtract)(i,j)->Blue) || ((*Subtract)(i,j)->Green != (*Subtract)(i,j)->Blue))
                count++;
        }
    }
    if(count>0)
    {
        if(DEBUG_RunClass_MESSAGES)
        std::cout << "Number of pixels not gray: " << count << std::endl;
        return false;
    }
    else
      return true;
    // subtract background image
}

std::string RunClass::get_image_filename()
{
    return image_filename;
}
std::string RunClass::get_output_filename()
{
    return output_filename;
}
std::string RunClass::get_background_image_filename()
{
    return background_image_filename;
}


std::string RunClass::set_image_filename(std::string s)
{
    image_filename=s;
    if(DEBUG_RunClass_MESSAGES)
    std::cout << "Image filename: " << image_filename << std::endl;
    return image_filename;
}
std::string RunClass::set_output_filename(std::string s)
{
    output_filename=s;
    if(DEBUG_RunClass_MESSAGES)
    std::cout << "Output image filename: " << output_filename << std::endl;
    return output_filename;
}
std::string RunClass::set_background_image_filename(std::string s)
{
    background_image_filename=s;
    if(DEBUG_RunClass_MESSAGES)
    std::cout << "Background image filename: " << background_image_filename << std::endl;
    return background_image_filename;
}

 void RunClass::PrintDetails()
 {
     std::cout << "*************************************************************************" << std::endl;
     std::cout << "Run Class details:" << std::endl;
     std::cout << "Image file name: " << image_filename << std::endl;
     std::cout << "Background image file name: " << background_image_filename << std::endl;
     std::cout << "Output image file name: " << output_filename << std::endl;
     std::cout << "Width of Otsu's algorithm: " << width_i << std::endl;
     std::cout << "Height of Otsu's algorithm: " << height_j << std::endl;
     std::cout << "Manual threshold for Otsu's algorithm: " << threshold << std::endl;
     std::cout << "Number of steps in horizontal direction for Otsu's algorithm: " << steps_i << std::endl;
     std::cout << "Number of steps in vertical direction for Otsu's algorithm: " << steps_j << std::endl;
     std::cout << "*************************************************************************" << std::endl;



 }
void RunClass::set_number_of_steps()
{

    steps_i = Input->TellWidth()/width_i; // how many steps in horizontal direction
    steps_j = Input->TellHeight()/height_j; // how many steps in vertical direction
    if(DEBUG_RunClass_MESSAGES)
    {
        std::cout << "Number of steps in horizontal direction: " << steps_i << std::endl;
        std::cout << "Number of steps in vertical direction: " << steps_j << std::endl;
    }
}


void RunClass::prepare_output_image()
{
    if(DEBUG_RunClass_MESSAGES)
    std::cout << "Preparing output image with all black pixels" << std::endl;
    Output = new BMP();
    Output->ReadFromFile(image_filename.c_str());
    for( int j=0 ; j < Output->TellHeight() ; j++)
    {
        for( int i=0 ; i < Output->TellWidth() ; i++)
        {
           (*Output)(i,j)->Red=0;
           (*Output)(i,j)->Green=0;
           (*Output)(i,j)->Blue=0;
        }
    }
}


void RunClass::reverse_output_image()
{
    RGBApixel p;
    for( int j=0 ; j < Output->TellHeight() ; j++)
    {
     for (int i = 0; i < Output->TellWidth(); i++)
     {
      p=Output->GetPixel(i,j);

        p.Red = 255-p.Red;
        p.Green = 255-p.Green;
        p.Blue = 255-p.Blue;
        Output->SetPixel(i, j, p);

     }
    }
}
void RunClass::write_output_image()
{
    Output->WriteToFile(output_filename.c_str()); // write output file
}

void RunClass::write_output_image(std::string name)
{
    Output->WriteToFile(name.c_str()); // write output file
}


BMP* RunClass::get_output_image_pointer()
{
    return Output;
}


BMP* RunClass::get_input_image_pointer()
{
    return Input;
}

bool RunClass::load_scene(std::string filename)
{
       SetEasyBMPwarningsOff();  // disable warnings comming from EasyBMP
    //image_filename=filename;
    if(Input->ReadFromFile(image_filename.c_str()))
     return true;
    else
    return false; // error
}
