//
//  midpoint_displacement.h
//  PCG-Blog
//
//  Created by Craig Milby on 11/4/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef MIDPOINT_DISPLACEMENT_H
#define MIDPOINT_DISPLACEMENT_H

#include <string>
#include <vector>

#include "utility.h"

class MidpointDisplacement {
    
private:
    std::vector<Point> m_data;
    
public:
    MidpointDisplacement( int roughness, int npoints );
    
    void generate( std::vector<Point> &points, int roughness, int npoints );
    
    Point middle( const Point &p1, const Point &p2 ) const;
    Point displace( const Point &p, int roughness ) const;
    
    void to_png( const std::string &file ) const;
};

#endif /* midpoint_displacement_h */
