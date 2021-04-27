#include "UI.h"

void UI::ImGuiInit(GLFWwindow *window)
{
    // init ImGui
    // Setup Dear ImGui context

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

    ImGui_ImplGlfw_InitForOpenGL(window, true);
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

void UI::displayDemTile(std::shared_ptr<DemTile> tile)
{
}