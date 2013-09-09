#ifndef MATHFUNCTIONS_H_INCLUDED
#define MATHFUNCTIONS_H_INCLUDED

namespace Virtuoso{

	namespace Math{


        template <class T>
        inline T s_curve(T t){
            const float tSquared = t*t;
            return 3.0 * tSquared - 2.0 * t * tSquared;
        }


		template <class T>
        inline T randomFloatInRange(const T& min, const T& max){

            return (((T)rand() / (T)RAND_MAX) * (max-min)) + min;

        }


        template <class T>
        inline T randomIntInRange(const T& min, const T& max){

            return (rand()%(max-min) ) + min;

        }


		///o(n) quickie way to get the log 2 of a uint.  can optimize later
		inline unsigned int log2(unsigned int val){
			unsigned int ctr = 0;

			while(val>>=1){
				ctr++;
			}

			return ctr;
		}


    inline double gaussian1D(double distanceX, double stdev){

        double a = 1.0 / sqrt(2.0 * M_PI * stdev * stdev);

        //using b as 0 ///\todo explain me

        double exponent = (-distanceX * distanceX )/ (2.0 * stdev * stdev);

        return a * exp(exponent);

    }

    inline double gaussian2D(double distanceX,double distanceY, double stdev){

        return gaussian1D( distanceX , stdev) * gaussian1D(distanceY, stdev);

    }

    template <class T>///\todo this probably doesn't belong here
    inline void makeGaussianKernel1D(T kernelArray[], int kernelSize, double stdev){

        int distance = kernelSize / 2;

        double totalSum=0.0;

        for(int i = -distance, index=0; index < kernelSize; i++, index++){
            totalSum+= (kernelArray[index]=  gaussian1D(i, stdev) );
        }

        //normalize
        for(int i = 0; i < kernelSize; i++){
            kernelArray[i] /= totalSum;
        }

    }




	}

}


#endif
