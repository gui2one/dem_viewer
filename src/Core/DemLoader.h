#ifndef DEM_LOADER_H
#define DEM_LOADER_H

#include <pch.h>

#include <iterator>
#include <algorithm>

#include <climits>
#include "DemTile.h"
/*

https://wiki.openstreetmap.org/wiki/SRTM

The HGT files have a very simple format. 
Each file is a series of 16-bit integers giving the height of each cell in meters arranged from west to east and then north to south. 
Each 3-arc-second data tile has 1442401 integers representing a 1201×1201 grid, 
while each 1-arc-second data tile has 12967201 integers representing a 3601×3601 grid. 
The outermost rows and columns of each tile overlap with the corresponding rows and columns of adjacent tiles.

*/

class DemLoader
{
public:
    DemLoader() = default;
    ~DemLoader() = default;

    std::vector<short> Load(std::string file_path);

private:
};
#endif /* DEM_LOADER_H */