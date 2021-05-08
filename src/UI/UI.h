#ifndef UI_H
#define UI_H

#include <pch.h>
#include <core.h>

#include "Core/DemTile.h"
#include "Core/DemLoader.h"
#include "Core/Timer.h"

#include "Render/OpenGLFrameBuffer.h"
#include "Render/OpenGLShader.h"

#include "Core/Camera.h"
#include "Core/CameraControls.h"

#include "Core/PlatformUtils.h"
#include "TileMapViewer/TileMapViewer.h"
#include "Core/Dem3dObject.h"
struct AppOptions
{
    std::string heightFilesDBPath;
    std::string tileTexturesPath;
};

class UI
{

public:
    CameraControls m_controls;
    TileMapViewer m_tileMapViewer;
    Ref<Dem3dObject> m_3dObject;
    AppOptions m_options;
    bool m_displayAppOptions = true;

public:
    UI();
    ~UI() = default;
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

    void drawAppOtions();

private:
    DemLoader m_loader;
    GLFWwindow *m_window;

    Ref<OpenGLFrameBuffer> m_frameBuffer;
    std::vector<Ref<DemTile>> m_demTiles;

    inline static int s_selected_tile = -1;
    inline static int s_old_selected_tile = -1;

    Ref<OpenGLShader> m_shader;
    Ref<Camera> m_camera;
};

#endif /* UI_H */