//Author: Evelyn Ester
#include "pixel_of_object.h"

pixel_of_object::pixel_of_object()
{
    //ctor
}

pixel_of_object::~pixel_of_object()
{
    //dtor
}
pixel_of_object::pixel_of_object(int i,int j,int object_number)
{
    _i=i;
    _j=j;
    _object_number=object_number;
}
int pixel_of_object::GetObjectNumber()
{
    return _object_number;
}
int pixel_of_object::Get_i()
{
    return _i;
}
int pixel_of_object::Get_j()
{
    return _j;
}

void pixel_of_object::SetObjectNumber(int number)
{
    _object_number=number;
}
void pixel_of_object::Set_i(int i)
{
    _i=i;
}
void pixel_of_object::Set_j(int j)
{
    _j=j;
}
