//
//  utility.cpp
//  PCG-Blog
//
//  Created by Craig Milby on 10/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "utility.h"

void Utility::print_map( const std::vector<char> &map, unsigned int width, unsigned int height ) {
    for ( unsigned int i = 0; i < width; i++ ) {
        for ( unsigned int j = 0; j < height; j++ ) {
            std::cout << map[ i * width + j ];
        }
        std::cout << "" << std::endl;
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

int Utility::random_in_range( int min, int max ) {
    return rand() % ( max - min + 1 ) + min;
}