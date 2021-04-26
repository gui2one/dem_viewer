
#include "Entity3d.h"

Entity3d::Entity3d() : m_name("default entity name"),
                       position(glm::vec3(0., 0.f, 0.f)),
                       rotation(glm::vec3(0., 0.f, 0.f)),
                       scale(glm::vec3(1., 1.f, 1.f)),
                       transforms(glm::mat4(1.f)),
                       m_parent(nullptr)
{
}

void Entity3d::applyTransforms()
{
    glm::mat4 matrix = glm::mat4(1.0f);

    if (m_parent != nullptr)
    {
        // TODO : apply parents matrices
    }
    // scale
    matrix = glm::scale(matrix, scale);

    // rotate
    matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
    matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
    matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));

    // translate
    matrix = glm::translate(matrix, position);
    transforms = matrix;
}

void Entity3d::setScale(glm::vec3 _scale)
{
    scale = _scale;
    applyTransforms();
}

void Entity3d::setPosition(glm::vec3 _pos)
{
    position = _pos;
    applyTransforms();
}

void Entity3d::setRotation(glm::vec3 _rot)
{
    rotation = _rot;
    applyTransforms();
}
