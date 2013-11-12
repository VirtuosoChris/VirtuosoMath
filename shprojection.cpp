///inline implementation of code to project environment map images to sh coefficients, and to project sh coefficients to environment maps
///copyright 2009 chris pugh

#include "shprojection.h"
#include "sh.h"

const double fourPi = 4* 3.14159;
void createLatLongMap(float* pixels, unsigned int width, unsigned int height, unsigned int channels, double* coefficients, unsigned int numCoefficients)
{
    const unsigned int numPixels = width*height;

    for(unsigned int pixel = 0; pixel < numPixels; pixel++)
    {
        //clear the pixel prior to summation
        for(unsigned int ch = 0; ch < channels; ch++)
        {
            pixels[pixel * channels + ch] =0.0;
        }

        double u = double(pixel%width) / width;
        double v = double(pixel /width) / height;

        double th =  2*3.14159*u;
        double phi = 3.14159*v;

        double smc = 0.0;

        int band_index[2]; //the band and index array to store for the SH coefficients


        for( int coeff = 0; coeff < numCoefficients; coeff++)
        {
            SHCoeffCountToBandIndex(coeff,band_index);

            double sh = sphericalHarmonicsEvaluate(band_index[0],band_index[1], th, phi);

            for(unsigned int ch = 0; ch < channels; ch++)
            {
                pixels[pixel * channels + ch] += coefficients[coeff*channels +ch] * sh;
            }

        }


    }
}


#ifdef VIRTUOSO_IMAGE_AVAILABLE
FloatImage createLatLongMap(const FloatImage::index_type&, double* coefficientsBegin, unsigned int numCoefficients)
{
    FloatImage latLong(dimensions);

    const FloatImage::index_type dims = latLong.getDimensions();

    createLatLongMap(latLong.dataPtr(),dims[1],dims[2],dims[0],coefficients,numCoefficients);

    return latLong;

}


void projectLatLongMap(const FloatImage& latLong, double* coefficientsBegin, unsigned int numCoefficients)
{

    const unsigned int& channels = latLong.getDimensions()[0];
    const unsigned int& width = latLong.getDimensions()[1];
    const unsigned int& height = latLong.getDimensions()[2];

    projectLatLongMap(latLong.dataPtr(), width, height, channels, coefficientsBegin, numCoefficients);

}

#endif

void projectLatLongMap(float* image, unsigned int width, unsigned int height, unsigned int channels, double* coefficients, unsigned int numCoefficients)
{

    const unsigned int numPixels = width*height;

    //zero the coefficients prior to summation
    for(unsigned int i = 0; i < numCoefficients * channels; i++)
    {
        coefficients[i] = 0.0;
    }

    int band_index[2]; //the band and index array to store for the SH coefficients

    //iterate through the pixels and compute the coefficients
    for(unsigned int pixel = 0; pixel < numPixels; pixel++)
    {
        //get normalized image coordinates

        double u = double(pixel % width)  / width;
        double v = double(pixel / width ) / height;

        //convert normalized image coordinates to angular coordinates
        double th =  2*3.14159*u;
        double phi = 3.14159*v;

        for( int coeff = 0; coeff < numCoefficients; coeff++)
        {

            SHCoeffCountToBandIndex(coeff,band_index);

            double add =  (fourPi / numPixels) * sphericalHarmonicsEvaluate(band_index[0],band_index[1],th,phi);

            for(unsigned int ch = 0; ch < channels; ch++)
            {

                float imageRead = image[pixel*channels + ch];

                coefficients[ coeff*channels + ch] += add * imageRead;
            }

        }
    }


}

