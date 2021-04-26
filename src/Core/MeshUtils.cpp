#include "MeshUtils.h"

namespace MeshUtils
{

    Mesh makeTriangle()
    {
        Mesh mesh;
        std::vector<Vertex> verts;

        verts.push_back(Vertex{glm::vec3(0.0f, 0.0f, 0.0f)});
        verts.push_back(Vertex{glm::vec3(1.0f, 0.0f, 0.0f)});
        verts.push_back(Vertex{glm::vec3(0.0f, 1.0f, 0.0f)});

        std::vector<unsigned int> indices{0, 1, 2};
        mesh.vertices = verts;
        mesh.indices = indices;
        computeNormals(mesh);
        return mesh;
    }

    Mesh makeQuad()
    {
        Mesh mesh;
        std::vector<Vertex> verts;

        verts.push_back(Vertex{glm::vec3(-1.0f, -1.0f, 0.0f)});
        verts.push_back(Vertex{glm::vec3(1.0f, -1.0f, 0.0f)});
        verts.push_back(Vertex{glm::vec3(-1.0f, 1.0f, 0.0f)});

        verts.push_back(Vertex{glm::vec3(-1.0f, 1.0f, 0.0f)});
        verts.push_back(Vertex{glm::vec3(1.0f, 1.0f, 0.0f)});
        verts.push_back(Vertex{glm::vec3(1.0f, -1.0f, 0.0f)});

        std::vector<unsigned int> indices{0, 1, 2, 3, 5, 4};
        mesh.vertices = verts;
        mesh.indices = indices;

        computeNormals(mesh);
        return mesh;
    }

    Mesh makeGrid(float width, float length, int cols, int rows)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        Mesh mesh;

        for (int y = 0; y < rows; y++)
        {
            for (int x = 0; x < cols; x++)
            {
                Vertex vert;
                float posx = 1.0 / (cols - 1) * x;
                float posy = 1.0 / (rows - 1) * y;

                vert.position.x = (posx - 0.5) * width;
                vert.position.y = (posy - 0.5) * length;
                vert.position.z = 0.0;

                vert.t_coords.x = posx;
                vert.t_coords.y = posy;

                vert.normal.x = 0.0;
                vert.normal.y = 0.0;
                vert.normal.z = 1.0;

                vertices.push_back(vert);
            }
        }

        for (unsigned int y = 0; y < rows - 1; y++)
        {
            for (unsigned int x = 0; x < cols - 1; x++)
            {
                unsigned int curIndex = x + y * cols;
                indices.push_back(curIndex);
                indices.push_back(curIndex + cols + 1);
                indices.push_back(curIndex + cols);

                indices.push_back(curIndex + cols + 1);
                indices.push_back(curIndex);
                indices.push_back(curIndex + 1);
            }
        }

        mesh.vertices = vertices;
        mesh.indices = indices;

        computeNormals(mesh);
        return mesh;
    }

    // Modificators
    void rotateX(Mesh &mesh, float radians)
    {

        glm::mat4 matrix(1.0f);
        matrix = glm::rotate(matrix, radians, glm::vec3(1.f, 0.f, 0.f));
        for (size_t i = 0; i < mesh.vertices.size(); i++)
        {
            mesh.vertices[i].position = matrix * glm::vec4(mesh.vertices[i].position, 1.0f);
        }
    }

    void rotateY(Mesh &mesh, float radians)
    {

        glm::mat4 matrix;
        matrix = glm::rotate(matrix, radians, glm::vec3(0.f, 1.f, 0.f));
        for (size_t i = 0; i < mesh.vertices.size(); i++)
        {
            mesh.vertices[i].position = matrix * glm::vec4(mesh.vertices[i].position, 1.0f);
        }
    }

    void rotateZ(Mesh &mesh, float radians)
    {

        glm::mat4 matrix;
        matrix = glm::rotate(matrix, radians, glm::vec3(0.f, 0.f, 1.f));
        for (size_t i = 0; i < mesh.vertices.size(); i++)
        {
            mesh.vertices[i].position = matrix * glm::vec4(mesh.vertices[i].position, 1.0f);
        }
    }

    void computeNormals(Mesh &mesh, bool invert)
    {

        std::vector<int> checked_indices;

        std::vector<int> num_normals(mesh.vertices.size());
        for (int i = 0; i < num_normals.size(); i++)
        {
            num_normals[i] = 0;
        }

        std::vector<glm::vec3> temp_normals(mesh.vertices.size());
        for (int i = 0; i < temp_normals.size(); i++)
        {
            temp_normals[i] = glm::vec3(0.0f, 0.0f, 0.0f);
        }
        // compute normals

        for (int i = 0; i < mesh.indices.size(); i++)
        {
            glm::vec3 AB;
            glm::vec3 AC;

            if ((i % 3) == 0)
            {
                AB = mesh.vertices[mesh.indices[i + 1]].position - mesh.vertices[mesh.indices[i]].position;
                AC = mesh.vertices[mesh.indices[i + 2]].position - mesh.vertices[mesh.indices[i]].position;
            }
            else if ((i % 3) == 1)
            {
                AB = mesh.vertices[mesh.indices[i + 1]].position - mesh.vertices[mesh.indices[i]].position;
                AC = mesh.vertices[mesh.indices[i - 1]].position - mesh.vertices[mesh.indices[i]].position;
            }
            else if ((i % 3) == 2)
            {
                AB = mesh.vertices[mesh.indices[i - 2]].position - mesh.vertices[mesh.indices[i]].position;
                AC = mesh.vertices[mesh.indices[i - 1]].position - mesh.vertices[mesh.indices[i]].position;
            }

            num_normals[mesh.indices[i]] += 1;

            glm::vec3 n_normal = glm::cross(glm::normalize(AB), glm::normalize(AC));

            temp_normals[mesh.indices[i]] += n_normal;
        }

        for (int i = 0; i < mesh.vertices.size(); i++)
        {
            if (invert == false)
                mesh.vertices[i].normal = glm::normalize(temp_normals[i]);
            else
                mesh.vertices[i].normal = glm::normalize(temp_normals[i]) * -1.0f;
        }

        // return mesh;
    }
}; /* end namespace MeshUtils */