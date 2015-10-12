//
//  random_cave.h
//  PCG-Blog
//
//  Created by Craig Milby on 10/12/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef RANDOM_CAVE_H
#define RANDOM_CAVE_H

#include <vector>

class RandomCave {
    
private:
    unsigned int m_width;
    unsigned int m_height;
    
    std::vector<char> m_map;
    
    bool is_out_of_bounds( int x, int y );
    bool is_wall( int x, int y, const std::vector<char> &map );
    
    int get_adjacent_walls( int x, int y, int xScope, int yScope, const std::vector<char> &map );
    char place_wall( int x, int y, std::vector<char> &map );
    char random_percent( int percent );
    
    std::vector<char> random_cave_map( unsigned int percent );
    void make_caves( std::vector<char> &map );
public:
    RandomCave( unsigned int width, unsigned int height, unsigned int percent );
    
    inline std::vector<char> get_map() const { return m_map; }
};

#endif /* random_cave_h */
