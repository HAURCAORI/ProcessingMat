#include "drawingview.h"



bool drw::RenderText(View& view, std::string const text, int x, int y, int font_size, Simd::Pixel::Bgr24 color)
{

    if(x > view.width || x < 0 || y > view.height || y < 0)
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

        for (int sy = y-face->glyph->bitmap_top, cy = 0; cy < h; sy++, cy++)
        {
            if(sy < 0) { continue; }
            for (int sx = x + face->glyph->bitmap_left, cx = 0; cx < w; sx++, cx++)
            {
                if(sx >= view.width) { continue; }

                int index = sy*view.width*4+sx*4;
                int index2 = cy*w+cx;
                uint8_t mask = face->glyph->bitmap.buffer[index2]^0xff;
                uint8_t imask = mask^0xff;
                view.data[index] = ((view.data[index]*mask)>>8)+((color.red*imask)>>8);
                view.data[index + 1] = ((view.data[index+1]*mask)>>8)+((color.green*imask)>>8);
                view.data[index + 2] = ((view.data[index+2]*mask)>>8)+((color.blue*imask)>>8);
            }
        }

        x += face->glyph->advance.x >> 6;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    return true;
}

void drw::DrawLine(View& view, int x0, int y0, int x1, int y1, Simd::Pixel::Bgr24 color){
    int dx, dy, p, x, y;

    dx=x1-x0;
    dy=y1-y0;

    x=x0;
    y=y0;

    p=2*dy-dx;

    while(x<x1)
    {
        if(p>=0)
        {
            //uint8_t * p =drw::Pixels(view,x,y)
            //putpixel(x,y,7);
            y=y+1;
            p=p+2*dy-2*dx;
        }
        else
        {
            //putpixel(x,y,7);
            p=p+2*dy;
        }
        x=x+1;
    }
}
