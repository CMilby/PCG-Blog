//
//  random_cave.cpp
//  PCG-Blog
//
//  Created by Craig Milby on 10/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "random_cave.h"

#include "utility.h"

RandomCave::RandomCave( unsigned int width, unsigned int height, unsigned int percent ) {
    m_width = width;
    m_height = height;
    
    m_map = random_cave_map( percent );
    make_caves( m_map );
}

bool RandomCave::is_out_of_bounds( int x, int y ) {
    if ( x < 0 || y < 0 )
        return true;
    if ( x > m_width - 1 || y > m_height - 1 )
        return true;
    return false;
}

bool RandomCave::is_wall( int x, int y, const std::vector<char> &map ) {
    if ( is_out_of_bounds( x, y ) )
        return true;
    if ( map[ x * m_width + y ] == '#' )
        return true;
    return false;
}

int RandomCave::get_adjacent_walls( int x, int y, int xScope, int yScope, const std::vector<char> &map ) {
    int startX = x - xScope;
    int startY = y - yScope;
    int endX = x + xScope;
    int endY = y + yScope;
    
    int iX = startX;
    int iY = startY;
    
    int wallCounter = 0;
    
    for ( iX = startX; iX <= endX; iX++ ) {
        for ( iY = startY; iY <= endY; iY++ ) {
            if ( !( iX == x && iY == y ) ) {
                if ( is_wall( iX, iY, map ) ) {
                    wallCounter++;
                }
            }
        }
    }
    return wallCounter;
}

char RandomCave::place_wall( int x, int y, std::vector<char> &map ) {
    int num_walls = get_adjacent_walls( x, y, 1, 1, map );
    
    if ( map[ x * m_width + y ] == '#' ) {
        if ( num_walls >= 4 )
            return '#';
        if ( num_walls < 2 )
            return ' ';
    } else {
        if ( num_walls >= 5 )
            return '#';
    }
    return ' ';
}

char RandomCave::random_percent( int percent ) {
    return ( Utility::random_in_range( 0, 100 ) < percent ) ? '#' : ' ';
}

void RandomCave::make_caves( std::vector<char> &map ) {
    for ( int row = 0, col = 0; row < m_width; row++ ) {
        for ( col = 0; col < m_height; col++ ) {
            map[ row * m_width + col ] = place_wall( row, col, map );
        }
    }
}

std::vector<char> RandomCave::random_cave_map( unsigned int percent ) {
    std::vector<char> map = Utility::blank_map( ' ', m_width, m_height );
    
    int map_middle = 0;
    for ( int row = 0, col = 0; row < m_height; row++ ) {
        for ( col = 0; col < m_width; col++ ) {
            if ( col == 0 || row == 0 || col == m_width - 1 || row == m_height - 1 ) {
                map[ row * m_width + col ] = '#';
            } else {
                map_middle = ( m_height / 2 );
                
                if ( row == map_middle )
                    map[ row * m_width + col ] = 0;
                else
                    map[ row * m_width + col ] = random_percent( percent );
            }
        }
    }
    
    return map;
}



