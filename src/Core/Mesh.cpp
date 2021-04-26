#include "Mesh.h"

void Mesh::print()
{
    printf("[Mesh] ...\n");

    for (auto &vert : vertices)
    {

        printf("\t%s\n", glm::to_string(vert.position).c_str());
    }
    printf("---------------------------------------\n");
}
