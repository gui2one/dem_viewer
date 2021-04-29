#ifndef DEM_TILE_H
#define DEM_TILE_H

#include <pch.h>
#include <core.h>
#include <climits>
#include <algorithm>

#include "Core/OpenGLTexture.h"
#include "Core/Dem3dObject.h"
class DemTile
{
public:
    const int SRTM_SIZE = 1201;
    std::vector<short> m_heights;
    Ref<OpenGLTexture> m_texture;

    std::string m_file_name;

    Ref<Dem3dObject> m_object;

public:
    DemTile() = default;
    DemTile(std::vector<short> heights);

    ~DemTile() = default;

    std::vector<unsigned char> toPixels()
    {
        size_t numSamples = SRTM_SIZE * SRTM_SIZE;
        std::vector<unsigned char> pixels;
        pixels.reserve(numSamples * 4);

        short min, max;

        min = SHRT_MAX;
        max = SHRT_MIN;
        for (size_t i = 0; i < SRTM_SIZE * SRTM_SIZE; i++)
        {

            short sample = m_heights[i];
            if (sample != SHRT_MIN && sample < min)
            {
                min = sample;
            }
            if (sample < SHRT_MAX && sample > max)
            {
                max = sample;
            }
        }

        std::cout << "Min Height = " << min << "\n";
        std::cout << "Max Height = " << max << "\n";
        for (size_t i = 0; i < SRTM_SIZE * SRTM_SIZE; i++)
        {

            short h = m_heights[i];
            float mult = (float)(max - min) / (float)SHRT_MAX;
            float f_value = (h) / ((float)SHRT_MAX);

            // unsigned char final_val = (unsigned char)(((f_value)*255.0f) / mult);
            unsigned char final_val = (unsigned char)((f_value * 256.0f));
            pixels.emplace_back(final_val);
            pixels.emplace_back(final_val);
            pixels.emplace_back(final_val);
            pixels.emplace_back(255);

            // if (i < 50)
            //     std::cout << " Color level : " << (int)final_val << " -- height : " << m_heights[i] << "\n";
        }

        // std::cout << "num Pixels : " << pixels.size() / 4 << "\n";
        // std::cout << "    Corner Pixel : " << (int)pixels[0] << "\n";

        return pixels;
    }

    void setName(const char *_name) { m_file_name = _name; }

private:
};
#endif /* DEM_TILE_H */