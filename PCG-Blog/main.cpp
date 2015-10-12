//
//  main.cpp
//  PCG-Blog
//
//  Created by Craig Milby on 10/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#include <cstdio>
#include <iostream>

#include "random_cave.h"
#include "random_dungeon.h"
#include "utility.h"

int main() {
    unsigned int seed = ( unsigned int ) time( 0 );
    srand( seed );
    
    unsigned int width = 45;
    unsigned int height = 45;
    
    // RandomDungeon dungeon( width, height, 5 );
    // Utility::print_map( dungeon.get_map(), width, height );
    
    RandomCave cave( width, height, 50 );
    Utility::print_map( cave.get_map(), width, height );
    
    system( "pause" );
    return 0;
}