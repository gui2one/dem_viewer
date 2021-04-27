#include "UI.h"

void UI::ImGuiInit(GLFWwindow *window)
{
    // init ImGui
    // Setup Dear ImGui context

    m_window = window;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.Fonts->AddFontFromFileTTF(RESOURCES_DIR "/fonts/JetBrainsMono-Regular.ttf", 16);

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = false;
    // io.ConfigViewportsNoDecoration = true;
    // io.ConfigViewportsNoDefaultParent = false;

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    const char *glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    ////////////
    // end imgui config
    ///////////
}

void UI::ImGuiBeginFrame()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowClass windowClass;

    windowClass.ViewportFlagsOverrideSet = ImGuiWindowFlags_NoBringToFrontOnFocus;
    ImGui::SetNextWindowClass(&windowClass);
    ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode /*|ImGuiDockNodeFlags_NoResize*/);
}

void UI::ImGuiEndFrame()
{

    // Rendering
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGui::EndFrame();

    ImGuiIO &io = ImGui::GetIO();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();

        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        glfwMakeContextCurrent(backup_current_context);
    }
}

void UI::drawMainMenu()
{
    if (ImGui::BeginMainMenuBar())
    {

        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open ..."))
            {
                std::optional<std::string> path = PlatformUtils::openFileialog("C:\\gui2one\\CODE", "HGT\0 *.hgt\0");

                if (path)
                {
                    // m_window->m_
                    loadDemTile(path.value());
                }
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

Ref<DemTile> UI::loadDemTile(std::string file_path)
{

    Ref<DemTile> tile = MakeRef<DemTile>(m_loader.Load(file_path));
    return tile;
}

void UI::drawTileList()
{

    if (ImGui::Begin("DEM Tiles"))
    {
        if (ImGui::Button("Add"))
        {
            std::optional<std::string> path = PlatformUtils::openFileialog("C:\\gui2one\\CODE", "HGT\0 *.hgt\0");

            if (path)
            {
                // m_window->m_
                auto tile = loadDemTile(path.value());
                m_demTiles.push_back(tile);
            }
        }

        ImGui::BeginListBox("##tiles");

        int inc = 0;
        for (auto tile : m_demTiles)
        {
            ImGui::PushID(inc);
            if (ImGui::Selectable("azeez", inc == s_selected_tile ? true : false))
            {
                s_selected_tile = inc;
                std::cout << s_selected_tile << "\n";
            }

            inc++;
            ImGui::PopID();
        }
        if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
        {
            s_selected_tile = -1;
        }
        ImGui::EndListBox();
    }
}
void UI::displayDemTile()
{
    ImGuiWindowFlags flags = 0;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("2D View");
    if (m_demTiles.size() > 0)
    {
        if (s_selected_tile != -1)
        {

            auto cur_tile = m_demTiles[s_selected_tile];
            ImGui::Image((void *)(intptr_t)cur_tile->m_texture->getID(), ImVec2(1201, 1201), ImVec2(0, 1), ImVec2(1, 0));
        }
    }
    ImGui::End();
    ImGui::PopStyleVar(1);
}