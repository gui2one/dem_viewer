#ifndef OPENGL_FRAME_BUFFER_H
#define OPENGL_FRAME_BUFFER_H

#include <pch.h>

class OpenGLFrameBuffer
{
public:
    OpenGLFrameBuffer();
    ~OpenGLFrameBuffer();

    void bind();
    void unbind();
    void invalidate(uint32_t width, uint32_t height);

    const uint32_t getWidth() const { return m_width; };
    const uint32_t getHeight() const { return m_height; };
    const uint32_t getID() const { return m_id; };

    void setWidth(uint32_t width) { m_width = width; };
    void setHeight(uint32_t height) { m_height = height; };

private:
    uint32_t m_id;
    uint32_t m_colorAttachment;
    uint32_t m_depthAttachment;

    uint32_t m_width;
    uint32_t m_height;
};

#endif /* OPENGL_FRAME_BUFFER_H */