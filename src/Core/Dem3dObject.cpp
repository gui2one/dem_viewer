#include "Dem3dObject.h"
#include "MeshUtils.h"
Dem3dObject::Dem3dObject()
{
    std::cout << "3d Object\n";
}

void Dem3dObject::buildVAO()
{
    Mesh mesh;
    mesh = MeshUtils::makeGrid(1.f, 1.f, 1201, 1201);
    MeshUtils::rotateX(mesh, -PI / 2.0f);
    MeshUtils::computeNormals(mesh);

    std::cout << glm::to_string(mesh.vertices[0].normal) << "\n";
    m_vertexBuffer.reset(new OpenGLVertexBuffer((float *)mesh.vertices.data(), mesh.vertices.size() * sizeof(Vertex)));
    // m_vertexBuffer->bind();

    BufferLayout layout = {
        {ShaderDataType::Float3, "position"},
        {ShaderDataType::Float3, "normal"},
        {ShaderDataType::Float2, "t_coords"}};

    m_vertexBuffer->setLayout(layout);

    m_vertexArray = MakeRef<OpenGLVertexArray>();
    m_vertexArray->addVertexBuffer(m_vertexBuffer);

    m_indexBuffer.reset(new OpenGLIndexBuffer(mesh.indices.data(), mesh.indices.size() * sizeof(int)));
    m_vertexArray->setIndexBuffer(m_indexBuffer);
    // m_indexBuffer->bind();

    m_numElements = (int)mesh.indices.size();
}

void Dem3dObject::draw()
{
    glBindVertexArray(m_vertexArray->getID());
    glDrawElements(GL_TRIANGLES, m_numElements, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
