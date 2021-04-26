#ifndef MESH_H
#define MESH_H

#include <pch.h>

struct Vertex
{
    glm::vec3 position = glm::vec3(1.0f);
    glm::vec3 normal = glm::vec3(1.0f);
    glm::vec2 t_coords = glm::vec2(1.0f);
};
class Mesh
{
public:
    void print();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

private:
};

#endif /* MESH_H */