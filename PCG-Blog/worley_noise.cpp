//
//  worley_noise.cpp
//  PCG-Blog
//
//  Created by Craig Milby on 11/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "worley_noise.h"

#include <cfloat>

#include <pngwriter.h>

WorleyNoise::WorleyNoise() {
    for ( int i = 0; i < 256; i++ ) {
        m_permutations[ i ] = i;
    }
    
    for ( int i = 0; i < 256; i++ ) {
        int j = m_permutations[ i ];
        int k = random_int();
        m_permutations[ i ] = m_permutations[ k ];
        m_permutations[ k ] = j;
    }
    
    fill_map( m_map, m_min, m_max );
}

WorleyNoise::~WorleyNoise() {
    
}

void WorleyNoise::fill_map( float map[][ GRID_SIZE ], float &min, float &max ) {
    float gain = 0.6f;
    float lacunarity = 2.0f;
    
    m_min = 10000.0f;
    m_max = 0.0f;
    
    int octaves = 4;
    
    float total;
    float frequency;
    float amplitude;
    float offset;
    
    for ( int x = 0; x < GRID_SIZE; x++ ) {
        for ( int y = 0; y < GRID_SIZE; y++ ) {
            total = 0.0f;
            frequency = 1.0f / ( float ) GRID_SIZE;
            amplitude = 1.0f;
            
            for ( int i = 0; i < octaves; i++ ) {
                offset = ( float ) i * 7.0f;
                total += smoothed_noise( ( float ) x * frequency + offset, ( float ) y * frequency + offset ) * amplitude;
                
                frequency *= lacunarity;
                amplitude *= gain;
            }
            
            map[ x ][ y ] = total;
            
            if ( total < min ) {
                min = total;
            }
            
            if ( total > max ) {
                max = total;
            }
        }
    }
}

float WorleyNoise::random( int x, int y, int z ) {
    int r1 = m_permutations[ ( x + m_permutations[ ( y + m_permutations[ z & 255 ] ) & 255 ] ) & 255 ];
    return ( ( float ) r1 / 256.0f );
}

int WorleyNoise::random_int() {
    return rand() & 255;
}

float WorleyNoise::smoothed_noise( float x, float y ) {
    int int_x = ( int ) x;
    int int_y = ( int ) y;
    
    float points[ 3 ][ 3 ][ 2 ];
    float temp_dis;
    float dist1;
    float dist2;
    
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            float temp_x = int_x + i - 1;
            float temp_y = int_y + j - 1;
            points[ i ][ j ][ 0 ] = temp_x + random( temp_x, temp_y, 1 );
            points[ i ][ j ][ 1 ] = temp_y + random( temp_x, temp_y, 2 );
        }
    }
    
    dist1 = dist2 = FLT_MAX;
    
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            temp_dis = euclidean_squared( x, y, points[ i ][ j ][ 0 ], points[ i ][ j ][ 1 ] );
            // temp_dis = manhattan( x, y, points[ i ][ j ][ 0 ], points[ i ][ j ][ 1 ] );
            // temp_dis = chebychev( x, y, points[ i ][ j ][ 0 ], points[ i ][ j ][ 1 ] );
            // temp_dis = quadratic( x, y, points[ i ][ j ][ 0 ], points[ i ][ j ][ 1 ] );
            
            if ( temp_dis < dist1 ) {
                if ( dist1 < dist2 ) {
                    dist2 = dist1;
                }
                dist1 = temp_dis;
            } else if ( temp_dis < dist2 ) {
                dist2 = temp_dis;
            }
        }
    }
    
    return ( 1.0f - dist1 );
}

float WorleyNoise::euclidean_squared( float x1, float y1, float x2, float y2 ) {
    return ( ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 ) );
}

float WorleyNoise::manhattan( float x1, float y1, float x2, float y2 ) {
    return ( fabs( x1 - x2 ) + fabs( y1 - y2 ) );
}

float WorleyNoise::chebychev( float x1, float y1, float x2, float y2 ) {
    return MAX( fabs( x1 - x2 ), fabs( y1 - y2 ) );
}

float WorleyNoise::quadratic( float x1, float y1, float x2, float y2 ) {
    return ( ( x1 - x2 ) * ( x1 - x2 ) + ( x1 - x2 ) * ( y1 - y2 ) + ( y1 - y2 ) * ( y1 - y2 ) );
}

void WorleyNoise::to_png( const std::string &file ) {
    pngwriter png( GRID_SIZE, GRID_SIZE, 0, file.c_str() );
    
    for ( int i = 0; i < GRID_SIZE; i++ ) {
        for ( int j = 0; j < GRID_SIZE; j++ ) {
            float value = m_map[ j ][ i ] - m_min;
        
            png.plot( j, i, ( double ) value, ( double ) value, ( double ) value );
        }
    }
    
    png.close();
}












