///code to perform projection of environment map images to sh coefficients, and to project sh coefficients to environment maps
///using discrete SH transform
///copyright 2009 Christopher Pugh

#ifndef VIRTUOSO_SH_PROJECTION_H_INCLUDED
#define VIRTUOSO_SH_PROJECTION_H_INCLUDED

#ifdef VIRTUOSO_IMAGE_AVAILABLE
#include <image.h>
#endif

///it's important to know that if you're using rgb, each "coefficient" is an rgb triple, so you need to pass in as coefficients an array that holds numCoefficients*channels values

void projectLatLongMap(float* image, unsigned int width, unsigned int height, unsigned int channels, double* coefficients, unsigned int numCoefficients);

void createLatLongMap(float* pixels, unsigned int width, unsigned int height, unsigned int channels, double* coefficients, unsigned int numCoefficients);


#ifdef VIRTUOSO_IMAGE_AVAILABLE
void projectLatLongMap(const FloatImage& latLong, double* coefficientsBegin, unsigned int numCoefficients);

FloatImage createLatLongMap(const FloatImage::index_type&, double* coefficientsBegin, unsigned int numCoefficients};

#endif


#endif
