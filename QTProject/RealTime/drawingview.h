#pragma once
#include "Simd/SimdLib.hpp"
#include <iostream>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#ifndef TEXTRENDERING_H
#define TEXTRENDERING_H

namespace drw {
typedef Simd::Point<ptrdiff_t> Point;
typedef Simd::View<Simd::Allocator> View;


bool RenderText(View& view, std::string const text, int x, int y, int font_size, Simd::Pixel::Bgr24 color);
void DrawLine(View& view, int x0, int y0, int x1, int y1, Simd::Pixel::Bgr24 color);

}
#endif // TEXTRENDERING_H
