//
//  worley_noise.h
//  PCG-Blog
//
//  Created by Craig Milby on 11/20/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#ifndef WORLEY_NOISE_H
#define WORLEY_NOISE_H

/*#include <algorithm>
#include <math.h>

#include "utility.h"

class WorleyNoise 
{
private:
    float DistanceArray[3];
    
    float CombinerFunction1(float ar[]);
    float CombinerFunction2(float ar[]);
    float CombinerFunction3(float ar[]);
    
    float EuclidianDistanceFunc(Vector3 p1, Vector3 p2);
    float ManhattanDistanceFunc(Vector3 p1, Vector3 p2);
    float ChebyshevDistanceFunc(Vector3 p1, Vector3 p2);
    
    long probLookup(long value);
    void insert(float  arr[], float value);
    long lcgRandom(long lastValue);
    long hash(long i, long j, long k);
    float noise(Vector3 input);
public:
    int DistanceFunction = 0;
    int CombineDistanceFunction = 0;
    int Seed = 3221;
    
    int OFFSET_BASIS = 2166136261;
    int FNV_PRIME = 16777619;
    
    float Get1D(float x);
    float Get2D(float x, float y);
    
    static void to_png( const std::string &file, unsigned int width, unsigned int height, WorleyNoise worley );
    
    WorleyNoise();
    ~WorleyNoise();
};*/

#include <functional>
#include <string>
#include <vector>

#include "utility.h"

#define GRID_SIZE 512

class WorleyNoise {
    
private:
    int m_permutations[ 256 ];
    float m_map[ GRID_SIZE ][ GRID_SIZE ];
    float m_min;
    float m_max;
    
    int random_int();
    float random( int x, int y, int z );
    
    void fill_map( float map[][ GRID_SIZE ], float &min, float &max );
    
    float smoothed_noise( float x, float y );
    float euclidean_squared( float x1, float y1, float x2, float y2 );
    float manhattan( float x1, float y1, float x2, float y2 );
    float chebychev( float x1, float y1, float x2, float y2 );
    float quadratic( float x1, float y1, float x2, float y2 );
    
public:
    WorleyNoise();
    virtual ~WorleyNoise();
    
    void to_png( const std::string &file );
    
/*private:
    int m_seed;
    
    float combine_function_1( float arr[] );
    float combine_function_2( float arr[] );
    float combine_function_3( float arr[] );
    
    float euclidian_distance( Vector3 p1, Vector3 p2 );
    float manhattan_distance( Vector3 p1, Vector3 p2 );
    float chebyshev_distance( Vector3 p1, Vector3 p2 );
    
    unsigned int lookup( unsigned int value );
    void insert( float arr[] , float value );
    unsigned int lcg_random( unsigned int last );
    unsigned int hash( unsigned int i, unsigned int j, unsigned int k );
    
    float noise( Vector3 input );
    
public:
    const int OFFSET_BASIS = 2166136261;
    const int FNV_PRIME = 16777619;
    
    WorleyNoise( int seed );
    virtual ~WorleyNoise();
    
    void to_png( const std::string &file, unsigned int width, unsigned int height );*/
};

#endif /* worley_noise_h */
