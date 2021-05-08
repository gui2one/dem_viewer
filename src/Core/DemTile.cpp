#include "DemTile.h"

DemTile::DemTile(std::vector<short> heights)
    : m_heights(heights)
{

    m_minHeight = *std::min_element(m_heights.begin(), m_heights.end());
    m_maxHeight = *std::max_element(m_heights.begin(), m_heights.end());
    m_texture = MakeRef<OpenGLTexture>();
    std::vector<unsigned char> pixels = toPixels();
    m_texture->setData(SRTM_SIZE, SRTM_SIZE, pixels.data());
};

std::vector<unsigned char> DemTile::toPixels()
{
    size_t numSamples = SRTM_SIZE * SRTM_SIZE;
    std::vector<unsigned char> pixels;
    pixels.reserve(numSamples * 4);

    float height_span = m_maxHeight - m_minHeight;
    std::cout << "height span --> " << height_span << std::endl;
    float ratio = height_span / SHRT_MAX;
    for (size_t i = 0; i < SRTM_SIZE * SRTM_SIZE; i++)
    {

        short h = m_heights[i] - m_minHeight;

        float f_value = ((float)h / ratio) / ((float)SHRT_MAX);

        unsigned char final_val = (unsigned char)((f_value * 256.0f));
        pixels.emplace_back(final_val);
        pixels.emplace_back(final_val);
        pixels.emplace_back(final_val);
        pixels.emplace_back(255); // alpha
    }

    return pixels;
}