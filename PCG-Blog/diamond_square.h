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
    std::vector<int> m_map;
    unsigned int m_size;
    
    int point_to_single( int x, int y ) const;
    int point_to_single( const Point &point ) const;
    
    void populate_map();
    
    void diamond_square( const Point &p1, const Point &p2, const Point &p3, const Point &p4, float magnitude );
    int square_step( unsigned int i, unsigned int j, int halfSpace, float magnitude );
    int diamond_step( unsigned int i, unsigned int j, int halfSpace, float magnitude );
    
    bool is_valid( const Point &point );
    bool is_valid( int x, int y );
public:
    DiamondSquare( unsigned int size );
  
    std::vector<std::string> get_map() const;
    void to_png( const std::string &file );
};

#endif /* diamond_square_h */
