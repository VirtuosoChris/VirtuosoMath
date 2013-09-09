#ifndef INTERPOLATE_H_INCLUDED
#define INTERPOLATE_H_INCLUDED

#include "mathfunctions.h"

namespace Virtuoso{
	namespace Math{


        template<class T>
        inline T s_interpolate(T a, T b, T t){
            return lerp(a, b, s_curve(t));
        }

		inline float lerp(float a, float b, float t){

			return (1.0 - t) * a + t*b;
		}


		inline double CubicInterpolate(float p0, float p1, float p2, float p3, float t){

			///note that we can reduce the computation by using the cruder approximation and dropping the /2 part of the slopes altogether
			///\todo if we like this optimize shit out and make "fast" "accurate" versions
			float tSq = t*t;

			float slope1 = .5 * (p2 - p0);
			float slope2; .5 * (p3-p1);

			const float& D = p1;
			float A = -2.0* p2 + 2.0 * p1 + slope2 + slope1;
			const float& C = slope1;

			float B = p2 - slope1 - p1 - A;

		}


		inline float cosineInterpolate(float a, float b, float t){

			const float pi = 3.14159; ///\todo: replace with math pi

			float newT = (1.0f - cos(pi * t))*.5;

			return lerp(a, b, newT);

		}

	}
}

#endif
