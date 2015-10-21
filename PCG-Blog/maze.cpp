//
//  maze.cpp
//  PCG-Blog
//
//  Created by Craig Milby on 10/13/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include "maze.h"

#include <stack>

Maze::Maze( unsigned int width, unsigned int height ) {
    m_width = width;
    m_height = height;
    
    m_map = Utility::blank_map( '#', width, height );
    generate_maze();
    add_entrance_exit();
}

void Maze::generate_maze() {
    std::vector<Cell> cells;
    for ( unsigned int i = 1; i < m_height; i += 2 ) {
        for ( unsigned int j = 1; j < m_width; j += 2 ) {
            cells.emplace_back( Cell( i, j, false ) );
        }
    }
    
    Cell currentCell = cells[ Utility::random_in_range( 0, ( int ) ( cells.size() - 1 ) ) ];
    currentCell.m_visited = true;
    
    std::stack<Cell> cellStack;
    
    while ( unvisited_cells( cells ) ) {
        std::vector<Cell> cellNeighbors = unvisited_neighbors( neighbors( currentCell, cells ) );
        
        if ( cellNeighbors.size() > 0 ) {
            Cell nextCell = cellNeighbors[ Utility::random_in_range( 0, ( int ) cellNeighbors.size() - 1 ) ];
            Point point = get_adjacent_point( currentCell, nextCell );
            
            currentCell = nextCell;
            cellStack.push( currentCell );
            
            m_map[ currentCell.m_x + m_width * currentCell.m_y ] = ' ';
            m_map[ point.m_x + m_width * point.m_y ] = ' ';
            
            cells[ get_cell( currentCell, cells ) ].m_visited = true;
        } else {
            cellStack.pop();
            currentCell = cellStack.top();
        }
    }
}

void Maze::add_entrance_exit() {
    // Entrance: top left
    m_map[ m_width ] = ' ';
    
    // Exit bottom right
    m_map[ m_width * m_height - m_width - 1 ] = ' ';
}

std::vector<Cell> Maze::neighbors( const Cell &currentCell, const std::vector<Cell> &map ) const {
    std::vector<Cell> neighbors;
    
    for ( unsigned int i = 0; i < map.size(); i++ ) {
        if ( currentCell.is_neighbor( map[ i ], 2 ) ) {
            neighbors.emplace_back( map[ i ] );
        }
    }
    
    return neighbors;
}

std::vector<Cell> Maze::unvisited_neighbors( const std::vector<Cell> &neighbors ) const {
    std::vector<Cell> unvisitedNeighbors;
    for ( unsigned int i = 0; i < neighbors.size(); i++ ) {
        if ( !neighbors[ i ].m_visited ) {
            unvisitedNeighbors.emplace_back( neighbors[ i ] );
        }
    }
    return unvisitedNeighbors;
}

bool Maze::unvisited_cells( const std::vector<Cell> &cellList ) {
    for ( unsigned int i = 0; i < cellList.size(); i++ ) {
        if ( !cellList[ i ].m_visited )
            return true;
    }
    return false;
}

int Maze::get_cell( const Cell &current, const std::vector<Cell> &cells ) const {
    for ( unsigned int i = 0; i < cells.size(); i++ ) {
        if ( cells[ i ] == current )
            return i;
    }
    return -1;
}

Point Maze::get_adjacent_point( const Cell &currentCell, const Cell &nextCell ) const {
    int x = currentCell.m_x;
    int y = currentCell.m_y;
    
    if ( currentCell.m_x < nextCell.m_x ) {
        x = currentCell.m_x + 1;
    } else if ( currentCell.m_x > nextCell.m_x ) {
        x = currentCell.m_x - 1;
    }
    
    if ( currentCell.m_y < nextCell.m_y ) {
        y = currentCell.m_y + 1;
    } else if ( currentCell.m_y > nextCell.m_y ) {
        y = currentCell.m_y - 1;
    }
    
    return Point( x, y );
}









