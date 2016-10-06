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

/*
#include "diamond_square.h"
#include "maze.h"
#include "midpoint_displacement.h"
#include "perlin_noise.h"
#include "simplexNoise.h"
#include "random_cave.h"
#include "random_dungeon.h"
#include "utility.h"
#include "worley_noise.h"*/
#include "noiseLayering.h"

int main() {
    unsigned int seed = ( unsigned int ) time( 0 );
    srand( seed );
    
    unsigned int width  = 1024;
    unsigned int height = 1024;
    
    std::string file = "/Users/Craig/Downloads/output.png";
    NoiseLayering *nl = new NoiseLayering();
    nl->to_png( file, width, height );
    
    return 0;
}












