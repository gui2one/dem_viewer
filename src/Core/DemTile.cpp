#include "DemTile.h"

DemTile::DemTile(std::vector<short> heights)
    : m_heights(heights)
{

    m_texture = MakeRef<OpenGLTexture>();
    std::vector<unsigned char> pixels = toPixels();
    m_texture->setData(SRTM_SIZE, SRTM_SIZE, pixels.data());

    m_object = MakeRef<Dem3dObject>();
    m_object->buildVAO();
};