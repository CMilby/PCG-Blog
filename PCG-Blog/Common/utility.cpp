//
//  utility.cpp
//  PCG-Blog
//
//  Created by Craig Milby on 10/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "utility.h"

unsigned int Utility::OFFSET_BASIS = 2166136261;
unsigned int Utility::FNV_PRIME = 16777619;

void Utility::print_map( const std::vector<char> &map, unsigned int width, unsigned int height ) {
    for ( unsigned int i = 0; i < height; i++ ) {
        for ( unsigned int j = 0; j < width; j++ ) {
            std::cout << map[ i * width + j ];
        }
        std::cout << "\n";
    }
}

void Utility::print_map( const std::vector<std::string> &map, unsigned int width, unsigned int height ) {
    for ( unsigned int i = 0; i < height; i++ ) {
        for ( unsigned int j = 0; j < width; j++ ) {
            std::cout << map[ i * width + j ] << " ";
        }
        std::cout << "\n";
    }
}

std::vector<char> Utility::blank_map( char delim, unsigned int width, unsigned int height ) {
    std::vector<char> map;
    for ( int i = 0; i < width; i++ ) {
        for ( int j = 0; j < height; j++ ) {
            map.push_back( delim );
        }
    }
    return map;
}

float Utility::scale( float x, float a, float b, float min, float max ) {
     return ( ( ( b - a ) * ( x - min ) ) / ( max - min ) ) + a;
}

float Utility::min( const std::vector<float> &vect ) {
    int min = vect[ 0 ];
    for ( unsigned int i = 1; i < vect.size(); i++ ) {
        if ( vect[ i ] < min ) {
            min = vect[ i ];
        }
    }
    return min;
}

float Utility::max( const std::vector<float> &vect ) {
    int max = vect[ 0 ];
    for ( unsigned int i = 1; i < vect.size(); i++ ) {
        if ( vect[ i ] > max ) {
            max = vect[ i ];
        }
    }
    return max;
}

int Utility::random_in_range( int min, int max ) {
    return rand() % ( max - min + 1 ) + min;
}

float Utility::random_in_range( float min, float max ) {
    float random = ( (float ) rand() ) / ( float ) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}

int Utility::clamp( int value, int min, int max ) {
    if ( value < min )
        return min;
    if ( value > max )
        return max;
   return value;
}

float Utility::clampf( float value, float min, float max ) {
    if ( value < min )
        return min;
    if ( value > max )
        return max;
    return value;
}

float Utility::dot( const int *p_g, const float p_x, const float p_y ) {
    return p_g[ 0 ] * p_y + p_g[ 1 ] * p_y;
}

float Utility::dot( const int *g, const float x, const float y, const float z ) {
    return g[ 0 ] * x + g[ 1 ] * y + g[ 2 ] * z;
}

int Utility::fast_floor( const float x ) {
    return x > 0 ? ( int ) x : ( int ) x - 1;
}

float Utility::distance( const int p_x1, const int p_y1, const int p_x2, const int p_y2 ) {
	return sqrtf( powf( p_x2 - p_x1, 2.0f ) + powf( p_y2 - p_y1, 2.0f ) );
}

