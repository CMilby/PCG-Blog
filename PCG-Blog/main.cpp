//
//  main.cpp
//  PCG-Blog
//
//  Created by Craig Milby on 10/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include <cstdio>
#include <iostream>

#include "diamond_square.h"
#include "maze.h"
#include "random_cave.h"
#include "random_dungeon.h"
#include "utility.h"

int main() {
    unsigned int seed = ( unsigned int ) time( 0 );
    srand( 1234 );
    
    unsigned int width = 45;
    unsigned int height = 45;
    
    // RandomDungeon dungeon( width, height, 9 );
    // Utility::print_map( dungeon.get_map(), width, height );
    
    RandomCave cave( width, height, 45 );
    Utility::print_map( cave.get_map(), width, height );
    
    // Maze maze( width, height );
    // Utility::print_map( maze.get_map(), width, height );

    // unsigned int size = 1025; // 2^n + 1
    // DiamondSquare diamondSquare( size );
    // Utility::print_map( diamondSquare.get_map(), size, size );
    // diamondSquare.to_png( "/Users/Craig/Downloads/output.png" );
    
    return 0;
}