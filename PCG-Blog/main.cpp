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
#include "simplex_noise.h"
#include "random_cave.h"
#include "random_dungeon.h"
#include "utility.h"
#include "worley_noise.h"

int main() {
    unsigned int seed = ( unsigned int ) time( 0 );
    srand( seed );
    
    unsigned int width  = 1024;
    unsigned int height = 1024;
    
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
    
    // WorleyNoise worley;
    // worley.to_png( file );
    
    static const float HEIGHT_MAX = 1.0f;
    static const float HEIGHT_MIN = 0.0f;
    static const float NOISE_PERSISTENCE = 0.3f;
    static const float NOISE_OCTAVES = 8.0f;
    static const float NOISE_SCALE = 0.007f;
    
    pngwriter png( width, height, 0, file.c_str() );
    
    float x, y, z;

    for ( unsigned int i = 0; i < height; i++ ) {
        for ( unsigned int j = 0; j < width; j++ ) {
            x = i;
            y = j;
            z = -1;
            
            float noise = SimplexNoise::ScaledOctaveNoise3D( NOISE_OCTAVES, NOISE_PERSISTENCE, NOISE_SCALE, HEIGHT_MIN, HEIGHT_MAX, i, j, 1.0 );
            noise = Utility::scale( noise, 0.0f, 1.0f, HEIGHT_MIN, HEIGHT_MAX );
            
            png.plot( i + 1, j + 1, noise, noise, noise );
        }
    }

    png.close();
    
    return 0;
}












