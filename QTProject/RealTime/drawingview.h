#pragma once
#include "Simd/SimdLib.hpp"
#include <iostream>
#include <map>
#include <ft2build.h>

#include <smmintrin.h>
#include <immintrin.h>
#include <stdio.h>

#include FT_FREETYPE_H

#ifndef TEXTRENDERING_H
#define TEXTRENDERING_H

#define CHANNEL 4

#if CHANNEL == 4
  #define FORMAT View::Bgra32
  #define FORMATQT QImage::Format_ARGB32
#elif CHANNEL == 3
  #define FORMAT View::Bgr24
  #define FORMATQT QImage::Format_RGB888
#else
  #define FORMAT View::Bgra32
  #define FORMATQT QImage::Format_ARGB32
#endif


  #include <chrono>
  #define BEGIN_CHRONO std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  #define END_CHRONO std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count() << "[ms]" << std::endl;

typedef Simd::Point<ptrdiff_t> Point;
typedef Simd::View<Simd::Allocator> View;

namespace drw {

inline float SQRT2() {
    return std::sqrt(2);
}

inline uint8_t* getPixel(View& view,int x,int y) {
    return &view.data[(CHANNEL*(x))+(view.width*CHANNEL*(y))];
}

inline uint8_t* getPixel(uint8_t*& data,int x,int y) {
    return &data[(CHANNEL*(x))+(view.width*CHANNEL*(y))];
}


inline size_t getStride(View& view) {
    return view.width;
}

Simd::Pixel::Bgra32 operator*(const Simd::Pixel::Bgr24 &color, float value);
Simd::Pixel::Bgra32 operator*(const Simd::Pixel::Bgr24 &color, uint8_t value);

void setPixel(uint8_t*& src, const Simd::Pixel::Bgr24 &color);
void setPixel(uint8_t*& src, const Simd::Pixel::Bgra32 &color);
void setPixel(View& view,int x, int y, const Simd::Pixel::Bgr24 &color);
void setPixel(View& view,int x, int y, const Simd::Pixel::Bgra32 &color);

void Overlay(View& dest, int x, int y, View& src);
void AlphaBlend(uint8_t*& dest, int x, int y, uint8_t*& mask, int mw, int mh, const Simd::Pixel::Bgr24& color);

bool RenderText(View& view, std::string const text, int x, int y, int font_size, const Simd::Pixel::Bgr24& color);
void DrawLine(View& view, int x0, int y0, int x1, int y1, const Simd::Pixel::Bgr24& color);
void DrawLineAL(View& view, float x0, float y0, float x1, float y1, const Simd::Pixel::Bgr24& color);
void DrawLine(View& view, int x0, int y0, int x1, int y1, float wd, const Simd::Pixel::Bgr24& color);
void DrawCircle(View& view, int x0, int y0, int radius, const Simd::Pixel::Bgr24& color);
void DrawCircleAL(View& view, int x0, int y0, int r, const Simd::Pixel::Bgr24& color);
void DrawQuarter(View& view,int x0,int y0, float x, float y, const Simd::Pixel::Bgra32& color);

}
#endif // TEXTRENDERING_H
