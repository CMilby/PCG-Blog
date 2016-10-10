
#include "voronoi.h"

#include <unordered_map>

Voronoi::Voronoi( unsigned int p_width, unsigned int p_height, const std::vector<Point> &p_points ) {
	m_width = p_width;
	m_height = p_height;
	m_points = p_points;

	m_image = new PPMWriter( p_width, p_height );
}

Voronoi::~Voronoi() {
	if ( m_image != 0 ) {
		delete m_image;
	}
}

void Voronoi::to_ppm( const std::string &p_file ) {
	std::unordered_map<Point, Color> m_colorMap;
	for ( unsigned int i = 0; i < m_points.size(); i++ ) {
		m_colorMap.insert( std::pair<Point, Color>( m_points[ i ], Color( Utility::random_in_range( 0, 255 ), Utility::random_in_range( 0, 255 ), Utility::random_in_range( 0, 255 ) ) ) );
	}
	
	for ( unsigned int i = 0; i < m_height; i++ ) {
		for ( unsigned int j = 0; j < m_width; j++ ) {
			float myMinDistance = m_width * m_height;
			Point myMinDistanceIndex = m_points[ 0 ];
			for ( int k = 0; k < m_points.size(); k++ ) {
				float myDistance = Utility::distance( i, j, m_points[ k ].m_x, m_points[ k ].m_y );
				if ( myDistance < myMinDistance ) {
					myMinDistance = myDistance;
					myMinDistanceIndex = m_points[ k ];
				}
			}

			m_image->SetPixel( i, j, m_colorMap[ myMinDistanceIndex ] );
		}
	}

	m_image->Write( p_file );
}