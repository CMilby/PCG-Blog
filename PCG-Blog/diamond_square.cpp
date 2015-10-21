//
//  diamond_square.cpp
//  PCG-Blog
//
//  Created by Craig Milby on 10/13/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "diamond_square.h"

#include <pngwriter.h>

#define MAX_VALUE 65535

DiamondSquare::DiamondSquare( unsigned int size ) {
    m_size = size;
    
    float magnitude = 1;
    populate_map();
    diamond_square( Point( 0, 0 ), Point( m_size - 1, 0 ), Point( 0, m_size - 1 ), Point( m_size - 1, m_size - 1 ), magnitude );
}

void DiamondSquare::diamond_square( const Point &p1, const Point &p2, const Point &p3, const Point &p4, float magnitude ) {
    int space = m_size - 1;
    int halfSpace;
    
    while ( space > 1 ) {
        halfSpace = space / 2;
        
        for ( unsigned int i = halfSpace; i < m_size; i+= space ) {
            for ( unsigned int j = halfSpace; j < m_size; j+= space ) {
                m_map[ point_to_single( i, j ) ] = square_step( i, j, halfSpace, magnitude );
            }
        }
        
        for ( unsigned int i = 0; i < m_size; i += halfSpace ) {
            int jStart = ( ( i / halfSpace ) % 2 == 0 ) ? halfSpace : 0;
            for ( unsigned int j = jStart; j < m_size; j += space ) {
                if ( m_map[ point_to_single( i, j ) ] == -1 ) {
                    m_map[ point_to_single( i, j ) ] = diamond_step( i, j, halfSpace, magnitude );
                }
            }
        }
        space = halfSpace;
    }
}

int DiamondSquare::square_step( unsigned int i, unsigned int j, int halfSpace, float magnitude ) {
    int a = m_map[ point_to_single( i - halfSpace, j - halfSpace ) ];
    int b = m_map[ point_to_single( i - halfSpace, j + halfSpace ) ];
    int c = m_map[ point_to_single( i + halfSpace, j - halfSpace ) ];
    int d = m_map[ point_to_single( i + halfSpace, j + halfSpace ) ];
    float noise = magnitude * halfSpace * Utility::random_in_range( 0.1f, 1.0f );
    return ( a + b + c + d ) / 4 + noise;
}

int DiamondSquare::diamond_step( unsigned int i, unsigned int j, int halfSpace, float magnitude ) {
    int a, b, c;
    float noise = magnitude * halfSpace * Utility::random_in_range( 0.1f, 1.0f );
    
    if ( i == 0 ) {
        a = m_map[ point_to_single( i, j + halfSpace ) ];
        b = m_map[ point_to_single( i, j - halfSpace ) ];
        c = m_map[ point_to_single( i + halfSpace, j ) ];
        return ( a + b + c ) / 3 + noise;
    }
    
    if ( i == m_size - 1 ) {
        a = m_map[ point_to_single( i, j + halfSpace ) ];
        b = m_map[ point_to_single( i, j - halfSpace ) ];
        c = m_map[ point_to_single( i - halfSpace, j ) ];
        return ( a + b + c ) / 3 + noise;
    }
    
    if ( j == 0 ) {
        a = m_map[ point_to_single( i + halfSpace, j ) ];
        b = m_map[ point_to_single( i - halfSpace, j ) ];
        c = m_map[ point_to_single( i, j + halfSpace ) ];
        return ( a + b + c ) / 3 + noise;
    }
    
    if ( j == m_size - 1 ) {
        a = m_map[ point_to_single( i + halfSpace, j ) ];
        b = m_map[ point_to_single( i - halfSpace, j ) ];
        c = m_map[ point_to_single( i, j - halfSpace ) ];
        return ( a + b + c ) / 3 + noise;
    }
    
    a = m_map[ point_to_single( i, j + halfSpace ) ];
    b = m_map[ point_to_single( i, j - halfSpace ) ];
    c = m_map[ point_to_single( i + halfSpace, j ) ];
    int d = m_map[ point_to_single( i - halfSpace, j ) ];
    return ( a + b + c + d ) / 4 + noise;
}

int DiamondSquare::point_to_single( int x, int y ) const {
    return x + m_size * y;
}

int DiamondSquare::point_to_single( const Point &point ) const {
    return point_to_single( point.m_x, point.m_y );
    
}

std::vector<std::string> DiamondSquare::get_map() const {
    std::vector<std::string> map;
    
    for ( unsigned int i = 0; i < m_map.size(); i++ ) {
        map.emplace_back( std::to_string( m_map[ i ] ) );
    }
    
    return map;
}

void DiamondSquare::populate_map() {
    for ( unsigned int i = 0; i < m_size; i++ ) {
        for ( unsigned int j = 0; j < m_size; j++ ) {
            m_map.emplace_back( -1 );
        }
    }
    
    m_map[ point_to_single( 0, 0 ) ] = Utility::random_in_range( 0, MAX_VALUE );
    m_map[ point_to_single( 0, m_size - 1 ) ] = Utility::random_in_range( 0, MAX_VALUE );
    m_map[ point_to_single( m_size - 1, 0 ) ] = Utility::random_in_range( 0, MAX_VALUE );
    m_map[ point_to_single( m_size - 1, m_size - 1 ) ] = Utility::random_in_range( 0, MAX_VALUE );
}

bool DiamondSquare::is_valid( const Point &point ) {
    return is_valid( point.m_x, point.m_y );
}

bool DiamondSquare::is_valid( int x, int y ) {
    if ( x < 0 || y < 0 )
        return false;
    if ( x > m_size || y > m_size )
        return false;
    return true;
}

void DiamondSquare::to_png( const std::string &file ) {
    pngwriter png( m_size, m_size, 0, file.c_str() );
    
    for ( unsigned int i = 0; i < m_size; i++ ) {
        for ( unsigned int j = 0; j < m_size; j++ ) {
            int value = m_map[ i * m_size + j ];
            png.plot( j + 1, i + 1, 0, value, 0 );
        }
    }
    
    png.close();
}












