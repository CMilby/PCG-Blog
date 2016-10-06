//
//  noiseLayering.h
//  PCG-Blog
//
//  Created by Craig Milby on 9/17/16.
//  Copyright © 2016 Craig Milby. All rights reserved.
//

#ifndef __NOISE_LAYERING_H__
#define __NOISE_LAYERING_H__

#include <string>

#include "simplexNoise.h"
#include "utility.h"

class NoiseLayering {
    
private:
    SimplexNoise *m_height;
    SimplexNoise *m_temperature;
    SimplexNoise *m_wetness;
    
public:
    NoiseLayering();
    NoiseLayering( unsigned int pHeightSeed, unsigned int pTemperatureSeed, unsigned int pWetnessSeed );
    virtual ~NoiseLayering();
    
    void to_png( const std::string &file, int width, int height );
    
private:
    Vector<float, 3> GeneratePoint( const float p_height, const float p_temp, const float p_wet );
    void SetColor( Vector<float, 3> &p_color, int p_red, int p_green, int p_blue );
};

#endif /* noiseLayering_h */
