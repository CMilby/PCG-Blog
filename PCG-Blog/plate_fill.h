
#pragma once

#ifndef __PLATE_FILL_H__
#define __PLATE_FILL_H__

#include "ppm_writer.h"
#include "utility.h"

class Plate {

private:
	std::vector<Point> m_points;
	std::vector<Point> m_neighbors;

public:
	Plate() {

	}

	inline std::vector<Point> GetPoints() const {
		return m_points;
	}

	// inline void Add( const Point &p_point );
	inline void Add( const Point &p_point, unsigned int p_width, unsigned int p_height );

	inline std::vector<Point> GetNeighbors() const {
		return m_neighbors;
	}
};

class PlateFill {

private:
	unsigned int m_width;
	unsigned int m_height;
	
	unsigned int m_numPlates;
	std::vector<Plate> m_plates;

	PPMWriter *m_image;

public:
	PlateFill( unsigned int p_width, unsigned int p_height, unsigned int p_numPlates );
	virtual ~PlateFill();

	void Fill();
	void to_ppm( const std::string &p_file );
};

#endif