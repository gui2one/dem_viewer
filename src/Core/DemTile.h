#ifndef DEM_TILE_H
#define DEM_TILE_H

#include <pch.h>
#include <core.h>
#include <climits>
#include <algorithm>

#include "Render/OpenGLTexture.h"
#include "Core/Dem3dObject.h"
class DemTile
{
public:
    const int SRTM_SIZE = 1201;
    std::vector<short> m_heights;
    Ref<OpenGLTexture> m_texture;

    std::string m_file_name;

    short m_minHeight;
    short m_maxHeight;

public:
    DemTile() = default;
    DemTile(std::vector<short> heights);

    ~DemTile() = default;

    std::vector<unsigned char> toPixels();

    void setName(const char *_name) { m_file_name = _name; }

private:
};
#endif /* DEM_TILE_H */