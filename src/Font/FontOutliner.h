#ifndef FONT_OUTLINER_H
#define FONT_OUTLINER_H

#include "FontLibrary.h"
class FontOutliner
{

public:
    std::vector<Point> m_points;

public:
    FontOutliner(const char *filename);
    ~FontOutliner();

    bool extractOutline(const char *symbol);

    static int MoveToFunction(const FT_Vector *to, void *user);
    static int LineToFunction(const FT_Vector *to, void *user);
    static int ConicToFunction(const FT_Vector *control, const FT_Vector *to, void *user);
    static int CubicToFunction(const FT_Vector *controlOne, const FT_Vector *controlTwo, const FT_Vector *to, void *user);

private:
    FontLibrary m_library;
    FontFace m_face;
};
#endif /* FONT_OUTLINER_H */