//
//  perlin_noise.cpp
//  PCG-Blog
//
//  Created by Craig Milby on 11/4/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "perlin_noise.h"

#include <algorithm>
#include <cmath>
#include <random>

#include <pngwriter.h>

#include "utility.h"

PerlinNoise::PerlinNoise( int seed ) {
    m_seed = seed;
    
    m_gradient.resize( 256 );
    std::iota( m_gradient.begin(), m_gradient.end(), 0 );
    
    std::default_random_engine engine( m_seed );
    std::shuffle( m_gradient.begin(), m_gradient.end(), engine );
    m_gradient.insert( m_gradient.end(), m_gradient.begin(), m_gradient.end() );
}

PerlinNoise::~PerlinNoise() {
    
}

float PerlinNoise::lerp( float t, float a, float b ) {
    return ( b - a ) * t + a;
}

float PerlinNoise::grad( int hash, float x, float y, float z ) {
    int h = hash & 15;
    double u = h < 8 ? x : y;
    double v = h < 4 ? y : ( h == 12 || h == 14 ) ? x : z;
    return ( float )  ( ( ( h & 1 ) == 0 ? u : -u ) + ( ( h & 2 ) == 0 ? v : -v ) );
}

float PerlinNoise::fade( double t ) {
    return t * t * t * ( t * ( t * 6 - 15 ) + 10 );
}

float PerlinNoise::perlin( float x, float y, float z ) {
    int x0 = ( int ) floor( x ) & 255;
    int y0 = ( int ) floor( y ) & 255;
    int z0 = ( int ) floor( z ) & 255;
    
    x -= floor( x );
    y -= floor( y );
    z -= floor( z );
    
    float u = fade( x );
    float v = fade( y );
    float w = fade( z );
    
    int a = m_gradient[ x0 ] + y0;
    int aa = m_gradient[ a ] + z0;
    int ab = m_gradient[ a + 1 ] + z0;
    int b = m_gradient[ x0 + 1 ] + y0;
    int ba = m_gradient[ b ] + z0;
    int bb = m_gradient[ b + 1 ] + z0;
    
    float g0 = grad( m_gradient[ bb + 1 ], x - 1, y - 1, z - 1 );
    float g1 = grad( m_gradient[ ab + 1 ], x, y - 1, z - 1 );
    float lerp0 = lerp( u, g1, g0 );
    
    g0 = grad( m_gradient[ ba + 1 ], x - 1, y, z - 1 );
    g1 = grad( m_gradient[ aa + 1], x, y, z - 1 );
    float lerp1 = lerp( u, g1, g0 );
    
    float lerp2 = lerp( v, lerp1, lerp0 );
    
    g0 = grad( m_gradient[ bb ], x - 1, y - 1, z );
    g1 = grad( m_gradient[ ab ], x, y - 1, z );
    lerp0 = lerp( u, g1, g0 );
    
    g0 = grad( m_gradient[ ba ], x - 1, y, z );
    g1 = grad( m_gradient[ aa ], x, y, z );
    lerp1 = lerp( u, g1, g0 );
    
    float lerp3 = lerp( v, lerp1, lerp0 );
    
    float res = lerp( w, lerp3, lerp2 );
    return ( res + 1.0 ) / 2.0;
}

void PerlinNoise::to_png( const std::string &file, int width, int height ) {
    pngwriter png( width, height, 0, file.c_str() );
    
    for ( unsigned int i = 0; i < height; i++ ) {
        for ( unsigned int j = 0; j < width; j++ ) {
            float x = ( float ) j / ( float ) width;
            float y = ( float ) i / ( float ) height;
            
            float n = 1.0f  * perlin( x * 1, y * 1, 0 ) +
                      0.5f  * perlin( x * 2, y * 2, 0 ) +
                      0.25f * perlin( x * 4, y * 4, 0 );
            
            // n = 20 * perlin(x, y, 0.8);
            // n = n - floor(n);
            
            png.plot( i, j, n, n, n );
        }
    }
    png.close();
}








