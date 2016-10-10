
#include "flood_fill.h"

FloodFill::FloodFill( unsigned int p_width, unsigned int p_height ) {
	m_image = new PPMWriter( p_width, p_height );

	m_width = p_width;
	m_height = p_height;
}

FloodFill::~FloodFill() {
	if ( m_image != 0 ) {
		delete m_image;
	}
}

void FloodFill::Fill( int p_x, int p_y, int p_amount, const Color &p_replacementColor ) {
	
}

void FloodFill::Fill( int p_x, int p_y, int p_amount, const Color &p_targetColor, const Color &p_replacementColor ) {
	if ( p_amount <= 0 ) {
		return;
	}

	if ( p_x < 0 ) {
		p_x = m_width - p_x;
		return;
	}

	if ( p_y < 0 ) {
		p_y = m_height - p_y;
	}

	if ( p_x > m_width - 1 ) {
		p_x = p_x - m_width;
	}

	if ( p_y > m_height - 1 ) {
		p_y = p_y - m_height;
	}

	m_image->SetPixel( p_x, p_y, p_replacementColor );
	p_amount--;

	// Now we need to randomly fill around it
}

void FloodFill::to_ppm( const std::string &p_file ) {
	m_image->Write( p_file );
}