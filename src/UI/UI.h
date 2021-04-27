#ifndef UI_H
#define UI_H

#include <pch.h>
#include <core.h>
#include "Core/DemTile.h"
class UI
{
public:
    void ImGuiInit(GLFWwindow *window);

    void ImGuiBeginFrame();
    void ImGuiEndFrame();

    void displayDemTile(std::shared_ptr<DemTile> tile);

private:
};
#endif /* UI_H */