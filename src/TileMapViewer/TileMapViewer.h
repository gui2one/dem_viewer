#ifndef TILE_MAP_VIEWER_H
#define TILE_MAP_VIEWER_H

#include <pch.h>
#include "Render/OpenGLBuffer.h"
#include "Render/OpenGLTexture.h"
class TileMapViewer
{
public:
    std::string m_folderPath;
    std::vector<std::unordered_map<int, OpenGLTexture>> m_tileTextures;

public:
    TileMapViewer();

private:
};
#endif /* TILE_MAP_VIEWER_H */