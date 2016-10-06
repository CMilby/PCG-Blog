//
//  noiseLayering.cpp
//  PCG-Blog
//
//  Created by Craig Milby on 9/17/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#include "noiseLayering.h"

#include <pngwriter.h>

NoiseLayering::NoiseLayering() {
    m_height = new SimplexNoise();
    m_temperature = new SimplexNoise();
    m_wetness = new SimplexNoise();
}

NoiseLayering::NoiseLayering( unsigned int pHeightSeed, unsigned int pTemperatureSeed, unsigned int pWetnessSeed ) {
    m_height = new SimplexNoise( pHeightSeed );
    m_temperature = new SimplexNoise( pTemperatureSeed );
    m_wetness = new SimplexNoise( pWetnessSeed );
}

NoiseLayering::~NoiseLayering() {
    if ( m_height ) {
        delete m_height;
    }
    
    if ( m_temperature ) {
        delete m_temperature;
    }
    
    if ( m_wetness ) {
        delete m_wetness;
    }
}

void NoiseLayering::to_png( const std::string &file, int width, int height ) {
    pngwriter png( width, height, 0, file.c_str() );
    
    static float const kOctaves = 4;
    static float const kPersistence = 0.4f;
    static float const kScale = 0.005f;
    
    float myHeight, myTemp, myWet;
    for ( int i = 0; i < width; i++ ) {
        for ( int j = 0; j < height; j++ ) {
            myHeight = m_height->OctaveNoise2D( kOctaves, kPersistence, kScale, i, j );
            myTemp =   m_temperature->OctaveNoise2D( kOctaves, kPersistence, kScale, i, j );
            myWet =    m_wetness->OctaveNoise2D( kOctaves, kPersistence, kScale, i, j );
            
            myHeight = Utility::scale( myHeight, 0.0f, 1.0f, -1.0f, 1.0f );
            myTemp =   Utility::scale( myTemp, 0.0f, 1.0f, -1.0f, 1.0f );
            myWet =    Utility::scale( myWet, 0.0f, 1.0f, -1.0f, 1.0f );
            
            Vector<float, 3> myColor = GeneratePoint( myHeight, myTemp, myWet );
            png.plot( i, j, ( double ) myColor[ 0 ], ( double ) myColor[ 1 ], ( double ) myColor[ 2 ] );
        }
    }
    
    png.close();
}

Vector<float, 3> NoiseLayering::GeneratePoint( const float p_height, const float p_temp, const float p_wet ) {
    Vector<float, 3> myColor;
    
    if ( p_height < 0.3f ) {
        SetColor( myColor, 0, 0, 255 );     // Ocean
    } else if ( p_height < 0.32 ) {
        SetColor( myColor, 177, 166, 29 );  // Sand
    } else if ( p_height > 0.7f ) {
        SetColor( myColor, 132, 132, 132 ); // Rock
    }
    
    if ( p_wet >= 0.75 ) {
        if ( p_temp >= 0.75f ) {
            // Rainforest
            SetColor( myColor, 8, 250, 54 );
        } else {
            // Swamp
            SetColor( myColor, 7, 249, 162 );
        }
    } else if ( p_wet >= 0.5f ) {
        if ( p_temp >= 0.75f ) {
            // Seasonal forest
            SetColor( myColor, 155, 224, 35 );
        } else if ( p_temp >= 0.5f ) {
            // Forest
            SetColor( myColor, 100, 148, 12 );
        } else {
            // Taiga
            SetColor( myColor, 5, 102, 33 );
        }
    } else if ( p_wet >= 0.25f ) {
        if ( p_temp >= 0.75f ) {
            // Savanah
            SetColor( myColor, 255, 255, 94 );
        } else if ( p_temp >= 0.5f ) {
            // Woods
            SetColor( myColor, 46, 177, 83 );
        } else {
            // Taiga
            SetColor( myColor, 5, 102, 33 );
        }
    } else {
        if ( p_temp >= 0.625 ) {
            // Desert
            SetColor( myColor, 177, 166, 29 );
        } else if ( p_temp >= 0.25 ) {
            // Grass Desert
            SetColor( myColor, 247, 193, 0 );
        } else {
            // Tundra
            SetColor( myColor, 81, 237, 250 );
        }
    }
    
    return myColor;
}

void NoiseLayering::SetColor( Vector<float, 3> &p_color, int p_red, int p_green, int p_blue ) {
    p_color[ 0 ] = ( float ) p_red / 255.0f;
    p_color[ 1 ] = ( float ) p_green / 255.0f;
    p_color[ 2 ] = ( float ) p_blue / 255.0f;
}







