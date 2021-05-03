#include "OpenGLBuffer.h"
// #include <glad/glad.h>

//////////////////////////////////////////////////////
//////   OpenGLVertexBuffer
//////////////////////////////////////////////////////

OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size)
{
    // if (m_id)
    // {
    //     glBindBuffer(GL_ARRAY_BUFFER, 0);
    //     glDeleteBuffers(1, &m_id);
    // }
    glCreateBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
    // printf("[GL LOG] -- created Vertex Buffer\n");
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    // printf("[DEBUG] delete vertex buffer\n");
    glDeleteBuffers(1, &m_id);
}
void OpenGLVertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void OpenGLVertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//////////////////////////////////////////////////////
//////    OpenGLIndexBuffer
//////////////////////////////////////////////////////

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t size)
{

    // if (m_id)
    // {
    //     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //     glDeleteBuffers(1, &m_id);
    // }
    glCreateBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_DYNAMIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    // printf("[DEBUG] delete Index buffer\n");
    glDeleteBuffers(1, &m_id);
}
void OpenGLIndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void OpenGLIndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
