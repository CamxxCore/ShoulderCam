#pragma once

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef float vec_t;
typedef vec_t vec3_t[3];

#define VECTOR_EMPTY vec3_t{ 0, 0, 0 }

#define VectorSubtract(a,b,c) {c[0]=a[0]-b[0];c[1]=a[1]-b[1];c[2]=a[2]-b[2];}
#define VectorAdd(a,b,c) {c[0]=a[0]+b[0];c[1]=a[1]+b[1];c[2]=a[2]+b[2];}
#define VectorCopy(a,b)((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])
#define	VectorScale(v, s, o)((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define VectorCompare(a,b)((b)[0]==(a)[0],(b)[1]==(a)[1],(b)[2]==(a)[2])

namespace Utility {
class Math {
  public:
    static void anglesToForward( vec3_t angles, unsigned int diff, vec3_t& result );

    static void lerp( const vec3_t start, const vec3_t end, float amount, vec3_t& result );

    static void lerp( const float start, const float end, float amount, float& result );

    static void smoothStep( const float start, const float end, float amount, float& result );

    static void vectorToAngles( vec3_t vec, vec3_t& result );

    static float getDistance( vec3_t point1, vec3_t point2 );

    static void vectorNormalize( vec3_t& v );

    static bool pointInSphere( vec3_t origin, vec3_t point, float radius );
};
}
