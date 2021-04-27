#include <pch.h>
#include <core.h>

#include "Core/DemLoader.h"
#include "UI/UI.h"

#include "Core/OpenGLTexture.h"
#include "Core/PlatformUtils.h"

#include "Core/Mesh.h"
#include "Core/MeshUtils.h"
#include "Core/OpenGLBuffer.h"
#include "Core/OpenGLVertexArray.h"
#include "Core/OpenGLFrameBuffer.h"

#include "Core/Camera.h"
#include "Core/CameraControls.h"
#include "Core/OpenGLShader.h"
#include "Core/Timer.h"

Timer timer;

Ref<OpenGLVertexBuffer> vertexBuffer = nullptr;
Ref<OpenGLIndexBuffer> indexBuffer = nullptr;
Ref<OpenGLVertexArray> vertexArray = nullptr;

int num_elements;

Ref<Camera> camera;
CameraControls controls;

Ref<OpenGLShader> shader;

void buildMeshBuffers()
{

    Mesh mesh;
    mesh = MeshUtils::makeGrid(1.f, 1.f, 1201, 1201);
    MeshUtils::rotateX(mesh, -PI / 2.0f);
    MeshUtils::computeNormals(mesh);

    std::cout << glm::to_string(mesh.vertices[0].normal) << "\n";
    vertexBuffer.reset(new OpenGLVertexBuffer((float *)mesh.vertices.data(), mesh.vertices.size() * sizeof(Vertex)));
    // vertexBuffer->bind();

    BufferLayout layout = {
        {ShaderDataType::Float3, "position"},
        {ShaderDataType::Float3, "normal"},
        {ShaderDataType::Float2, "t_coords"}};

    vertexBuffer->setLayout(layout);

    vertexArray = MakeRef<OpenGLVertexArray>();
    vertexArray->addVertexBuffer(vertexBuffer);

    indexBuffer.reset(new OpenGLIndexBuffer(mesh.indices.data(), mesh.indices.size() * sizeof(int)));
    vertexArray->setIndexBuffer(indexBuffer);
    // m_indexBuffer->bind();

    num_elements = (int)mesh.indices.size();
}
int main(int argc, char **argv)
{

    UI ui;
    camera = MakeRef<Camera>(glm::radians(45.f), 1.0f);
    std::string dem_file;
    if (argc < 2)
    {
        dem_file = "C:/gui2one/CODE/DEM_files/K11/N41W118.hgt";
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

    glfwWindowHintString(GLFW_FOCUSED, GLFW_FALSE);
    glfwWindowHintString(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(1280, 720, "Starter Project", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset) {
        std::cout << yoffset << "\n";
    });
    glfwSetWindowPos(window, 100, 100);
    // glfwMaximizeWindow(window);

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    ui.ImGuiInit(window);

    Ref<OpenGLFrameBuffer> framebuffer = MakeRef<OpenGLFrameBuffer>();

    buildMeshBuffers();
    shader = MakeRef<OpenGLShader>();
    shader->loadVertexShaderSource(RESOURCES_DIR "/shaders/phong_shader.vert");
    shader->loadFragmentShaderSource(RESOURCES_DIR "/shaders/phong_shader.frag");
    shader->createShader();

    std::vector<unsigned char>
        pixels = tile->toPixels();

    OpenGLTexture texture;
    texture.bind(0);
    texture.setData(1201, 1201, pixels.data());

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1201, 1201, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    glBindTexture(GL_TEXTURE_2D, 0);
    glViewport(0, 0, 640, 360);
    glfwSwapInterval(1);

    controls.init(window, camera);

    glm::vec3 lightPos(1.f, 5.f, 0.f);
    glm::mat4 model(1.f);

    while (!glfwWindowShouldClose(window))
    {
        timer.update();
        // controls.setCamera(camera);
        controls.update(timer.getDeltaTime());

        glm::mat4 view = glm::mat4(1.0f);

        glm::vec3 up_vector(0.f, 1.f, 0.f);
        view *= glm::lookAt(
            camera->position,
            camera->target_position,
            glm::normalize(up_vector));

        framebuffer->bind();
        glClearColor(.0f, 0.9f, .1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->useProgram();

        glUniform3fv(glGetUniformLocation(shader->getID(), "u_lightPos"), 1, glm::value_ptr(lightPos));
        glUniform3fv(glGetUniformLocation(shader->getID(), "u_cameraPos"), 1, glm::value_ptr(camera->position));

        glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "u_model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "u_projection"), 1, GL_FALSE, glm::value_ptr(camera->projection));
        glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "u_view"), 1, GL_FALSE, glm::value_ptr(view));

        shader->useProgram();
        glBindVertexArray(vertexArray->getID());
        glDrawElements(GL_TRIANGLES, num_elements, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        framebuffer->unbind();
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

        ImGuiWindowFlags flags = 0;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("2D View");
        ImGui::Image((void *)(intptr_t)texture.getID(), ImVec2(1201, 1201), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();

        ImGui::Begin("3D View");
        ImGui::Image((void *)(intptr_t)framebuffer->getID(), ImVec2(512, 512), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();

        ImGui::PopStyleVar(1);
        ui.ImGuiEndFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    printf("Good Bye... \n");
    return 0;
}
