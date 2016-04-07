//
//  diamond_square.cpp
//  PCG-Blog
//
//  Created by Craig Milby on 10/13/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "diamond_square.h"

#include <pngwriter.h>

DiamondSquare::DiamondSquare( unsigned int width, unsigned int height, int featureSize ) {
    m_width = width;
    m_height = height;
    
    for ( unsigned int i = 0; i < width * height; i++ ) {
        m_map.push_back( 0.0f );
    }
    
    for ( unsigned int y = 0; y < width; y += featureSize ) {
        for ( unsigned int x = 0; x < width; x += featureSize ) {
            setSample( x, y, Utility::random_in_range( -1.0f, 1.0f ) );
        }
    }
    
    int stepSize = featureSize;
    float scale = 1.0f / width;
    float scaleMod = 1.0f;
    
    do {
        diamond_square( stepSize, scale );
        
        stepSize /= 2;
        scale *= ( scaleMod + 0.8f );
        scaleMod *= 0.3;
    } while ( stepSize > 1 );
}

void DiamondSquare::diamond_square( int stepSize, float scale ) {
    int halfStep = stepSize / 2;
    for ( unsigned int y = halfStep; y < m_width + halfStep; y += stepSize ) {
        for ( unsigned int x = halfStep; x < m_width + halfStep; x += stepSize ) {
            square_step( x, y, stepSize, Utility::random_in_range( -1.0f, 1.0f ) * scale );
        }
    }
    
    for ( unsigned int y = 0; y < m_width; y += stepSize ) {
        for ( unsigned int x = 0; x < m_width; x += stepSize ) {
            diamond_step( x + halfStep, y, stepSize, Utility::random_in_range( -1.0f, 1.0f ) * scale );
            diamond_step( x, y + halfStep, stepSize, Utility::random_in_range( -1.0f, 1.0f ) * scale );
        }
    }
}

void DiamondSquare::square_step( int x, int y, int size, float value ) {
    int hs = size / 2;
    
    float a = sample( x - hs, y - hs );
    float b = sample( x + hs, y - hs );
    float c = sample( x - hs, y + hs );
    float d = sample( x + hs, y + hs );
    setSample( x, y, ( ( a + b + c + d ) / 4.0f ) + value );
}

void DiamondSquare::diamond_step( int x, int y, int size, float value ) {
    int hs = size / 2;
    
    float a = sample( x - hs, y );
    float b = sample( x + hs, y );
    float c = sample( x, y - hs );
    float d = sample( x, y + hs );
    setSample( x, y, ( ( a + b + c + d ) / 4.0f ) + value );
}

float DiamondSquare::sample( int x, int y ) {
    return m_map[ ( x & ( m_width - 1 ) ) + ( y & ( m_height - 1 ) ) * m_width ];
}

void DiamondSquare::setSample( int x, int y, float value ) {
    m_map[ ( x & ( m_width - 1 ) ) + ( y & ( m_height - 1 ) ) * m_width ] = value;
}

void DiamondSquare::to_png( const std::string &file ) {
    pngwriter png( m_width, m_height, 0, file.c_str() );

    float min = Utility::min( m_map );
    float max = Utility::max( m_map );
    
    for ( unsigned int i = 0; i < m_height; i++ ) {
        for ( unsigned int j = 0; j < m_width; j++ ) {
            double value = ( double ) m_map[ i * m_width + j ];
            value = Utility::scale( value, 0.0, 1.0, min, max );
            png.plot( i, j, value, value, value );
        }
    }
    
    png.close();
}

