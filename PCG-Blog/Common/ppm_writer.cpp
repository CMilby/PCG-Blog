
#include "ppm_writer.h"

#include <cassert>
#include <fstream>
#include <iostream>

PPMWriter::PPMWriter( unsigned int p_width, unsigned int p_height, const std::string &p_filepath ) : m_width( p_width ), m_height( p_height ), m_file( p_filepath ) {
	m_image.resize( p_height );
	for ( unsigned int i = 0; i < p_height; i++ ) {
		m_image[ i ].resize( p_width );
		for ( unsigned int j = 0; j < m_width; j++ ) {
			m_image[ i ][ j ] = Color( 0, 0, 0 );
		}
	}
}

void PPMWriter::SetPixel( unsigned int p_x, unsigned int p_y, const Color &p_color ) {
	assert( p_x < m_width );
	assert( p_y < m_height );

	m_image[ p_y ][ p_x ] = p_color;
}
	
void PPMWriter::SetPixel( unsigned int p_x, unsigned int p_y, unsigned int p_red, unsigned int p_green, unsigned int p_blue ) {
	SetPixel( p_x, p_y, Color( p_red, p_green, p_blue ) );
}

Color PPMWriter::GetPixel( unsigned int p_x, unsigned int p_y ) const {
	return m_image[ p_y ][ p_x ];
}

void PPMWriter::Write() {
	assert( m_file != "" );
	Write( m_file );
}

void PPMWriter::Write( const std::string &p_file ) {
	m_file = p_file;

	std::ofstream myFile( p_file.c_str() );
	if ( !myFile.is_open() ) {
		throw "Error: File not found, opended, or created.";
	}

	// Header                                       This "255" may change
	myFile << "P3\n" << m_width << " " << m_height << "\n255\n";
	
	std::string myLine;
	for ( unsigned int i = 0; i < m_height; i++ ) {
		myLine = "";
		for ( unsigned int j = 0; j < m_width; j++ ) {
			std::string myRed = std::to_string( ( unsigned long long ) m_image[ i ][ j ].m_red );
			std::string myGreen = std::to_string( ( unsigned long long ) m_image[ i ][ j ].m_green );
			std::string myBlue = std::to_string( ( unsigned long long ) m_image[ i ][ j ].m_blue );

			while ( myRed.length() != 3 ) {
				myRed = " " + myRed;
			}

			while ( myGreen.length() != 3 ) {
				myGreen = " " + myGreen;
			}

			while ( myBlue.length() != 3 ) {
				myBlue = " " + myBlue;
			}

			myLine += myRed + " " + myGreen + " " + myBlue;
			if ( j != m_width - 1 ) {
				myLine += "   ";
			}

			myFile << myLine;
			myLine = "";
		}

		myFile << "\n";
	}

	myFile.close();
}