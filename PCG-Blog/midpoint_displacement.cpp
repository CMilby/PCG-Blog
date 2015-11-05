//
//  midpoint_displacement.cpp
//  PCG-Blog
//
//  Created by Craig Milby on 11/4/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "midpoint_displacement.h"

#include <pngwriter.h>

MidpointDisplacement::MidpointDisplacement( int roughness, int npoints ) {
    m_data.push_back( Point( 0, 512 ) );
    m_data.push_back( Point( 1024, 512 ) );
    npoints -= 2;
    generate( m_data, roughness, npoints );
}

void MidpointDisplacement::generate( std::vector<Point> &points, int roughness, int npoints ) {
    if ( npoints < 0 )
        return;
    for ( unsigned int i = 1; i < points.size(); i += 2 ) {
        Point pMid = middle( points.at( i ), points.at( i - 1 ) );
        Point pDis = displace( pMid, roughness );
        points.insert( points.begin() + i, pDis );
        npoints--;
    }
    
    generate( points, roughness / 2, npoints );
}

Point MidpointDisplacement::middle( const Point &p1, const Point &p2 ) const {
    return Point( ( p1.m_x + p2.m_x ) / 2, ( p1.m_y + p2.m_y ) / 2 );
}

Point MidpointDisplacement::displace( const Point &p, int roughness ) const {
    return Point( p.m_x, Utility::random_in_range( p.m_y - roughness, p.m_y + roughness ) );
}

void MidpointDisplacement::to_png( const std::string &file ) const {
    pngwriter png( 1024, 1024, 0, file.c_str() );
    
    for ( unsigned int i = 0; i < m_data.size(); i++ ) {
        png.plot( m_data[ i ].m_x, m_data[ i ].m_y, 1.0, 0.0, 0.0 );
    }
    
    png.close();
}