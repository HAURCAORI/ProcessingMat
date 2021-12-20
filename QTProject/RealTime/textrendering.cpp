#include "textrendering.h"

gly::TextRendering::TextRendering(){
    if(gly::TextRendering::Init()) {

    }
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
        View view(face->glyph->bitmap.width,face->glyph->bitmap.rows, View::Bgra32);
        view.data = face->glyph->bitmap.buffer;

        Character character = {
            view,
            Point(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            Point(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }

    return true;
}
