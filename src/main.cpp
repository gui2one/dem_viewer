#include <pch.h>
#include "Core/Application.h"
#include <stdio.h>

#include "Core/Utils.h"
#include "Core/PlatformUtils.h"
#include "Python/PythonHelper.h"

// #include "Font/FontOutliner.h"
// #include "vendor/delaunator.hpp"
#include <Font/FontLibrary.h>

#include "poly2tri.h"

// #include <FTGL/FTPoint.h>

#include <FTGL/ftgl.h>

#include <FTVectoriser.h>

#include <json.hpp>
using json::JSON;
Application *app = Application::getInstance();

int main(int argc, char **argv)
{

    FontLibrary library;
    FontFace face(library, RESOURCES_DIR "/fonts/arial.ttf");

    FT_UInt index = FT_Get_Char_Index(face.m_face, 'A');
    FT_Error error = FT_Load_Glyph(face.m_face, index, FT_LOAD_NO_SCALE | FT_LOAD_NO_BITMAP);
    FT_GlyphSlot slot = face.m_face->glyph;

    JSON data;

    FTGLPolygonFont font(RESOURCES_DIR "/fonts/arial.ttf");

    // std::cout << data << std::endl;
    // std::cout << mesh->TesselationCount() << std::endl;
    // std::cout << mesh->Tesselation(0)->Point(0).Xf() << std::endl;

    // FontOutliner outliner(RESOURCES_DIR "/fonts/arial.ttf");
    // outliner.extractOutline("A");

    app->run();
    return 0;
}
