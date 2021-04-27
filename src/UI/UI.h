#ifndef UI_H
#define UI_H

#include <pch.h>
#include <core.h>
#include "Core/DemTile.h"
#include "Core/DemLoader.h"

#include "Core/PlatformUtils.h"

class UI
{
public:
    void ImGuiInit(GLFWwindow *window);

    void ImGuiBeginFrame();
    void ImGuiEndFrame();

    void drawMainMenu();

    Ref<DemTile> loadDemTile(std::string file_path);

    void drawTileList();
    void displayDemTile();

private:
    DemLoader m_loader;
    GLFWwindow *m_window;

    std::vector<Ref<DemTile>> m_demTiles;
    int s_selected_tile = -1;
};

#endif /* UI_H */