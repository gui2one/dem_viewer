#include "OpenGLFrameBuffer.h"
// #include <glad/glad.h>

OpenGLFrameBuffer::OpenGLFrameBuffer()
{
    // printf("creating frameBuffer\n");
    invalidate(1000, 1000);
}

OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
    printf("delete frameBuffer\n");
    glDeleteFramebuffers(1, &m_id);
    glDeleteTextures(1, &m_colorAttachment);
    glDeleteTextures(1, &m_depthAttachment);
}

void OpenGLFrameBuffer::invalidate(uint32_t width, uint32_t height)
{

    m_width = width;
    m_height = height;
    if (m_id)
    {

        glDeleteFramebuffers(1, &m_id);
        glDeleteTextures(1, &m_colorAttachment);
        glDeleteTextures(1, &m_depthAttachment);

        m_colorAttachment = 0;
        m_depthAttachment = 0;

        // // printf("deleted frame buffer data\n");
    }

    if (width < 16)
        width = 16;
    if (height < 16)
        height = 16;

    glCreateFramebuffers(1, &m_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachment);
    glBindTexture(GL_TEXTURE_2D, m_colorAttachment);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachment);
    glBindTexture(GL_TEXTURE_2D, m_depthAttachment);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        // ORBITONS_ASSERT(false, "problem with frame buffer");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    glViewport(0, 0, m_width, m_height);
}
void OpenGLFrameBuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
