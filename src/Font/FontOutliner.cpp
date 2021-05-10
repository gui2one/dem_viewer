#include "FontOutliner.h"

FontOutliner::FontOutliner(const char *filename)
    : m_face(m_library, filename)
{
    std::cout << "[Outliner start]" << std::endl;
}

FontOutliner::~FontOutliner()
{
}

bool FontOutliner::extractOutline(const char *symbol)
{
    FT_ULong code = symbol[0];

    // For simplicity, use the charmap FreeType provides by default;
    // in most cases this means Unicode.
    FT_UInt index = FT_Get_Char_Index(m_face, code);
    FT_Error error = FT_Load_Glyph(m_face, index, FT_LOAD_NO_SCALE | FT_LOAD_NO_BITMAP);

    if (error)
        std::cout << "[freetype Error]" << std::endl;

    FT_Outline_Funcs callbacks;
    callbacks.move_to = MoveToFunction;
    callbacks.line_to = LineToFunction;
    callbacks.conic_to = ConicToFunction;
    callbacks.cubic_to = CubicToFunction;
    callbacks.shift = 0;
    callbacks.delta = 0;

    FT_Face face = m_face;
    FT_GlyphSlot slot = face->glyph;
    FT_Outline &outline = slot->outline;

    std::cout << "n_contours : " << outline.n_contours << std::endl;
    std::cout << "n_points : " << outline.n_points << std::endl;

    for (size_t i = 0; i < outline.n_points; i++)
    {
        const char c = outline.flags;
        // char c = 0b00000011;

        if (c & FT_OUTLINE_NONE)
        {

            std::cout << "Bit 0 on" << std::endl;
        }
        if (c & FT_OUTLINE_OWNER)
        {
            std::cout << "Bit 1 on" << std::endl;
        }
        if (c & FT_OUTLINE_EVEN_ODD_FILL)
        {
            std::cout << "FT_OUTLINE_EVEN_ODD_FILL" << std::endl;
        }
        if (c & FT_OUTLINE_REVERSE_FILL)
        {
            std::cout << "FT_OUTLINE_REVERSE_FILL" << std::endl;
        }
        if (c & FT_OUTLINE_IGNORE_DROPOUTS)
        {
            std::cout << "FT_OUTLINE_IGNORE_DROPOUTS" << std::endl;
        }
        if (c & FT_OUTLINE_HIGH_PRECISION)
        {
            std::cout << "FT_OUTLINE_HIGH_PRECISION" << std::endl;
        }
        if (c & FT_OUTLINE_SINGLE_PASS)
        {
            std::cout << "FT_OUTLINE_SINGLE_PASS" << std::endl;
        }
    }

    FT_BBox bbox;
    error = FT_Outline_Get_BBox(&outline, &bbox);

    if (error)
    {
        std::cout << "[Bbox error] " << std::endl;
        return false;
    }
    else
    {
        std::cout << "xMin : " << bbox.xMin;
        std::cout << " -- xMax : " << bbox.xMax;
        std::cout << " -- yMin : " << bbox.yMin;
        std::cout << " -- yMax : " << bbox.yMax << std::endl;
    }

    error = FT_Outline_Decompose(&outline, &callbacks, this);

    if (error)
    {
        std::cout << "[freetype outline error]" << std::endl;
        return false;
    }

    error = FT_Outline_Check(&outline);
    if (error)
    {
        std::cout << "Outline Check Error" << std::endl;
    }
    return true;
}

int FontOutliner::MoveToFunction(const FT_Vector *to,
                                 void *user)
{
    FontOutliner *self = static_cast<FontOutliner *>(user);
    printf("MoveTo %lf, %lf\n", (double)to->x, (double)to->y);

    Point p;
    p.x = to->x;
    p.y = to->y;

    self->m_points.push_back(p);
    return 0;
}

int FontOutliner::LineToFunction(const FT_Vector *to,
                                 void *user)
{
    printf("LineTo %lf, %lf\n", (double)to->x, (double)to->y);

    return 0;
}
int FontOutliner::ConicToFunction(const FT_Vector *control,
                                  const FT_Vector *to,
                                  void *user)
{
    printf("ConicTo %lf, %lf\n", (double)to->x, (double)to->y);
    std::cout << "\tControl " << control->x << " " << control->y << std::endl;

    return 0;
}
int FontOutliner::CubicToFunction(const FT_Vector *controlOne,
                                  const FT_Vector *controlTwo,
                                  const FT_Vector *to,
                                  void *user)
{
    std::cout << "CubicTo " << to->x << " " << to->y << std::endl;
    std::cout << "\tControl1 " << controlOne->x << " " << controlOne->y << std::endl;
    std::cout << "\tControl2 " << controlTwo->x << " " << controlTwo->y << std::endl;

    return 0;
}