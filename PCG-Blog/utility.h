//
//  utility.hpp
//  PCG-Blog
//
//  Created by Craig Milby on 10/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <vector>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))

namespace Utility {
    
    void print_map( const std::vector<char> &map, unsigned int width, unsigned int height );
    
    std::vector<char> blank_map( char delim, unsigned int width, unsigned int height );
    
    int random_in_range( int min, int max );
}

#endif
