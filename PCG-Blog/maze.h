//
//  maze.h
//  PCG-Blog
//
//  Created by Craig Milby on 10/13/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef MAZE_H
#define MAZE_H

#include <vector>

#include "utility.h"

struct Cell {

    bool m_visited;
    int m_x;
    int m_y;
    
    Cell( int x, int y, bool visited ) :
            m_x( x ), m_y( y ),
            m_visited( visited ) {}
    
    inline bool is_neighbor( const Cell &cell, int reach ) const {
        return ( ( m_x - reach == cell.m_x && m_y == cell.m_y ) ||
                 ( m_x == cell.m_x && m_y - reach == cell.m_y ) ||
                 ( m_x + reach == cell.m_x && m_y == cell.m_y ) ||
                 ( m_x == cell.m_x && m_y + reach == cell.m_y ) );
    }
    
    inline bool operator==( const Cell &other ) const {
        return ( m_x == other.m_x && m_y == other.m_y );
    }
    
    inline bool operator!=( const Cell &other ) const {
        return !operator==( other );
    }
};

class Maze {
    
private:
    std::vector<char> m_map;

    unsigned int m_width;
    unsigned int m_height;
    
    void generate_maze();
    bool unvisited_cells( const std::vector<Cell> &cellList );
    void add_entrance_exit();
    
    std::vector<Cell> neighbors( const Cell &currentCell, const std::vector<Cell> &map ) const;
    std::vector<Cell> unvisited_neighbors( const std::vector<Cell> &neighbors ) const;
    
    int get_cell( const Cell &current, const std::vector<Cell> &cells ) const;
    Point get_adjacent_point( const Cell &currentCell, const Cell &nextCell ) const;
    
public:
    Maze( unsigned int width, unsigned int height );
    
    inline std::vector<char> get_map() const { return m_map; }
};

#endif /* maze_h */
