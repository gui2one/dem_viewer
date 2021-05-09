#include "FontLibrary.h"

FontLibrary::FontLibrary()
{
    FT_Error error = FT_Init_FreeType(&m_library);

    if (error)
    {
        std::cout << "[freetype Init Error]" << std::endl;
    }
}

FontLibrary::~FontLibrary()
{

    FT_Done_FreeType(m_library);
    std::cout << "Delete FontLibrary" << std::endl;
}

FontLibrary::operator FT_Library() const
{
    return m_library;
}

/*
 FONT FACE
*/

FontFace::FontFace(const FT_Library &library,
                   const char *filename)
{
    // For simplicity, always use the first face index.
    FT_Error error = FT_New_Face(library, filename, 0, &m_face);

    if (error)
        std::cout << "[Font Face error]" << std::endl;
    else
        std::cout << "Loaded Face successfully" << std::endl;
}

FontFace::operator FT_Face() const
{
    return m_face;
}