#include "OpenGLVertexArray.h"
// #include <glad/glad.h>

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {
    case ShaderDataType::Float:
        return GL_FLOAT;
    case ShaderDataType::Float2:
        return GL_FLOAT;
    case ShaderDataType::Float3:
        return GL_FLOAT;
    case ShaderDataType::Float4:
        return GL_FLOAT;
    case ShaderDataType::Mat3:
        return GL_FLOAT;
    case ShaderDataType::Mat4:
        return GL_FLOAT;
    case ShaderDataType::Int:
        return GL_INT;
    case ShaderDataType::Int2:
        return GL_INT;
    case ShaderDataType::Int3:
        return GL_INT;
    case ShaderDataType::Int4:
        return GL_INT;
    case ShaderDataType::Bool:
        return GL_BOOL;
    }

    return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
{
    glCreateVertexArrays(1, &m_id);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    // printf("deleting VertexBuffer \n");
    glDeleteVertexArrays(1, &m_id);
}
void OpenGLVertexArray::bind()
{
    glBindVertexArray(m_id);
}
void OpenGLVertexArray::unbind()
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer> &vertexBuffer)
{
    int inc = 0;

    glBindVertexArray(m_id);

    for (const auto &element : vertexBuffer->getLayout().getElements())
    {
        // printf("  - name : %s\n", element.Name.c_str());

        glEnableVertexAttribArray(inc);
        glVertexAttribPointer(
            inc /*index*/,
            element.getNumComponents() /*size*/,
            ShaderDataTypeToOpenGLBaseType(element.Type), /* enum type*/ //TODO !!!!!!
            GL_FALSE, /* normalized */                                   //TODO !!!!!!
            sizeof(Vertex),                                              /* stride  ??? */
            (void *)element.Offset                                       /* offset ptr*/

        );

        inc++;
    }
}

void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer> &indexBuffer)
{
    m_indexBuffer = indexBuffer;
}
