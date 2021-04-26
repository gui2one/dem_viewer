#ifndef VERTEX_ARRAY_BUFFER_H
#define VERTEX_ARRAY_BUFFER_H

#include <pch.h>
#include "Core/OpenGLBuffer.h"
#include "Core/Mesh.h"

class OpenGLVertexArray
{
public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    void bind();
    void unbind();

    void addVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer> &vertexBuffer);
    void setIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer> &indexBuffer);

    uint32_t getID() { return m_id; };

private:
    uint32_t m_id;
    std::vector<std::shared_ptr<OpenGLVertexBuffer>> m_vertexBuffers;
    std::shared_ptr<OpenGLIndexBuffer> m_indexBuffer;
};

#endif /* VERTEX_ARRAY_BUFFER_H */