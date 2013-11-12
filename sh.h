///code to evaluate real spherical harmonics, with additional math helper functions
///copyright 2009 Christopher Pugh

#ifndef VIRTUOSO_SPHERICAL_HARMONICS_H_INCLUDED
#define VIRTUOSO_SPHERICAL_HARMONICS_H_INCLUDED


//evaluates the real spherical harmonic of band l, index m, at spherical coordinates theta, phi
double sphericalHarmonicsEvaluate(const unsigned int& l, const int& m, const double& theta, const double& phi);

//evaluates the real legendre polynomial of band l, index m, at x
double legendreEvaluate(const unsigned int& l, const unsigned int& m, const double& x);
 
unsigned int doubleFactorial(unsigned int in);

///converts a coefficient index to an l,m pair
void SHCoeffCountToBandIndex(const unsigned int& i, int x[2]);

//integer power function
double exponential(const double base, const int pow);

//integer factorial function
unsigned int factorial( const unsigned int& in);

double shNormConstant(const  int& l, const int&m);



  
#endif