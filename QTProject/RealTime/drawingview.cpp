#include "drawingview.h"

Simd::Pixel::Bgra32 drw::operator*(const Simd::Pixel::Bgr24 &color, float value) {
    Simd::Pixel::Bgra32 temp(color.blue ,color.green ,color.red, std::round(value*255.0));
    return temp;
}
Simd::Pixel::Bgra32 drw::operator*(const Simd::Pixel::Bgr24 &color, uint8_t value) {
    Simd::Pixel::Bgra32 temp(color.blue ,color.green ,color.red, value^0xff);
    return temp;
}

void drw::setPixel(uint8_t*& src, const Simd::Pixel::Bgr24 &color) {
    *(src++) = color.red;
    *(src++) = color.green;
    *(src++) = color.blue;
#if CHANNEL==4
    *(src++) = 255;
#endif
}
void drw::setPixel(uint8_t*& src, const Simd::Pixel::Bgra32 &color) {
    uint8_t imask = color.alpha;
    uint8_t mask = imask^0xff;
    *(src) = ((*(src)*mask)>>8)+((color.red*imask)>>8);
    ++src;
    *(src) = ((*(src)*mask)>>8)+((color.green*imask)>>8);
    ++src;
    *(src) = ((*(src)*mask)>>8)+((color.blue*imask)>>8);
    ++src;
#if CHANNEL==4
    *(src++) = 255;
#endif
}

void drw::setPixel(View& view,int x, int y, const Simd::Pixel::Bgr24 &color) {
    if((unsigned int) x >= view.width || x < 0 || (unsigned int) y >= view.height || y < 0)
    {
        return;
    }
    uint8_t* src = getPixel(view,x,y);
    setPixel(src,color);
}
void drw::setPixel(View& view,int x, int y, const Simd::Pixel::Bgra32 &color) {
    if((unsigned int) x >= view.width || x < 0 || (unsigned int) y >= view.height || y < 0)
    {
        return;
    }
    uint8_t* src = getPixel(view,x,y);
    if(color.alpha == 0xff) {
        setPixel(src,(Simd::Pixel::Bgr24) color);
    } else {
        setPixel(src,color);
    }
}

void drw::Overlay(View& dest, int x, int y, View& src) {
    int h = src.height;
    int w = src.width;
    for (int sy = y, cy = 0; cy < h; sy++, cy++)
    {
        if((unsigned int) sy >= dest.height) { break; }
        int sx = x;
        int cx = 0;
        for (; cx + 8 <= w; sx+=8, cx+=8)
        {
            if( (unsigned int) sx + 8 >= dest.width) { break; }
            __m256i dm = _mm256_loadu_si256((__m256i_u*) getPixel(src,cx,cy));
            _mm256_storeu_si256((__m256i*) getPixel(dest,sx,sy),dm);
        }

        for(; cx < w; sx++, cx++) {
            if( (unsigned int) sx >= dest.width) { break; }
            uint8_t* dp = getPixel(dest,sx,sy);
            uint8_t* sp = getPixel(src,cx,cy);
            *(dp++) = *(sp++);
            *(dp++) = *(sp++);
            *(dp++) = *(sp++);
            *(dp++) = *(sp++);
        }
    }
}

void drw::AlphaBlend(View& dest, int x, int y, uint8_t*& alpha, int w, int h, const Simd::Pixel::Bgr24& color) {
    for (int sy = y, cy = 0; cy < h; sy++, cy++)
    {
        if(sy < 0) { continue; }
        int sx = x;
        int cx = 0;

        for (; cx < w; sx++, cx++)
        {
            if( (unsigned int) sx >= dest.width) { continue; }
            uint8_t* src2 = getPixel(dest,sx,sy);
            int index2 = cy*w + cx;

            uint8_t imask = alpha[index2];
            uint8_t mask = imask^0xff;

            *(src2++) = ((*(src2)*mask)>>8)+((color.red*imask)>>8);
            *(src2++) = ((*(src2)*mask)>>8)+((color.green*imask)>>8);
            *(src2++) = ((*(src2)*mask)>>8)+((color.blue*imask)>>8);
        }
    }
    /*
    uint32_t rgb = (0xff) | (uint32_t(color.blue) << 8) | (uint32_t(color.green) << 16) | (uint32_t(color.red) << 24);
    __m256i src = _mm256_set1_epi32(rgb);
    for (int sy = y, cy = 0; cy < h; sy++, cy++)
    {
        if(sy < 0) { continue; }
        int sx = x;
        int cx = 0;

        for (; cx + 8 < w; sx+=8, cx+=8)
        {
            if( (unsigned int) sx >= dest.width) { break; }

            int index2 = cy*w+cx;
            __m256i dm = _mm256_loadu_si256((__m256i_u*) getPixel(dest, sx,sy));
            uint32_t alpha_mask[8];
            for(int i = 0; i < 8; i++)
            {
                alpha_mask[i] = uint32_t(alpha[index2+i]) | (uint32_t(alpha[index2+i]) << 8) | (uint32_t(alpha[index2+i]) << 16) | (uint32_t(alpha[index2+i]) << 24);
            }

            __m256i mask = _mm256_setr_epi32(alpha_mask[0],alpha_mask[1],alpha_mask[2],alpha_mask[3],alpha_mask[4],alpha_mask[5],alpha_mask[6],alpha_mask[7]);
            __m256i imask = _mm256_sub_epi8(max, mask);

            __m256i lo = AlphaBlendingI16(_mm256_unpacklo_epi8(dm, zero), _mm256_unpacklo_epi8(src, zero), _mm256_unpacklo_epi8(imask, zero), _mm256_unpacklo_epi8(mask, zero));
            __m256i hi = AlphaBlendingI16(_mm256_unpackhi_epi8(dm, zero), _mm256_unpackhi_epi8(src, zero), _mm256_unpackhi_epi8(imask, zero), _mm256_unpacklo_epi8(mask, zero));

            _mm256_storeu_si256((__m256i*) getPixel(dest,sx,sy),_mm256_packus_epi16(lo, hi));


            uint8_t* d = getPixel(dest,sx,sy);
            __m256i dm = _mm256_loadu_si256((__m256i_u*) d);

            int index2 = cy*w+cx;
            uint8_t mask = alpha[index2]^0xff;
            uint8_t imask = mask^0xff;

            *(src++) = ((*(src)*mask)>>8)+((color.red*imask)>>8);
            *(src++) = ((*(src)*mask)>>8)+((color.green*imask)>>8);
            *(src++) = ((*(src)*mask)>>8)+((color.blue*imask)>>8);

        }

        for (; cx < w; sx++, cx++)
        {
            if( (unsigned int) sx >= dest.width) { continue; }
            uint8_t* src2 = getPixel(dest,sx,sy);
            int index2 = cy*w + cx;

            uint8_t imask = alpha[index2];
            uint8_t mask = imask^0xff;

            *(src2++) = ((*(src2)*mask)>>8)+((color.red*imask)>>8);
            *(src2++) = ((*(src2)*mask)>>8)+((color.green*imask)>>8);
            *(src2++) = ((*(src2)*mask)>>8)+((color.blue*imask)>>8);
        }
    }
*/
}

bool drw::RenderText(View& view, std::string const text, int x, int y, int font_size, const Simd::Pixel::Bgr24& color)
{
    if((unsigned int) x > view.width || x < 0 || (unsigned int) y > view.height || y < 0)
    {
        return false;
    }

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return false;
    }

    FT_Face face;
    if (FT_New_Face(ft, "/usr/share/fonts/truetype/ubuntu/Ubuntu-L.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, font_size);

    std::string::const_iterator c;

    for (c = text.begin(); c != text.end(); c++)
    {
        if (FT_Load_Char(face, *c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        float w = face->glyph->bitmap.width;
        float h = face->glyph->bitmap.rows;
        //drw::AlphaBlend(view ,x + face->glyph->bitmap_left, y - face->glyph->bitmap_top, face->glyph->bitmap.buffer,w,h,color);


        for (int sy = y-face->glyph->bitmap_top, cy = 0; cy < h; sy++, cy++)
        {
            if(sy < 0) { continue; }
            for (int sx = x + face->glyph->bitmap_left, cx = 0; cx < w; sx++, cx++)
            {
                if( (unsigned int) sx >= view.width) { continue; }

                uint8_t* src = getPixel(view,sx,sy);
                int index2 = cy*w+cx;
                uint8_t mask = face->glyph->bitmap.buffer[index2]^0xff;
                uint8_t imask = mask^0xff;
                *(src++) = ((*(src)*mask)>>8)+((color.red*imask)>>8);
                *(src++) = ((*(src)*mask)>>8)+((color.green*imask)>>8);
                *(src++) = ((*(src)*mask)>>8)+((color.blue*imask)>>8);
            }
        }

        x += face->glyph->advance.x >> 6;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return true;
}

void drw::DrawLine(View& view, int x0, int y0, int x1, int y1, const Simd::Pixel::Bgr24& color){
    int dx, dy, p, x, y;

    dx=x1-x0;
    dy=y1-y0;

    x=x0;
    y=y0;

    p=2*dy-dx;

    uint8_t* src = getPixel(view,x0,y0);
    size_t stride = getStride(view);

    while(x<x1)
    {
        if(p>=0)
        {
            setPixel(src,color);

            src += stride*CHANNEL;
            y=y+1;
            p=p+2*dy-2*dx;
        }
        else
        {
            setPixel(src,color);

            p=p+2*dy;
        }
        x=x+1;
    }
}


void drw::DrawLineAL(View& view, float x0, float y0, float x1, float y1, const Simd::Pixel::Bgr24& color) {
    auto ipart = [](float x) -> int {return int(std::floor(x));};
    auto round = [](float x) -> float {return std::round(x);};
    auto fpart = [](float x) -> float {return x - std::floor(x);};
    auto rfpart = [=](float x) -> float {return 1 - fpart(x);};

    const bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        std::swap(x0,y0);
        std::swap(x1,y1);
    }
    if (x0 > x1) {
        std::swap(x0,x1);
        std::swap(y0,y1);
    }

    const float dx = x1 - x0;
    const float dy = y1 - y0;
    const float gradient = (dx == 0) ? 1 : dy/dx;

    int xpx11;
    float intery;
    {
        const float xend = round(x0);
        const float yend = y0 + gradient * (xend - x0);
        const float xgap = rfpart(x0 + 0.5);
        xpx11 = int(xend);
        const int ypx11 = ipart(yend);
        if (steep) {
            setPixel(view,ypx11,xpx11,color*(rfpart(yend) * xgap)); // rfpart(yend) * xgap
            setPixel(view,ypx11+1,xpx11,color*(fpart(yend) * xgap)); // fpart(yend) * xgap
        } else {
            setPixel(view,xpx11,ypx11,color*(rfpart(yend) * xgap)); // rfpart(yend) * xgap
            setPixel(view,xpx11,ypx11+1,color*(fpart(yend) * xgap)); // fpart(yend) * xgap
        }
        intery = yend + gradient;
    }

    int xpx12;
    {
        const float xend = round(x1);
        const float yend = y1 + gradient * (xend - x1);
        const float xgap = rfpart(x1 + 0.5);
        xpx12 = int(xend);
        const int ypx12 = ipart(yend);
        if (steep) {
            setPixel(view,ypx12,xpx12,color*(rfpart(yend) * xgap)); // rfpart(yend) * xgap
            setPixel(view,ypx12+1,xpx12,color*(fpart(yend) * xgap)); // fpart(yend) * xgap
        } else {
            setPixel(view,xpx12,ypx12,color*(rfpart(yend) * xgap)); // rfpart(yend) * xgap
            setPixel(view,xpx12,ypx12+1,color*(fpart(yend) * xgap)); // fpart(yend) * xgap
        }
    }

    if (steep) {
        for (int x = xpx11 + 1; x < xpx12; x++) {
            setPixel(view,ipart(intery),x,color*(rfpart(intery))); // rfpart(intery)
            setPixel(view,ipart(intery)+1,x,color*(fpart(intery))); // fpart(intery)
            intery += gradient;
        }
    } else {
        for (int x = xpx11 + 1; x < xpx12; x++) {
            setPixel(view,x,ipart(intery),color*(rfpart(intery))); // rfpart(intery)
            setPixel(view,x,ipart(intery)+1,color*(fpart(intery))); // fpart(intery)
            intery += gradient;
        }
    }
}

void drw::DrawLine(View& view, int x0, int y0, int x1, int y1, float wd, const Simd::Pixel::Bgr24& color){
   int dx = abs(x1-x0), sx = x0 < x1 ? 1 : -1;
   int dy = abs(y1-y0), sy = y0 < y1 ? 1 : -1;
   int err = dx-dy, e2, x2, y2;                          /* error value e_xy */
   float ed = dx+dy == 0 ? 1 : sqrt((float)dx*dx+(float)dy*dy);

   for (wd = (wd+1)/2; ; ) {                                   /* pixel loop */
      setPixel(view,x0,y0,color*((uint8_t) std::max(0.0f,255*(abs(err-dx+dy)/ed-wd+1))));
      e2 = err; x2 = x0;
      if (2*e2 >= -dx) {                                           /* x step */
         for (e2 += dy, y2 = y0; e2 < ed*wd && (y1 != y2 || dx > dy); e2 += dx)
            setPixel(view,x0, y2 += sy, color*((uint8_t) std::max(0.0f,255*(abs(e2)/ed-wd+1))));
         if (x0 == x1) break;
         e2 = err; err -= dy; x0 += sx;
      }
      if (2*e2 <= dy) {                                            /* y step */
         for (e2 = dx-e2; e2 < ed*wd && (x1 != x2 || dx < dy); e2 += dy)
            setPixel(view,x2 += sx, y0, color*((uint8_t) std::max(0.0f,255*(abs(e2)/ed-wd+1))));
         if (y0 == y1) break;
         err += dx; y0 += sy;
      }
   }
}


void drw::DrawCircle(View& view, int x0, int y0, int radius, const Simd::Pixel::Bgr24& color)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        DrawQuarter(view,x0,y0,x,y,color);
        DrawQuarter(view,x0,y0,y,x,color);

        if (err <= 0) {
            y += 1;
            err += 2*y + 1;
        }

        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }

}


void drw::DrawCircleAL(View& view, int x0, int y0, int r, const Simd::Pixel::Bgr24& color) {
    auto fpart = [](float x) -> float {return x - std::floor(x);};
    auto floor = [](float x) -> float {return std::floor(x);};
    auto round = [](float x) -> float {return std::round(x);};


    float rsq = r*r;
    float ffd = round(r/SQRT2());

    for(int xi = 0; xi < ffd; xi++) {
      float yj = std::sqrt(rsq - xi*xi);  // the "step 2" formula noted above
      float frc = fpart(yj);
      float flr = floor(yj);

      DrawQuarter(view,x0,y0,xi,flr,color*(1-frc));
      DrawQuarter(view,x0,y0,xi,flr+1,color*(frc));
    }

    for(int yi = 0; yi < ffd; yi++) {
      float xj = std::sqrt (rsq-yi*yi);
      float frc = fpart(xj);
      float flr = floor(xj);
      DrawQuarter(view,x0,y0,flr,yi,color*(1-frc));
      DrawQuarter(view,x0,y0,flr+1,yi,color*(frc));
    }
}

void drw::DrawQuarter(View& view,int x0,int y0, float x, float y, const Simd::Pixel::Bgra32& color) {
    setPixel(view,x0 + x, y0 + y, color);
    setPixel(view,x0 - x, y0 + y, color);
    setPixel(view,x0 - x, y0 - y, color);
    setPixel(view,x0 + x, y0 - y, color);
}
