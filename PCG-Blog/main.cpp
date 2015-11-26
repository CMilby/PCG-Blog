//
//  main.cpp
//  PCG-Blog
//
//  Created by Craig Milby on 10/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include <cstdio>
#include <iostream>

#include <pngwriter.h>

#include "diamond_square.h"
#include "maze.h"
#include "midpoint_displacement.h"
#include "perlin_noise.h"
#include "random_cave.h"
#include "random_dungeon.h"
#include "utility.h"
#include "worley_noise.h"

int main() {
    unsigned int seed = ( unsigned int ) time( 0 );
    srand( seed );
    
    unsigned int width = 200;
    unsigned int height = 200;
    
    std::string file = "/Users/Craig/Downloads/output.png";
    
    // RandomDungeon dungeon( width, height, 9 );
    // Utility::print_map( dungeon.get_map(), width, height );
    
    // RandomCave cave( width, height, 45 );
    // Utility::print_map( cave.get_map(), width, height );
    
    // Maze maze( width, height );
    // Utility::print_map( maze.get_map(), width, height );
    
    // MidpointDisplacement midpoint( 512, 4096 );
    // midpoint.to_png( file );
    
    // DiamondSquare diamond( width, height, 32 );
    // diamond.to_png( file );
    
    // PerlinNoise noise( seed );
    // noise.to_png( file, width, height );
    
    WorleyNoise worley;
    worley.to_png( file );
    
    return 0;
}












