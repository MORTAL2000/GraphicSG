/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2004 Robert Osfield 
*
* This library is open source and may be redistributed and/or modified under  
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
* (at your option) any later version.  The full license is in LICENSE file
* included with this distribution, and on the openscenegraph.org website.
* 
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
* OpenSceneGraph Public License for more details.
*/

#ifndef __VR_MATH
#define __VR_MATH

#include <math.h>

// for OSX users :
// comment in if you want backwards compatibility with 10.1.x versions
// otherwise you'll have problems with missing floorf and __isnan*()
// #define APPLE_PRE_10_2

#if defined(_MSC_VER)
#include <float.h>
#endif

#if defined (sun) || defined (__APPLE__)

#include <float.h>

#ifndef acosf
inline float acosf(float value) { return static_cast<float>(acos(value)); }
#endif

#ifndef asinf
inline float asinf(float value) { return static_cast<float>(asin(value)); }
#endif

#ifndef cosf
inline float cosf(float value) { return static_cast<float>(cos(value)); }
#endif

#ifndef sinf
inline float sinf(float value) { return static_cast<float>(sin(value)); }
#endif

#ifndef logf
inline float logf(float value) { return static_cast<float>(log(value)); }
#endif

#ifndef powf
inline float powf(float value1,float value2) { return static_cast<float>(pow(value1,value2)); }
#endif

#ifndef sqrtf
inline float sqrtf(float value) { return static_cast<float>(sqrt(value)); }
#endif

#ifndef fabsf
inline float fabsf(float value) { return static_cast<float>(fabs(value)); }
#endif

#ifndef atan2f
inline float atan2f(float value1, float value2) { return static_cast<float>(atan2(value1,value2)); }
#endif

#endif


#if defined (sun) || \
  defined (__hpux) || \
  defined (APPLE_PRE_10_2)

#ifndef floorf
inline float floorf(float value) { return static_cast<float>(floor(value)); }
#endif

#endif

namespace vr {

  // define the standard trig values
#ifdef PI
#undef PI
#undef PI_2
#undef PI_4
#endif
  const double PI   = 3.14159265358979323846;
  const double PI_2 = 1.57079632679489661923;
  const double PI_4 = 0.78539816339744830962;

  /** return the minimum of two values, equivalent to std::min.
  * std::min not used because of STL implementation under IRIX not
  * containing std::min.
  */
  template<typename T>
    inline T absolute(T v) { return v<(T)0?-v:v; }

    /** return true if float lhs and rhs are equivalent,
    * meaning that the difference between them is less than an epsilon value
    * which defaults to 1e-6.
    */
    inline float equivalent(float lhs,float rhs,float epsilon=1e-6)
    { float delta = rhs-lhs; return delta<0.0f?delta>=-epsilon:delta<=epsilon; }

    /** return true if double lhs and rhs are equivalent,
    * meaning that the difference between them is less than an epsilon value
    * which defaults to 1e-6.
    */
    inline double equivalent(double lhs,double rhs,double epsilon=1e-6)
    { double delta = rhs-lhs; return delta<0.0?delta>=-epsilon:delta<=epsilon; }

    /** return the minimum of two values, equivilent to std::min.
    * std::min not used because of STL implementation under IRIX not containing
    * std::min.
    */
    template<typename T>
      inline T minimum(T lhs,T rhs) { return lhs<rhs?lhs:rhs; }

      /** return the maximum of two values, equivilent to std::max.
      * std::max not used because of STL implementation under IRIX not containing
      * std::max.
      */
      template<typename T>
        inline T maximum(T lhs,T rhs) { return lhs>rhs?lhs:rhs; }

        template<typename T>
          inline T clampTo(T v,T minimum,T maximum)
        { return v<minimum?minimum:v>maximum?maximum:v; }

        template<typename T>
          inline T clampAbove(T v,T minimum) { return v<minimum?minimum:v; }

          template<typename T>
            inline T clampBelow(T v,T maximum) { return v>maximum?maximum:v; }

            template<typename T>
              inline T clampBetween(T v,T minimum, T maximum)
            { return clampBelow(clampAbove(v,minimum),maximum); }

            template<typename T>
              inline T sign(T v) { return v<(T)0?(T)-1:(T)1; }

              template<typename T>
                inline T square(T v) { return v*v; }

                template<typename T>
                  inline T signedSquare(T v) { return v<(T)0?-v*v:v*v;; }

                  inline float inDegrees(float angle) { return angle*(float)PI/180.0f; }
                  inline double inDegrees(double angle) { return angle*PI/180.0; }

                  template<typename T>
                    inline T inRadians(T angle) { return angle; }

                    inline float DegreesToRadians(float angle) { return angle*(float)PI/180.0f; }
                    inline double DegreesToRadians(double angle) { return angle*PI/180.0; }

                    inline float RadiansToDegrees(float angle) { return angle*180.0f/(float)PI; }
                    inline double RadiansToDegrees(double angle) { return angle*180.0/PI; }

#if defined(WIN32) && !defined(__CYGWIN__) && !defined(__MWERKS__)
                    inline bool isNaN(float v) { return _isnan(v)!=0; }
                    inline bool isNaN(double v) { return _isnan(v)!=0; }
#else
# if defined(__APPLE__) && !defined (APPLE_PRE_10_2)
                    inline bool isNaN(float v) { return __isnanf(v); }
                    inline bool isNaN(double v) { return __isnand(v); }
#else
                    inline bool isNaN(float v) { return isnan(v); }
                    inline bool isNaN(double v) { return isnan(v); }
#endif
#endif


                    /** compute the volume of a tetrahedron. */
                    template<typename T>
                      inline float computeVolume(const T& a,const T& b,const T& c,const T& d)
                    {
                      return fabsf(((b-c)^(a-b))*(d-b));
                    }

                    /** compute the volume of a prism. */
                    template<typename T>
                      inline float computeVolume(const T& f1,const T& f2,const T& f3,
                      const T& b1,const T& b2,const T& b3)
                    {
                      return computeVolume(f1,f2,f3,b1)+
                        computeVolume(b1,b2,b3,f2)+
                        computeVolume(b1,b3,f2,f3);
                    }

}

#endif  // __OSG_MATH

