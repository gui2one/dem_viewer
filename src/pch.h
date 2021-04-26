#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include <vector>
#include <memory>

// windows stuff
#include <windows.h>
#undef near
#undef far
#include <commdlg.h>
#include "psapi.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

// glm
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#endif /* PCH_H */