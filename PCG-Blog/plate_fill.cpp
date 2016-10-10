
#include "plate_fill.h"

#include <algorithm>
#include <iostream>

/*std::vector<Point> Plate::GetNeighbors() const {
	std::vector<Point> myNeighbors;

	for ( unsigned int i = 0; i < m_points.size(); i++ ) {
		if ( std::find( m_points.begin(), m_points.end(), Point( m_points[ i ].m_x - 1, m_points[ i ].m_y ) ) == m_points.end() ) {
			myNeighbors.push_back( Point( m_points[ i ].m_x - 1, m_points[ i ].m_y ) );
		}

		if ( std::find( m_points.begin(), m_points.end(), Point( m_points[ i ].m_x + 1, m_points[ i ].m_y ) ) == m_points.end() ) {
			myNeighbors.push_back( Point( m_points[ i ].m_x + 1, m_points[ i ].m_y ) );
		}

		if ( std::find( m_points.begin(), m_points.end(), Point( m_points[ i ].m_x, m_points[ i ].m_y - 1 ) ) == m_points.end() ) {
			myNeighbors.push_back( Point( m_points[ i ].m_x, m_points[ i ].m_y - 1 ) );
		}

		if ( std::find( m_points.begin(), m_points.end(), Point( m_points[ i ].m_x, m_points[ i ].m_y + 1 ) ) == m_points.end() ) {
			myNeighbors.push_back( Point( m_points[ i ].m_x, m_points[ i ].m_y + 1 ) );
		}
	}

	return myNeighbors;
}*/

void Plate::Add( const Point &p_point, unsigned int p_width, unsigned int p_height ) {
	m_points.push_back( p_point );

	if ( std::find( m_neighbors.begin(), m_neighbors.end(), p_point ) != m_neighbors.end() ) {
		m_neighbors.erase( std::remove( m_neighbors.begin(), m_neighbors.end(), p_point ), m_neighbors.end() );
	}

	Point myPoint = Point( Utility::clamp( p_point.m_x - 1, 0, p_width - 1 ), Utility::clamp( p_point.m_y, 0, p_height - 1 ) );
	if ( std::find( m_neighbors.begin(), m_neighbors.end(), myPoint ) == m_neighbors.end() ) {
		m_neighbors.push_back( myPoint );
	}

	myPoint = Point( Utility::clamp( p_point.m_x + 1, 0, p_width - 1 ), Utility::clamp( p_point.m_y, 0, p_height - 1 ) );
	if ( std::find( m_neighbors.begin(), m_neighbors.end(), myPoint ) == m_neighbors.end() ) {
		m_neighbors.push_back( myPoint );
	}

	myPoint = Point( Utility::clamp( p_point.m_x, 0, p_width - 1 ), Utility::clamp( p_point.m_y - 1, 0, p_height - 1 ) );
	if ( std::find( m_neighbors.begin(), m_neighbors.end(), myPoint ) == m_neighbors.end() ) {
		m_neighbors.push_back( myPoint );
	}

	myPoint = Point( Utility::clamp( p_point.m_x, 0, p_width - 1 ), Utility::clamp( p_point.m_y + 1, 0, p_height - 1 ) );
	if ( std::find( m_neighbors.begin(), m_neighbors.end(), myPoint ) == m_neighbors.end() ) {
		m_neighbors.push_back( myPoint );
	}
}

PlateFill::PlateFill( unsigned int p_width, unsigned int p_height, unsigned int p_numPlates ) {
	m_width = p_width;
	m_height = p_height;
	m_numPlates = p_numPlates;

	m_image = new PPMWriter( p_width, p_height );
}

PlateFill::~PlateFill() {
	if ( m_image != 0 ) {
		delete m_image;
	}
}

void PlateFill::Fill() {
	std::vector<Point> empty;
	for ( unsigned int i = 0; i < m_height; i++ ) {
		for ( unsigned int j = 0; j < m_width; j++ ) {
			empty.push_back( Point( i, j ) );
		}
	}

	std::vector<Point> myStarts;
	std::vector<Plate> myPlates;
	for ( unsigned int i = 0; i < m_numPlates; i++ ) {
		Point myStart;
		do { 
			myStart = Point( Utility::random_in_range( 0, m_width - 1 ), Utility::random_in_range( 0, m_height - 1 ) );
		} while ( std::find( myStarts.begin(), myStarts.end(), myStart ) != myStarts.end() );

		Plate myPlate;
		myPlate.Add( myStart, m_width, m_height );
		myPlates.push_back( myPlate );
	}

	do {
		for ( unsigned int i = 0; i < myPlates.size(); i++ ) {
			std::vector<Point> myNeighbors = myPlates[ i ].GetNeighbors();
			std::random_shuffle( myNeighbors.begin(), myNeighbors.end() );
			
			int myIndex = 0;
			do {
				if ( std::find( empty.begin(), empty.end(), myNeighbors[ myIndex ] ) != empty.end() ) {
					myPlates[ i ].Add( myNeighbors[ myIndex ], m_width, m_height );
					empty.erase( std::remove( empty.begin(), empty.end(), myNeighbors[ myIndex ] ), empty.end() );
					break;
				}

				myIndex++;
				if ( myIndex > myNeighbors.size() - 1 ) {
					m_plates.push_back( myPlates[ i ] );
					myPlates.erase( myPlates.begin() + i );
					i--;
					break;
				}
			} while ( true );
		}
	} while ( empty.size() > 0 );

	for ( unsigned int i = 0; i < myPlates.size(); i++ ) {
		m_plates.push_back( myPlates[ i ] );
	}
}

void PlateFill::to_ppm( const std::string &p_file ) {
	for ( unsigned int i = 0; i < m_numPlates; i++ ) {
		std::vector<Point> myPoints = m_plates[ i ].GetPoints();
		Color myColor( Utility::random_in_range( 0, 255 ), Utility::random_in_range( 0, 255 ), Utility::random_in_range( 0, 255 ) );
		for ( unsigned int j = 0; j < myPoints.size(); j++ ) {
			m_image->SetPixel( myPoints[ j ].m_x, myPoints[ j ].m_y, myColor );
		}
	}

	m_image->Write( p_file );
}