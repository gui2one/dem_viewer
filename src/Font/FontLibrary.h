#ifndef FONT_LIBRARY_H
#define FONT_LIBRARY_H
#include <pch.h>
#include <core.h>

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_BBOX_H

struct Point
{
    double x;
    double y;
};
class FontLibrary
{

public:
    FT_Library m_library;

    std::vector<Point> m_points;
    operator FT_Library() const;

public:
    FontLibrary();
    ~FontLibrary();

private:
    FontLibrary(const FontLibrary &);
    FontLibrary &operator=(const FontLibrary &);
};

class FontFace
{
public:
    FT_Face m_face;
    operator FT_Face() const;

public:
    FontFace(const FT_Library &library,
             const char *filename);

    ~FontFace()
    {
        FT_Done_Face(m_face);
    }

private:
    FontFace(const FontFace &);
    FontFace &operator=(const FontFace &);

private:
};
#endif /* FONT_LIBRARY_H */