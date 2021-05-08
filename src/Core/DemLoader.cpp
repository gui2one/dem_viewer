#include "DemLoader.h"

static void removeSRTMErrors(std::vector<short> &heights, int resolution = 1201)
{
    for (size_t i = 0; i < heights.size(); i++)
    {
        int x = i % resolution;
        int y = i / resolution;
        short cur_height = heights[i];
        if (cur_height == SHRT_MIN)
        {

            int n_samples = 0;
            short total = 0;
            // check neighbours height

            // LEFT
            if (x > 0)
            {
                if (heights[i - 1] != SHRT_MIN)
                {
                    total += heights[i - 1];
                    n_samples++;
                }
            }

            // TOP
            if (y > 0)
            {
                if (heights[i - resolution] != SHRT_MIN)
                {
                    total += heights[i - resolution];
                    n_samples++;
                }
            }

            // RIGHT
            if (x < resolution - 1)
            {
                if (heights[i + 1] != SHRT_MIN)
                {
                    total += heights[i + 1];
                    n_samples++;
                }
            }

            // BOTTOM
            if (y < resolution - 1)
            {
                if (heights[i + resolution] != SHRT_MIN)
                {
                    total += heights[i + resolution];
                    n_samples++;
                }
            }

            short avg = total / n_samples;

            heights[i] = avg;
        }
    }
}
std::vector<short> DemLoader::Load(std::string file_path)
{
    std::vector<short> heights;
    const int SRTM_SIZE = 1201;
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (!file)
    {
        std::cout << "Error opening file!" << std::endl;
        // return -1;
    }

    unsigned char buffer[2];
    for (int i = 0; i < SRTM_SIZE * SRTM_SIZE; i++)
    {

        if (!file.read(reinterpret_cast<char *>(buffer), sizeof(buffer)))
        {
            std::cout << "Error reading file!" << std::endl;
            // return -1;
        }

        short val = (buffer[0] << 8) | buffer[1];

        heights.push_back(val);
    }

    // smooth sampling errors
    removeSRTMErrors(heights);

    return heights;
}
