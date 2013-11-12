///code to evaluate real spherical harmonics, with additional math helper functions
///copyright 2009 Christopher Pugh

#include "sh.h"


const double fourPi = 4* 3.14159;

unsigned int doubleFactorial(unsigned int in){

	int result = 1;
    for(int i = in; i > 1; i-= 2){
        result *= i;
    }
    return result;
}


//integer factorial function
unsigned int factorial( const unsigned int& in){

 int result = 1;
    for(int i = in; i > 0; i--){
            result *= i;
    }

    return result;
}


void SHCoeffCountToBandIndex(const unsigned int& i, int x[2]){

 int& l = x[0];
 int& m = x[1];

     l = floor(sqrt(i));
     m = (i - (l*l)) - l;

}


double sphericalHarmonicsEvaluate(const unsigned int& l, const int& m, const double& theta, const double& phi){
    const double root2 =sqrt(2);

	double result = 0.0;
   
   if(m >0){
        result =  root2 * shNormConstant(l,m) * cos(double(m)*theta) * legendreEvaluate(l,m,cos(phi));
    }else if(m < 0){
        result =  root2 * shNormConstant(l,-m) * sin(double(-m)*theta) * legendreEvaluate(l,-m,cos(phi));
    }
    else{
        result= shNormConstant(l, 0) * legendreEvaluate(l, 0, cos(phi));
    }
 
return result;
}


//evaluates the real legendre polynomial of band l, index m, at x
double legendreEvaluate(const unsigned int& l, const unsigned int& m, const double& x){
 
	double r = 1.0;
	
	if(m == 0) r = 1; //base case legendre polynomial(0,0)
	
	else{
	   r =  exponential(-1.0, m) * doubleFactorial(2*m - 1) * pow(1.0 - x*x, .5 * double(m));
	}

    if(l==m) return r;

    //calculate the legendre polynomial at the point up one band
   double rmPlusOne = x* double(2*m + 1) * r;

   if(l == m+1) return rmPlusOne; //lf l is m+1 we're done

    for(unsigned int i = m+2; i <= l; i++){

       double temp = rmPlusOne;
       rmPlusOne =  x*double(2*i-1)*rmPlusOne - double((i+m-1))*r;
       rmPlusOne /= double(i-m);
       r = temp;

    }

return rmPlusOne;

}



//integer power function
double exponential(const double base, const int pow){

//break cases
if(base == 0.0)return 0;
if(base == 1.0 || pow == 0)return 1.0;
if(pow == 1.0)return base;

//unsigned int extra = 0;
unsigned int loops = 0;
unsigned int div = pow >0?pow:-pow;
unsigned int pow2 = div;

while( div > 1){
    //if(div%2)extra++;
    div>>=1;
    loops++;
}

double result = base;
unsigned int sExt = 1;

for(unsigned int i = 0; i < loops; i++){
  result*= result;

  sExt <<= 1;

}

for(unsigned int i = 0; i < pow2 - sExt; i++){
    result *= base;
}

return pow >0?result: (1.0 / result);

}



inline double shNormConstant(const  int& l, const int&m){

 return    sqrt(double ((2*l+1)*factorial(l - m)) / (fourPi * factorial(l+m)));

}

