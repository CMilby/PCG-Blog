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

class Vector3 {

public:
    float m_x;
    float m_y;
    float m_z;
    
    Vector3() {
        m_x = m_y = m_z = 0.0f;
    }
    
    Vector3( float x, float y, float z ) {
        m_x = x;
        m_y = y;
        m_z = z;
    }
    
    inline Vector3 operator-( const Vector3 &vect ) const {
        return Vector3( m_x - vect.m_x, m_y - vect.m_y, m_z - vect.m_z );
    }
};

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
    
    inline Point operator-( const Point &p ) const {
        return Point( m_x - p.m_x, m_y - p.m_y );
    }
};

namespace Utility {
    
    extern unsigned int OFFSET_BASIS;
    extern unsigned int FNV_PRIME;
    
    void print_map( const std::vector<char> &map, unsigned int width, unsigned int height );
    void print_map( const std::vector<std::string> &map, unsigned int width, unsigned int height );
    
    std::vector<char> blank_map( char delim, unsigned int width, unsigned int height );
    
    float scale( float x, float a, float b, float min, float max );
    float min( const std::vector<float> &vect );
    float max( const std::vector<float> &vect );
    
    int random_in_range( int min, int max );
    float random_in_range( float min, float max );
    unsigned int lcg_random( unsigned int last );
    
    int clamp( int value, int min, int max );
    float clampf( float value, float min, float max );
    
    float dot( const int *g, const float x, const float y, const float z );
    int fast_floor( const float x );
}

#endif
