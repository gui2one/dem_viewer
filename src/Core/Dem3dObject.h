#ifndef DEM_3D_OBJECT_H
#define DEM_3D_OBJECT_H

#include <pch.h>
#include <core.h>
#include "Entity3d.h"

#include "Render/OpenGLBuffer.h"
#include "Render/OpenGLVertexArray.h"
class Dem3dObject : public Entity3d
{
public:
    Ref<OpenGLVertexBuffer> m_vertexBuffer;
    Ref<OpenGLIndexBuffer> m_indexBuffer;
    Ref<OpenGLVertexArray> m_vertexArray;

    unsigned int m_numElements;

public:
    Dem3dObject();

    void buildVAO(std::vector<short> heights);
    void draw();

private:
};
#endif /* DEM_3D_OBJECT_H */