#include "textrendering.h"

gly::TextRendering::TextRendering(){
    Init();
}
bool gly::TextRendering::Init() {
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return false;
    }

    FT_Face face;
    if (FT_New_Face(ft, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return false;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture

        Character character = {
            face->glyph->bitmap.buffer,
            Point(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            Point(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };

        Characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return true;
}

void gly::TextRendering::RenderText(View& view, std::string const text, int x, int y, float scale)
{
    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        View resizeView(w,h,View::Gray8);
        SimdResizeBilinear(ch.Texture ,ch.Size.x, ch.Size.y, ch.Size.x ,resizeView.data, w, h, w,1);



        for (int sy = ypos, cy = 0; cy < h; sy++, cy++)
        {
            for (int sx = x, cx = 0; cx < w; sx++, cx++)
            {
                int index = sy*view.width*4+sx*4;
                int index2 = cy*w+cx;
                view.data[index] = ch.Texture[index2];
                view.data[index + 1] = ch.Texture[index2];
                view.data[index + 2] = ch.Texture[index2];
            }
        }

        x += w;
        /*
        for (int y = top ; y < bottom; ++y)
        {
            __declspec(align(16)) uint8_t byte[4];

            unit8_t* resultByte;
            unit8_t* srcByte = ch.Texture.data[w+]
            unit8_t* srcByteTop; = GET_BYTE(srcBitsTop, left, y, stride, bytepp);
            unit8_t* maskCurrent; = GET_GREY(maskSrc, left, y, width);
            for (int x = left; x < right; x += 4)
                {
                    //If you can't align, use _mm_loadu_si128()
                    // Step 1
                    __mm128i src = _mm_load_si128(reinterpret_cast<__mm128i*>(srcByte))
                    // Step 2
                    __mm128i srcTop = _mm_load_si128(reinterpret_cast<__mm128i*>(srcByteTop))

                    // Step 3
                    // Fill the 4 positions for the first pixel with maskCurrent[0], etc
                    // Could do better with shifts and so on, but this is clear
                    __mm128i mask = _mm_set_epi8(maskCurrent[0],maskCurrent[0],maskCurrent[0],maskCurrent[0],
                                                maskCurrent[1],maskCurrent[1],maskCurrent[1],maskCurrent[1],
                                                maskCurrent[2],maskCurrent[2],maskCurrent[2],maskCurrent[2],
                                                maskCurrent[3],maskCurrent[3],maskCurrent[3],maskCurrent[3],
                                                )

                    // step 4
                    __mm128i maskInv = _mm_subs_epu8(_mm_set1_epu8(255), mask)

                    //Todo : Multiply, with saturate - find correct instructions for 4..6
                    //note you can use Multiply and add _mm_madd_epi16

                    alpha = *maskCurrent;
                    red = (srcByteTop[R] * alpha + srcByte[R] * (255 - alpha)) / 255;
                    green = (srcByteTop[G] * alpha + srcByte[G] * (255 - alpha)) / 255;
                    blue = (srcByteTop[B] * alpha + srcByte[B] * (255 - alpha)) / 255;
                    CLAMPTOBYTE(red);
                    CLAMPTOBYTE(green);
                    CLAMPTOBYTE(blue);
                    resultByte[R] = red;
                    resultByte[G] = green;
                    resultByte[B] = blue;
                    //----

                    // Step 7 - store result.
                    //Store aligned if output is aligned on 16 byte boundrary
                    _mm_store_si128(reinterpret_cast<__mm128i*>(resultByte), result)
                    //Slow version if you can't guarantee alignment
                    //_mm_storeu_si128(reinterpret_cast<__mm128i*>(resultByte), result)

                    //Move pointers forward 4 places
                    srcByte += bytepp * 4;
                    srcByteTop += bytepp * 4;
                    resultByte += bytepp * 4;
                    maskCurrent += 4;
                }
            }
        */

        //x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
}
