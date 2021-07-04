#include "FTFont.h"
#include <iostream>
#include "EngineGlobal.h"

FT_Library FTFont::ft = NULL;




FTFont::FTFont(const char* path,int size) {

    if (FT_New_Face(ft,path, 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
       // return -1;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, size);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 255; c++) {

        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        else {

            std::cout << "Loaded char " << c << std::endl;

        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));

    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    FT_Done_Face(face);

    draw = new IDraw(EngineGlobals::rWidth, EngineGlobals::rHeight);

    FXText = new FXTextDraw(EngineGlobals::rWidth,EngineGlobals::rHeight);

    std::cout << "Loaded font face succesfully.\n";
}

void FTFont::Draw(const char* text, float x, float y) {

    std::string txt = std::string(text);
    std::string::const_iterator c;
    float scale = 1.0f;

    draw->Begin();

    for (c = txt.begin(); c != txt.end(); c++)
    {

        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        Texture2D *tmp = new Texture2D(ch.TextureID);

        draw->DrawTex(xpos, ypos-h, w, h, tmp, 1, 1, 1, 1);
        x += (ch.Advance >> 6) * scale;
    }

    draw->End(FXText, true);

}

void FTFont::InitFontLib() {



    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
       // return -1;
        return;
    }
    std::cout << "Successfully initialized font lib.\n";
}