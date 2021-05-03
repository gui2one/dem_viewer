#ifndef UI_H
#define UI_H

#include <pch.h>
#include <core.h>

#include "Core/DemTile.h"
#include "Core/DemLoader.h"
#include "Core/Timer.h"

#include "Core/OpenGLFrameBuffer.h"
#include "Core/OpenGLShader.h"

#include "Core/Camera.h"
#include "Core/CameraControls.h"

#include "Core/PlatformUtils.h"

class UI
{

public:
    CameraControls m_controls;

public:
    void ImGuiInit(GLFWwindow *window);

    void ImGuiBeginFrame();
    void ImGuiEndFrame();

    void render(Timer &timer);
    void render3DView();
    void drawMainMenu();

    Ref<DemTile> loadDemTile(std::string file_path);
    void loadFromFile(std::string path);
    void loadFromFiles(std::vector<std::string> paths);

    void drawTileList();
    void displayDemTile();
    void displayDemTile3D(float delta_time);

private:
    DemLoader m_loader;
    GLFWwindow *m_window;

    Ref<OpenGLFrameBuffer> m_frameBuffer;
    std::vector<Ref<DemTile>> m_demTiles;
    int s_selected_tile = -1;

    Ref<OpenGLShader> m_shader;
    Ref<Camera> m_camera;
};

#endif /* UI_H */