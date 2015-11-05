//
//  utility.h
//  PCG-Blog
//
//  Created by Craig Milby on 10/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>
#include <vector>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))

class Point {
    
public:
    int m_x;
    int m_y;
    
    Point() {
        m_x = m_y = 0;
    }
    
    Point( int x, int y ) {
        m_x = x;
        m_y = y;
    }
};

namespace Utility {
    
    void print_map( const std::vector<char> &map, unsigned int width, unsigned int height );
    void print_map( const std::vector<std::string> &map, unsigned int width, unsigned int height );
    
    std::vector<char> blank_map( char delim, unsigned int width, unsigned int height );
    
    double scale( double value, double min, double max );
    
    int random_in_range( int min, int max );
    float random_in_range( float min, float max );
    int clamp( int value, int min, int max );
}

#endif
