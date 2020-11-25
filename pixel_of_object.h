//Author: Evelyn Ester
#ifndef CLOUDCHAMBER_PIXEL_OF_OBJECT_H
#define CLOUDCHAMBER_PIXEL_OF_OBJECT_H

// keeps the information about a pixel and the track to which it belongs
// all detected tracks are stored in a vector of vectors of pixel_of_object
class pixel_of_object
{
    public:

        pixel_of_object(int i,int j,int object_number);
        pixel_of_object();

        ~pixel_of_object();
        int GetObjectNumber();
        int Get_i();
        int Get_j();
        void SetObjectNumber(int number);
        void Set_i(int i);
        void Set_j(int j);



    protected:

    private:
        int _i; // coordinate on horizontal axis
        int _j; // coordinate on vertical axis
        int _object_number; // object(track) number starting from 0
};

#endif // CLOUDCHAMBER_PIXEL_OF_OBJECT_H
