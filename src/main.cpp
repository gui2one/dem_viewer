#include "pch.h"
#include <core.h>

#include "Core/DemLoader.h"
#include "UI/UI.h"

#include "Core/OpenGLTexture.h"
#include "Core/PlatformUtils.h"

#include "Core/Mesh.h"
#include "Core/OpenGLFrameBuffer.h"

const int SRTM_SIZE = 1201;
short height[SRTM_SIZE][SRTM_SIZE] = {0};
int main(int argc, char **argv)
{

    UI ui;
    std::string dem_file = "C:/gui2one/CODE/DEM_files/F44/N20E078.hgt";
    if (argc < 2)
    {
        dem_file = "C:/gui2one/CODE/DEM_files/F44/N20E078.hgt";
    }
    else
    {
        dem_file = std::string(argv[1]);
    }

    DemLoader loader;

    std::vector<short> heights = loader.Load(dem_file);
    Ref<DemTile> tile = MakeRef<DemTile>(heights);
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

    glfwSetWindowPos(window, 100, 100);
    // glfwMaximizeWindow(window);

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    ui.ImGuiInit(window);

    Ref<OpenGLFrameBuffer> frame_buffer = MakeRef<OpenGLFrameBuffer>();
    std::vector<unsigned char> pixels = tile->toPixels();

    OpenGLTexture texture;
    texture.bind(0);
    texture.setData(1201, 1201, pixels.data());

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1201, 1201, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    glBindTexture(GL_TEXTURE_2D, 0);
    glViewport(0, 0, 640, 360);
    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(window))
    {
        ui.ImGuiBeginFrame();

        glClearColor(.1f, .1f, .1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (ImGui::BeginMainMenuBar())
        {

            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open ..."))
                {
                    std::optional<std::string> path = PlatformUtils::openFileialog("C:\\gui2one\\CODE", "HGT\0 *.hgt\0");

                    if (path)
                    {
                        std::cout << "Open File : " << path.value() << "\n";
                        auto heights = loader.Load(path.value());

                        tile = std::make_shared<DemTile>(heights);
                        pixels = tile->toPixels();

                        texture.setData(1201, 1201, pixels.data());
                    }
                }

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        static bool showDemoWindow = true;
        if (showDemoWindow)
        {
            ImGui::ShowDemoWindow(&showDemoWindow);
        }

        ImGui::Begin("Image");

        ImGui::Image((void *)(intptr_t)texture.getID(), ImVec2(1201, 1201), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
        ImGui::End();
        ui.ImGuiEndFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    printf("Good Bye... \n");
    return 0;
}
