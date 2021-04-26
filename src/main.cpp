#include "pch.h"

#include "Core/DemLoader.h"

void ImGuiInit(GLFWwindow *window)
{
    // init ImGui
    // Setup Dear ImGui context

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // io.Fonts->AddFontFromFileTTF(ORBITONS_RES_DIR "/fonts/JetBrainsMono-Regular.ttf", 16);

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char *glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    ////////////
    // end imgui config
    ///////////
}
void ImGuiBeginFrame()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode /*|ImGuiDockNodeFlags_NoResize*/);
}
void ImGuiEndFrame()
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

const int SRTM_SIZE = 1201;
short height[SRTM_SIZE][SRTM_SIZE] = {0};
int main(int argc, char **argv)
{
    std::string dem_file = "C:/gui2one/CODE/DEM_files/F44/N20E078.hgt";
    if (argc < 2)
    {
        dem_file = "C:/gui2one/CODE/DEM_files/F44/N20E078.hgt";
    }
    else
    {
        dem_file = std::string(argv[1]);
    }
    // std::ifstream file(dem_file, std::ios::in | std::ios::binary);
    // if (!file)
    // {
    //     std::cout << "Error opening file!" << std::endl;
    //     return -1;
    // }

    // unsigned char buffer[2];
    // for (int i = 0; i < SRTM_SIZE; ++i)
    // {
    //     for (int j = 0; j < SRTM_SIZE; ++j)
    //     {
    //         if (!file.read(reinterpret_cast<char *>(buffer), sizeof(buffer)))
    //         {
    //             std::cout << "Error reading file!" << std::endl;
    //             return -1;
    //         }
    //         height[i][j] = (buffer[0] << 8) | buffer[1];
    //     }
    // }

    // //Read single value from file at row,col
    // const int row = 0;
    // const int col = 0;
    // size_t offset = sizeof(buffer) * ((row * SRTM_SIZE) + col);
    // file.seekg(offset, std::ios::beg);
    // file.read(reinterpret_cast<char *>(buffer), sizeof(buffer));
    // short single_value = (buffer[0] << 8) | buffer[1];
    // std::cout << "values at " << row << "," << col << ":" << std::endl;
    // std::cout << "  height array: " << height[row][col] << ", file: " << single_value << std::endl;

    // return 0;

    ///////////////////////////////
    ///////////////////////////////
    ///////////////////////////////
    ///////////////////////////////

    DemLoader loader;

    std::vector<short> heights = loader.Load(dem_file);
    std::shared_ptr<DemTile> tile = std::make_shared<DemTile>(heights);
    short corner_height = heights[0];
    std::cout << "Corner Height : " << corner_height << "\n";

    if (!glfwInit())
    {
        printf("problem with GLFW\n");
        return -1;
    }
    int count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "Starter Project", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowPos(window, 1920, 10);
    glfwMaximizeWindow(window);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    ImGuiInit(window);

    GLuint texture_id;
    glCreateTextures(GL_TEXTURE_2D, 1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    std::vector<unsigned char> pixels = tile->toPixels();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1201, 1201, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    glBindTexture(GL_TEXTURE_2D, 0);
    glViewport(0, 0, 640, 360);
    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(window))
    {
        ImGuiBeginFrame();

        glClearColor(.1f, .1f, .1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        static bool showDemoWindow = true;
        if (showDemoWindow)
        {
            ImGui::ShowDemoWindow(&showDemoWindow);
        }

        ImGui::Begin("Image");

        ImGui::Image((void *)(intptr_t)texture_id, ImVec2(1201, 1201), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
        ImGui::End();
        ImGuiEndFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    printf("GoodBye... \n");
    return 0;
}

// #include <iostream>
// #include <fstream>

// const int SRTM_SIZE = 1201;
// short height[SRTM_SIZE][SRTM_SIZE] = {0};

// int main(int argc, const char *argv[])
// {
//     std::ifstream file("N45W066.hgt", std::ios::in | std::ios::binary);
//     if (!file)
//     {
//         std::cout << "Error opening file!" << std::endl;
//         return -1;
//     }

//     unsigned char buffer[2];
//     for (int i = 0; i < SRTM_SIZE; ++i)
//     {
//         for (int j = 0; j < SRTM_SIZE; ++j)
//         {
//             if (!file.read(reinterpret_cast<char *>(buffer), sizeof(buffer)))
//             {
//                 std::cout << "Error reading file!" << std::endl;
//                 return -1;
//             }
//             height[i][j] = (buffer[0] << 8) | buffer[1];
//         }
//     }

//     //Read single value from file at row,col
//     const int row = 500;
//     const int col = 1000;
//     size_t offset = sizeof(buffer) * ((row * SRTM_SIZE) + col);
//     file.seekg(offset, std::ios::beg);
//     file.read(reinterpret_cast<char *>(buffer), sizeof(buffer));
//     short single_value = (buffer[0] << 8) | buffer[1];
//     std::cout << "values at " << row << "," << col << ":" << std::endl;
//     std::cout << "  height array: " << height[row][col] << ", file: " << single_value << std::endl;

//     return 0;
// }
