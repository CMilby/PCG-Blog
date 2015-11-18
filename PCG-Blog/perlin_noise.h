//
//  perlin_noise.h
//  PCG-Blog
//
//  Created by Craig Milby on 11/4/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include <string>
#include <vector>

class PerlinNoise {
    
private:
    std::vector<int> m_gradient;
    int m_seed;
    
public:
    PerlinNoise( int seed );
    virtual ~PerlinNoise();
    
    void to_png( const std::string &file, int width, int height );
    
    float lerp( float t, float a, float b );
    float grad( int hash, float x, float y, float z );
    float fade( double t );
    float perlin( float x, float y, float z );
};

#endif /* perlin_noise_h */
