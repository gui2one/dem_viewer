#ifndef VERTEX_ARRAY_BUFFER_H
#define VERTEX_ARRAY_BUFFER_H

#include <pch.h>
#include <core.h>
#include "Core/OpenGLBuffer.h"
#include "Core/Mesh.h"

class OpenGLVertexArray
{
public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    void bind();
    void unbind();

    void addVertexBuffer(const Ref<OpenGLVertexBuffer> &vertexBuffer);
    void setIndexBuffer(const Ref<OpenGLIndexBuffer> &indexBuffer);

    uint32_t getID() { return m_id; };

private:
    uint32_t m_id;
    std::vector<Ref<OpenGLVertexBuffer>> m_vertexBuffers;
    Ref<OpenGLIndexBuffer> m_indexBuffer;
};

#endif /* VERTEX_ARRAY_BUFFER_H */