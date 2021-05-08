#include "Dem3dObject.h"
#include "MeshUtils.h"
Dem3dObject::Dem3dObject()
{
    std::cout << "3d Object\n";

    m_mesh = MeshUtils::makeGrid(1.f, 1.f, 1201, 1201);
    MeshUtils::rotateX(m_mesh, -PI / 2.0f);

    std::cout << " num vertices " << m_mesh.vertices.size() << std::endl;
}
void Dem3dObject::init()
{
    m_vertexBuffer.reset(new OpenGLVertexBuffer((float *)m_mesh.vertices.data(), m_mesh.vertices.size() * sizeof(Vertex)));
    BufferLayout layout = {
        {ShaderDataType::Float3, "position"},
        {ShaderDataType::Float3, "normal"},
        {ShaderDataType::Float2, "t_coords"}};

    m_vertexBuffer->setLayout(layout);

    m_vertexArray.reset(new OpenGLVertexArray());
    m_vertexArray->addVertexBuffer(m_vertexBuffer);

    m_indexBuffer.reset(new OpenGLIndexBuffer(m_mesh.indices.data(), m_mesh.indices.size() * sizeof(int)));
    m_vertexArray->setIndexBuffer(m_indexBuffer);

    m_numElements = (int)m_mesh.indices.size();
}

void Dem3dObject::buildVAO(std::vector<short> heights)
{

    for (size_t i = 0; i < m_mesh.vertices.size(); i++)
    {
        Vertex &vertex = m_mesh.vertices[i];
        vertex.position.y = (float)heights[i] / (float)SHRT_MAX;
    }

    MeshUtils::computeNormals(m_mesh);

    m_vertexBuffer.reset(new OpenGLVertexBuffer((float *)m_mesh.vertices.data(), m_mesh.vertices.size() * sizeof(Vertex)));

    BufferLayout layout = {
        {ShaderDataType::Float3, "position"},
        {ShaderDataType::Float3, "normal"},
        {ShaderDataType::Float2, "t_coords"}};

    m_vertexBuffer->setLayout(layout);

    // m_vertexArray.reset(new OpenGLVertexArray());
    m_vertexArray->addVertexBuffer(m_vertexBuffer);

    // m_indexBuffer.reset(new OpenGLIndexBuffer(m_mesh.indices.data(), m_mesh.indices.size() * sizeof(int)));
    // m_vertexArray->setIndexBuffer(m_indexBuffer);

    // m_numElements = (int)m_mesh.indices.size();
}

void Dem3dObject::draw()
{
    glBindVertexArray(m_vertexArray->getID());
    glDrawElements(GL_TRIANGLES, m_numElements, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
