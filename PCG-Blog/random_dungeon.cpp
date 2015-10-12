//
//  random_dungeon.cpp
//  PCG-Blog
//
//  Created by Craig Milby on 10/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "random_dungeon.h"
#include "utility.h"

RandomDungeon::RandomDungeon( unsigned int width, unsigned int height, unsigned int num_rooms ) {
    m_width = width;
    m_height = height;
    
    m_map = Utility::blank_map( '#', width, height );
    generate_dungeon_room_map( m_map, num_rooms );
}

void RandomDungeon::horizontal_corridor( std::vector<char> &map, unsigned int x1, unsigned int x2, unsigned int y ) {
    for ( int i = MIN( x1, x2 ); i < MAX( x1, x2 ) + 1; i++ ) {
        map[ y * m_width + i ] = ' ';
    }
}

void RandomDungeon::vertical_corridor( std::vector<char> &map, unsigned int y1, unsigned int y2, unsigned int x ) {
    for ( int i = MIN( y1, y2 ); i < MAX( y1, y2 ) + 1; i++ ) {
        map[ i * m_width + x ] = ' ';
    }
}

void RandomDungeon::generate_dungeon_room_map( std::vector<char> &map, unsigned int num_rooms ) {
    std::vector<Room> rooms;
    
    for ( int i = 0; i < num_rooms; i++ ) {
        Room room;
        
        bool intersects = false;
        
        do {
            intersects = false;
            
            int room_width = Utility::random_in_range( 5, 10 );
            int room_height = Utility::random_in_range( 5, 10 );
            
            room.m_x1 = Utility::random_in_range( 1, m_width - room_width - 1 );
            room.m_y1 = Utility::random_in_range( 1, m_height - room_height - 1 );
            room.m_x2 = room.m_x1 + room_width;
            room.m_y2 = room.m_y1 + room_height;
            
            for ( unsigned int i = 0; i < rooms.size(); i++ ) {
                if ( room.intersects( rooms[ i ] ) )
                    intersects = true;
            }
        } while ( intersects );
        
        for ( int k = room.m_x1; k < room.m_x2; k++ ) {
            for ( int j = room.m_y1; j < room.m_y2; j++ ) {
                map[ j * m_width + k ] = ' ';
            }
        }
        
        rooms.push_back( room );
        
        if ( i > 0 ) {
            Room prev = rooms[ i - 1 ];
            horizontal_corridor( map, prev.center_x(), room.center_x(), prev.center_y() );
            vertical_corridor(  map, prev.center_y(), room.center_y(), room.center_x() );
        }
    }
}
