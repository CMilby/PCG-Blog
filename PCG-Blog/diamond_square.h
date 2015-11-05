//
//  diamond_square.h
//  PCG-Blog
//
//  Created by Craig Milby on 10/13/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef DIAMOND_SQUARE_H
#define DIAMOND_SQUARE_H

#include <string>
#include <vector>

#include "utility.h"

class DiamondSquare {
    
private:
    std::vector<float> m_map;
    
    unsigned int m_width;
    unsigned int m_height;
    
public:
    DiamondSquare( unsigned int width, unsigned int height, int featureSize );
    
    void diamond_square( int stepSize, float scale );

    void diamond_step( int x, int y, int size, float value );
    void square_step( int x, int y, int size, float value );
    
    float sample( int x, int y );
    void setSample( int x, int y, float value );
    
    void to_png( const std::string &file );
};

#endif /* diamond_square_h */
