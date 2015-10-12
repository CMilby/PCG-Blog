//
//  random_dungeon.h
//  PCG-Blog
//
//  Created by Craig Milby on 10/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef RANDOM_DUNGEON_H
#define RANDOM_DUNGEON_H

#include <vector>

class Room {
    
public:
    int m_x1;
    int m_y1;
    int m_x2;
    int m_y2;
    
    Room() {
        Room( 0, 0, 0, 0 );
    }
    
    Room( int x1, int y1, int x2, int y2 ) {
        m_x1 = x1;
        m_y1 = y1;
        m_x2 = x2;
        m_y2 = y2;
    }
    
    inline bool intersects( Room &room ) {
        return !( m_x2 < room.m_x1 || m_y2 < room.m_y1 || m_x1 > room.m_x2 || m_y1 > room.m_y2 );
    }
    
    inline int center_x() const {
        return ( m_x2 + m_x1 ) / 2;
    }
    
    inline int center_y() const {
        return ( m_y2 + m_y1 ) / 2;
    }
};

class RandomDungeon {
    
private:
    unsigned int m_width;
    unsigned int m_height;
    
    std::vector<char> m_map;
    
    void horizontal_corridor( std::vector<char> &map, unsigned int x1, unsigned int x2, unsigned int y );
    void vertical_corridor( std::vector<char> &map, unsigned int y1, unsigned int y2, unsigned int x );
    
    void generate_dungeon_room_map( std::vector<char> &map, unsigned int num_rooms );
    
public:    
    RandomDungeon( unsigned int width, unsigned int height, unsigned int num_rooms );
    
    inline std::vector<char> get_map() const { return m_map; }
};

#endif /* random_dungeon_h */










