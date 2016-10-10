//
//  utility.h
//  PCG-Blog
//
//  Created by Craig Milby on 10/11/15.
//  Copyright © 2015 Craig Milby. All rights reserved.
//

#pragma once

#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))

template<class T, unsigned int D> class Vector {
    
private:
    T m_values[ D ];
    
public:
    Vector() {
        for ( unsigned int i = 0; i < D; i++ )
            m_values[ i ] = T( 0 );
    }
    
    Vector( const Vector<T, D> &vect ) {
        for ( unsigned int i = 0; i < D; i++ )
            m_values[ i ] = vect[ i ];
    }
    
	Vector( const T &p_x, const T &p_y ) {
		m_values[ 0 ] = p_x;
		m_values[ 1 ] = p_y;
	}

    inline T Dot( const Vector<T, D> &vect ) const {
        T result = T( 0 );
        for ( unsigned int i = 0; i < D; i++ ) {
            result += ( *this )[ i ] * vect[ i ];
        }
        return result;
    }
    
    inline T LengthSq() const {
        return this->Dot( *this );
    }
    
    inline T Length() const {
        return sqrt( LengthSq() );
    }
    
    inline Vector<T, D> Normalized() const {
        return *this / Length();
    }
    
    inline T Max() const {
        T max = m_values[ 0 ];
        for ( unsigned int i = 1; i < D; i++ ) {
            if ( m_values[ i ] > max ) {
                max = m_values[ i ];
            }
        }
        return max;
    }
    
    inline Vector<T, D> Max( const Vector<T, D> &pOther ) const {
        Vector<T, D> myResult;
        for ( unsigned int i = 0; i < D; i++ ) {
            myResult[ i ] = m_values[ i ] > pOther[ i ] ? m_values[ i ] : pOther[ i ];
        }
        return myResult;
    }
    
    inline T Min() const {
        T min = m_values[ 0 ];
        for ( unsigned int i = 1; i < D; i++ ) {
            if ( m_values[ i ] < min ) {
                min = m_values[ i ];
            }
        }
        return min;
    }
    
    inline Vector<T, D> Reflect( const Vector<T, D> &pNormal ) const {
        return *this - ( pNormal * ( this->Dot( pNormal ) * 2 ) );
    }
    
    inline Vector<T, D> Midpoint( const Vector<T, D> &pOther ) const {
        Vector<T, D> myResult;
        for ( unsigned int i = 0; i < D; i++ ) {
            myResult[ i ] = ( m_values[ i ] + pOther[ i ] ) / T( 2 );
        }
        return myResult;
    }
    
    inline Vector<T, D> operator+( const Vector<T, D> &vect ) const {
        Vector<T, D> sum;
        for ( unsigned int i = 0; i < D; i++ ) {
            sum[ i ] = m_values[ i ] + vect[ i ];
        }
        return sum;
    }
    
    inline Vector<T, D> operator+( const T &pScalar ) const {
        Vector<T, D> mySum;
        for ( unsigned int i = 0; i < D; i++ ) {
            mySum[ i ] = m_values[ i ] + pScalar;
        }
        return mySum;
    }
    
    inline Vector<T, D>& operator+=( const Vector<T, D> &vect ) {
        for ( unsigned int i = 0; i < D; i++ ) {
            ( *this )[ i ] = m_values[ i ] + vect[ i ];
        }
        return *this;
    }
    
    inline Vector<T, D> operator-( const Vector<T, D> &vect ) const {
        Vector<T, D> difference;
        for ( unsigned int i = 0; i < D; i++ ) {
            difference[ i ] = m_values[ i ] - vect[ i ];
        }
        return difference;
    }
    
    inline Vector<T, D> operator-( const T &pScalar ) const {
        Vector<T, D> myDifferece;
        for ( unsigned int i = 0; i < D; i++ ) {
            myDifferece[ i ] = m_values[ i ] - pScalar;
        }
        return myDifferece;
    }
    
    inline Vector<T, D>& operator-=( const Vector<T, D> &vect ) {
        for ( unsigned int i = 0; i < D; i++ ) {
            m_values[ i ] -= vect[ i ];
        }
        return  *this;
    }
    
    inline Vector<T, D> operator*( const T &scale ) const {
        Vector<T, D> product;
        for ( unsigned int i = 0; i < D; i++ ) {
            product[ i ] = m_values[ i ] * scale;
        }
        return product;
    }
    
    inline Vector<T, D> operator*( const Vector<T, D> &vect ) {
        Vector<T, D> product;
        for ( unsigned int i = 0; i < D; i++ ) {
            product[ i ] = ( *this )[ i ] * vect[ i ];
        }
        return product;
    }
    
    inline Vector<T, D>& operator*=( const T &scale ) {
        for ( unsigned int i = 0; i < D; i++ ) {
            m_values[ i ] *= scale;
        }
        return *this;
    }
    
    inline Vector<T, D> operator/( const T &scale ) const {
        Vector<T, D> quotient;
        for ( unsigned int i = 0; i < D; i++ ) {
            quotient[ i ] = m_values[ i ] / scale;
        }
        return quotient;
    }
    
    inline Vector<T, D>& operator/=( const T &scale ) {
        for ( unsigned int i = 0; i < D; i++ ) {
            m_values[ i ] /= scale;
        }
        return *this;
    }
    
    inline bool operator==( const Vector<T, D> &vect ) const {
        for ( unsigned int i = 0; i < D; i++ ) {
            if ( m_values[ i ] != vect[ i ] )
                return false;
        }
        return true;
    }
    
    inline bool operator!=( const Vector<T, D> &vect ) const {
        return !operator==( vect );
    }
    
    inline bool operator<( const Vector<T, D> &vect ) const {
        for ( unsigned int i = 0; i < D; i++ ) {
            if ( m_values[ i ] >= vect[ i ] )
                return false;
        }
        return true;
    }
    
    inline bool operator>( const Vector<T, D> &vect ) const {
        for ( unsigned int i = 0; i < D; i++ ) {
            if ( m_values[ i ] <= vect[ i ] )
                return false;
        }
        return true;
    }
    
    inline bool operator<=( const Vector<T, D> &vect ) const {
        for ( unsigned int i = 0; i < D; i++ ) {
            if ( m_values[ i ] > vect[ i ] )
                return false;
        }
        return true;
    }
    
    inline bool operator>=( const Vector<T, D> &vect ) const {
        for ( unsigned int i = 0; i < D; i++ ) {
            if ( m_values[ i ] < vect[ i ] )
                return false;
        }
        return true;
    }
    
    inline T& operator[]( unsigned int index ) {
        return m_values[ index ];
    }
    
    inline T operator[]( unsigned int index ) const {
        return m_values[ index ];
    }
    
    inline void Print() const {
        for ( unsigned int i = 0; i < D; i++ ) {
            std::cout << m_values[ i ] << " ";
        }
        std::cout << "\n";
    }
};

class Point {
    
public:
    int m_x;
    int m_y;
    
    Point() {
        m_x = m_y = 0;
    }
    
    Point( int x, int y ) {
        m_x = x;
        m_y = y;
    }
    
	inline void operator=( const Point &p_point ) {
		m_x = p_point.m_x;
		m_y = p_point.m_y;
	}

	inline bool operator==( const Point &p_point ) const {
		return m_x == p_point.m_x && m_y == p_point.m_y;
	}

    inline Point operator-( const Point &p ) const {
        return Point( m_x - p.m_x, m_y - p.m_y );
    }
};

namespace std {

	template<>
	struct hash<Point> {
		size_t operator()( const Point &p_point ) const {
			return ( ( hash<int>()( p_point.m_x ) ^ ( hash<int>()( p_point.m_y ) << 1 ) ) >> 1 );
		}
	};
};

namespace Utility {
    
    extern unsigned int OFFSET_BASIS;
    extern unsigned int FNV_PRIME;
    
    void print_map( const std::vector<char> &map, unsigned int width, unsigned int height );
    void print_map( const std::vector<std::string> &map, unsigned int width, unsigned int height );
    
    std::vector<char> blank_map( char delim, unsigned int width, unsigned int height );
    
    float scale( float x, float a, float b, float min, float max );
    float min( const std::vector<float> &vect );
    float max( const std::vector<float> &vect );
    
    int random_in_range( int min, int max );
    float random_in_range( float min, float max );
    unsigned int lcg_random( unsigned int last );
    
    int clamp( int value, int min, int max );
    float clampf( float value, float min, float max );
    
    float dot( const int *p_g, const float p_x, const float p_y );
    float dot( const int *g, const float x, const float y, const float z );
    int fast_floor( const float x );

	float distance( const int p_x1, const int p_y1, const int p_x2, const int p_y2 );
}

#endif