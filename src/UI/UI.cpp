#include "UI.h"

static std::string getFileNameFromPath(std::string path)
{
    //string to be searched
    std::string mystr = "C:/gui2one/CODE/DEM_files/K11/N41W118.hgt";

    // regex expression for pattern to be searched
    // std::regex regexp("[^\\/]*\\.(\\w+)$");
    std::regex regexp("[^\\\\]*\\.(\\w+)$");

    // flag type for determining the matching behavior (in this case on string objects)
    std::smatch m;

    // regex_search that searches pattern regexp in the string mystr
    std::regex_search(path, m, regexp);

    // std::cout << "String that matches the pattern:" << std::endl;
    // for (auto x : m)
    //     std::cout << x << " ";

    return std::string(m[0]);
}

UI::UI()
{
    m_3dObject = MakeRef<Dem3dObject>();
    m_texture = MakeRef<OpenGLTexture>();
}

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
    const char *glsl_version = "#version 400";
    ImGui_ImplOpenGL3_Init(glsl_version);

    m_3dObject->init();

    ////////////
    // end imgui config
    ///////////

    m_frameBuffer = MakeRef<OpenGLFrameBuffer>();

    m_shader = MakeRef<OpenGLShader>();
    m_shader->loadVertexShaderSource(RESOURCES_DIR "/shaders/phong_shader.vert");
    m_shader->loadFragmentShaderSource(RESOURCES_DIR "/shaders/phong_shader.frag");
    m_shader->createShader();

    m_camera = MakeRef<Camera>(glm::radians(45.0f), 1.0f);

    m_controls.init(m_window, m_camera);
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

void UI::render(Timer &timer)
{
    // 'listen' to selection change
    if (s_old_selected_tile != s_selected_tile && s_selected_tile != -1)
    {
        std::cout << "[Selection Change]" << std::endl;
        s_old_selected_tile = s_selected_tile;

        auto cur_tile = m_demTiles[s_selected_tile];
        m_3dObject->buildVAO(cur_tile->m_heights);
        m_texture->setData(1201, 1201, cur_tile->toPixels().data());
    }

    m_controls.update(timer.getDeltaTime());
    ImGuiBeginFrame();

    drawMainMenu();
    if (m_displayAppOptions)
        drawAppOtions();
    drawTileList();

    displayDemTile();
    displayDemTile3D(timer.getDeltaTime());

    ImGuiEndFrame();
}

void UI::render3DView()
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    glm::vec3 lightPos(1.f, 1.f, 1.f);
    glm::vec3 up_vector(0.f, 1.f, 0.f);
    view *= glm::lookAt(
        m_camera->position,
        m_camera->target_position,
        glm::normalize(up_vector));
    m_frameBuffer->bind();

    glEnable(GL_DEPTH_TEST);
    glClearColor(.2f, .2f, .2f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto tile = m_demTiles[s_selected_tile];

    m_shader->useProgram();

    glUniform3fv(glGetUniformLocation(m_shader->getID(), "u_lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(m_shader->getID(), "u_cameraPos"), 1, glm::value_ptr(m_camera->position));

    glUniformMatrix4fv(glGetUniformLocation(m_shader->getID(), "u_model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(m_shader->getID(), "u_projection"), 1, GL_FALSE, glm::value_ptr(m_camera->projection));
    glUniformMatrix4fv(glGetUniformLocation(m_shader->getID(), "u_view"), 1, GL_FALSE, glm::value_ptr(view));

    // m_shader->useProgram();

    m_3dObject->draw();
    glUseProgram(0);
    m_frameBuffer->unbind();
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
                    loadFromFile(path.value());
                }
            }

            if (ImGui::MenuItem("Pick Folder"))
            {
                std::string path = PlatformUtils::PickFolder();

                if (!path.empty())
                {
                    std::cout << "Path  : " << path << std::endl;
                }
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Misc"))
        {
            if (ImGui::MenuItem("Options", NULL, &m_displayAppOptions))
            {
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

void UI::loadFromFile(std::string path)
{

    auto tile = loadDemTile(path);
    tile->setName(getFileNameFromPath(path).c_str());
    m_demTiles.push_back(tile);
}

void UI::loadFromFiles(std::vector<std::string> paths)
{
    for (auto path : paths)
    {
        loadFromFile(path);
    }

    s_selected_tile = m_demTiles.size() - 1;
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
                tile->setName(getFileNameFromPath(path.value()).c_str());
                m_demTiles.push_back(tile);
            }
        }

        ImGui::SetNextItemWidth(-1);
        ImGui::BeginListBox("##tiles");

        int inc = 0;
        for (auto tile : m_demTiles)
        {
            ImGui::PushID(inc);
            if (ImGui::Selectable(tile->m_file_name.c_str(), inc == s_selected_tile ? true : false))
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

            // auto cur_tile = m_demTiles[s_selected_tile];
            // m_texture->setData(1201, 1201, cur_tile->toPixels().data());
            ImGui::Image((void *)(intptr_t)m_texture->getID(), ImVec2(1201, 1201), ImVec2(0, 1), ImVec2(1, 0));
        }
    }
    ImGui::End();
    ImGui::PopStyleVar(1);
}

void UI::displayDemTile3D(float delta_time)
{
    ImGuiWindowFlags flags = 0;
    if (m_controls.activated)
        flags |= ImGuiWindowFlags_NoMove;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    ImGui::Begin("3D View", NULL, flags);

    if (m_demTiles.size() > 0)
    {
        if (s_selected_tile != -1)
        {
            ImVec2 avail_size = ImGui::GetContentRegionAvail();
            m_frameBuffer->invalidate(avail_size.x, avail_size.y);
            m_camera->setScreenRatio(avail_size.x / avail_size.y);
            render3DView();
            ImGui::Image((void *)(intptr_t)m_frameBuffer->getID(), avail_size, ImVec2(0, 1), ImVec2(1, 0));
            if (ImGui::IsItemHovered())
            {
                m_controls.activated = true;
            }
            else
            {
                m_controls.activated = false;
            }
        }
    }

    ImGui::End();
    ImGui::PopStyleVar(1);
}

void UI::drawAppOtions()
{

    if (ImGui::Begin("App Options", &m_displayAppOptions))
    {

        ImGui::Text("HGT Files Directory : ");
        if (!m_options.heightFilesDBPath.empty())
            ImGui::Text(m_options.heightFilesDBPath.c_str());
        else
            ImGui::Text("Not Set");

        if (ImGui::Button("Set"))
        {
            m_options.heightFilesDBPath = PlatformUtils::PickFolder();
        }
    }
}