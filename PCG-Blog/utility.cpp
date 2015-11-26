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

double Utility::scale( double value, double min, double max ) {
    return ( value - min ) / ( max - min );
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


