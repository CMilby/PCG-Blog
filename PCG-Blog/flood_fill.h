
#pragma once

#ifndef __FLOOD_FILL_H__
#define __FLOOD_FILL_H__

#include <string>

#include "ppm_writer.h"
#include "utility.h"

class FloodFill {

private:
	unsigned int m_width;
	unsigned int m_height;

	PPMWriter *m_image;

public:
	FloodFill( unsigned int p_width, unsigned int p_height );
	virtual ~FloodFill();

	void Fill( int p_x, int p_y, int p_amount, const Color &p_targetColor );
	void Fill( int p_x, int p_y, int p_amount, const Color &p_targetColor, const Color &p_replacementColor );

	void to_ppm( const std::string &p_file );

private:

};

#endif