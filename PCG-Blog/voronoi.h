
#pragma once

#ifndef __VORONOI_H__
#define __VORONOI_H__

#include "ppm_writer.h"
#include "utility.h"

class Voronoi {

private:
	unsigned int m_width;
	unsigned int m_height;

	std::vector<Point> m_points;

	PPMWriter *m_image;

public:
	Voronoi( unsigned int p_width, unsigned int p_height, const std::vector<Point> &p_points );
	virtual ~Voronoi();

	void to_ppm( const std::string &p_file );
};

#endif