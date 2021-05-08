#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <memory>
#include <chrono>
#include <regex>

// windows stuff
#include <windows.h>
// #undef near
// #undef far
#include <commdlg.h>
#include "psapi.h"
#include <Shlobj.h>
#include <shobjidl.h>
#pragma comment(lib, "Shell32.lib")

#include <glad/glad.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

// glm
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

// #include <json.hpp>

#endif /* PCH_H */