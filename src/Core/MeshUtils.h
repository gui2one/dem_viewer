#ifndef MESH_UTILS_H
#define MESH_UTILS_H

#include "../pch.h"

#include "Mesh.h"

namespace MeshUtils
{

    // generators
    Mesh makeTriangle();
    Mesh makeQuad();
    Mesh makeGrid(float width, float length, int cols, int rows);

    // modificators
    void rotateX(Mesh &mesh, float radians);
    void rotateY(Mesh &mesh, float radians);
    void rotateZ(Mesh &mesh, float radians);

    void computeNormals(Mesh &mesh, bool invert = false);
};

#endif /* MESH_UTILS_H */