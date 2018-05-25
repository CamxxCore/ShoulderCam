#include "stdafx.h"

namespace Utility {
float Math::getDistance( vec3_t point1, vec3_t point2 ) {
    return sqrt( ( point1[0] - point2[0] ) * ( point1[0] - point2[0] ) +
                 ( point1[1] - point2[1] ) * ( point1[1] - point2[1] ) +
                 ( point1[2] - point2[2] ) * ( point1[2] - point2[2] ) );
}

void Math::anglesToForward( vec3_t angles, unsigned int diff, vec3_t& result ) {
    float num = static_cast<float>( sin( angles[0] * M_PI / 180 ) ) * diff;
    float num1 = static_cast<float>( sqrt( diff * diff - num * num ) );
    float num2 = static_cast<float>( sin( angles[1] * M_PI / 180 ) ) * num1;
    float num3 = static_cast<float>( cos( angles[1] * M_PI / 180 ) ) * num1;
    result[0] = num3;
    result[1] = num2;
    result[2] = num;
}

void Math::lerp( const vec3_t start, const vec3_t end, float amount, vec3_t& result ) {
    result[0] = start[0] + ( end[0] - start[0] ) * amount;
    result[1] = start[1] + ( end[1] - start[1] ) * amount;
    result[2] = start[2] + ( end[2] - start[2] ) * amount;
}

void Math::lerp( const float start, const float end, float amount, float& result ) {
    result = start + ( end - start ) * amount;
}

void Math::smoothStep( const float start, const float end, float amount, float & result ) {
    amount = ( amount > 1.0f ) ? 1.0f : ( ( amount < 0.0f ) ? 0.0f : amount );
    amount = ( amount * amount ) * ( 3.0f - ( 2.0f * amount ) );
    result = start + ( ( end - start ) * amount );
}

void Math::vectorToAngles( vec3_t vec, vec3_t& result ) {
    float yaw;
    float pitch;
    float PiDiv = 180.0f / ( float )M_PI;

    if ( vec[1] == 0 && vec[0] == 0 ) {
        yaw = 0.0F;
        if ( vec[2] > 0 )
            pitch = 90.0F;
        else
            pitch = 270.0F;
    } else {
        if ( vec[0] > 0 )
            yaw = ( float )( atan2( vec[1], vec[0] ) * PiDiv );
        else if ( vec[1] > 0 )
            yaw = 90.0f;
        else
            yaw = 270.0f;
        if ( yaw < 0.0f )
            yaw += 360.0f;
        float forward = ( float )sqrt( vec[0] * vec[0] + vec[1] * vec[1] );
        pitch = ( float )( atan2( vec[2], forward ) * PiDiv );
        if ( pitch < 0.0f )
            pitch += 360;
    }

    auto v = vec3_t{ 360.0f - pitch, yaw, 0.0f };

    for ( int i = 0; i < 2; i++ ) {
        if ( v[i] > 360.0f )
            v[i] -= 360.0f;
        if ( v[i] < 0.0f )
            v[i] += 360.0f;
    }

    VectorCopy( v, result );
}

void Math::vectorNormalize( vec3_t& v ) {
    auto length = sqrt( v[0] * v[0] + v[1] * v[1] + v[2] * v[2] );

    float num = 1 / length;

    v[0] *= num;
    v[1] *= num;
    v[2] *= num;
}

bool Math::pointInSphere( vec3_t origin, vec3_t point, float radius ) {
    auto goal = origin;

    auto dx = ( point[0] - goal[0] );
    dx = dx * dx;

    auto dy = ( point[1] - goal[1] );
    dy = dy * dy;

    auto dz = ( point[2] - goal[2] );
    dz = dz * dz;

    auto left = ( dx + dy + dz );
    auto right = radius * radius;

    return left < right;
}
}
