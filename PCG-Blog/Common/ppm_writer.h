
#pragma once

#ifndef __PPM_WRITER_H__
#define __PPM_WRITER_H__

#include <string>
#include <vector>

struct Color {
	unsigned int m_red;
	unsigned int m_green;
	unsigned int m_blue;

	Color() : m_red( 0 ), m_green( 0 ), m_blue( 0 ) {}
	Color( unsigned int p_red, unsigned int p_green, unsigned int p_blue ) : m_red( p_red ), m_green( p_green ), m_blue( p_blue ) {}

	void operator=( const Color &p_color ) {
		m_red = p_color.m_red;
		m_green = p_color.m_green;
		m_blue = p_color.m_blue;
	}

	bool operator==( const Color &p_color ) const {
		return m_red == p_color.m_red &&
			   m_green == p_color.m_green &&
			   m_blue == p_color.m_blue;
	}

	bool operator!=( const Color &p_color ) const {
		return !operator==( p_color );
	}
};

namespace std {

	template<>
	struct hash<Color> {
		size_t operator()( const Color &p_color ) const {
			return ( ( hash<int>()( p_color.m_red ) ^ ( hash<int>()( p_color.m_green ) << 1 ) ) >> 1 ) ^ ( hash<int>()( p_color.m_blue ) << 1 );
		}
	};
};

class PPMWriter {

private:
	std::string m_file;
	unsigned int m_width;
	unsigned int m_height;

	std::vector<std::vector<Color>> m_image;

public:
	PPMWriter( unsigned int p_width, unsigned int p_height, const std::string &p_filepath = "" );

	void SetPixel( unsigned int p_x, unsigned int p_y, const Color &p_color );
	void SetPixel( unsigned int p_x, unsigned int p_y, unsigned int p_red, unsigned int p_green, unsigned int p_blue );

	Color GetPixel( unsigned int p_x, unsigned int p_y ) const;

	void Write();
	void Write( const std::string &p_file );
};

#endif