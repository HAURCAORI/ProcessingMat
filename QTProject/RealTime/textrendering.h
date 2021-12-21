#pragma once
#include "Simd/SimdLib.hpp"
#include <iostream>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#ifndef TEXTRENDERING_H
#define TEXTRENDERING_H

namespace gly {
typedef Simd::Point<ptrdiff_t> Point;
typedef Simd::View<Simd::Allocator> View;

struct Character {
    View Texture;  // ID handle of the glyph texture
    Point Size;       // Size of glyph
    Point Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class TextRendering
{
private:
    std::map<char, Character> Characters;
public:
    TextRendering();
    bool Init();
    void RenderText(View& view, std::string const text, float x, float y, float scale, View::Bgr24);
};
}
#endif // TEXTRENDERING_H
