cmake_minimum_required(VERSION 3.2)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(dem_viewer)

set(CMAKE_GENERATOR_PLATFORM x64)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "/MP /arch:AVX2 /EHsc")
# add_definitions(-DDEBUG)

file(GLOB_RECURSE src_files "src/*.rc" "src/*.cpp" "src/*.c" "src/*.h" "src/*.hpp")

add_executable( ${CMAKE_PROJECT_NAME} #SHARED

    ${src_files}


)

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}\\resources
        $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>\\resources
)

target_precompile_headers(${CMAKE_PROJECT_NAME}
    PUBLIC
        src/pch.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME}
	PUBLIC
		src/
		vendor/
		vendor/glad/include

)

#Python
include_directories(
    C:/Python38/include/
)
target_link_directories(${CMAKE_PROJECT_NAME} PUBLIC libs/)
target_link_libraries(${CMAKE_PROJECT_NAME} python3.lib)

# poly2tri
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC vendor/poly2tri/poly2tri)

add_library(
	poly2tri STATIC

	vendor/poly2tri/poly2tri/common/shapes.cc
    vendor/poly2tri/poly2tri/sweep/cdt.cc
    vendor/poly2tri/poly2tri/sweep/advancing_front.cc
    vendor/poly2tri/poly2tri/sweep/sweep_context.cc
    vendor/poly2tri/poly2tri/sweep/sweep.cc
)

target_link_libraries(${CMAKE_PROJECT_NAME} poly2tri ${POLY2TRI_LIBRARIES})

# FreeType
# set(SKIP_INSTALL_LIBRARIES 0)
# set(SKIP_INSTALL_ALL 0)
add_subdirectory(vendor/freetype)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC vendor/freetype/include)
target_link_libraries(${CMAKE_PROJECT_NAME} freetype ${FREETYPE_LIBRARIES})
export(TARGETS freetype  FILE Freetype.cmake)

# FTGL
option(BUILD_SHARED_LIBS OFF)
include_directories(
    vendor/freetype/include
)
set(Freetype_DIR "../../build/vendor/freetype/CMakeFiles/Export/lib/cmake/freetype")
set(CMAKE_PREFIX_PATH vendor/freetype/include)
add_subdirectory(vendor/ftgl)
target_include_directories(
    ${CMAKE_PROJECT_NAME} PRIVATE 
    vendor/ftgl/src
    vendor/ftgl/
)
target_link_libraries(${CMAKE_PROJECT_NAME} ftgl ${FTGL_LIBRARIES})

# Simple JSON
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC vendor/SimpleJSON)



# GLAD
add_subdirectory(vendor/glad)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC vendor/glad/include)
target_link_libraries(${CMAKE_PROJECT_NAME} glad ${GLAD_LIBRARIES})

#GLM
include_directories(vendor/glm)

# GLFW
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
add_subdirectory(vendor/glfw)

include_directories(vendor/glfw/include)
target_link_libraries(${CMAKE_PROJECT_NAME} glfw ${GLFW_LIBRARIES})


# # CURL
# option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
# add_subdirectory(vendor/curl)

# include_directories(vendor/curl/include)
# target_link_libraries(${CMAKE_PROJECT_NAME} libcurl ${LIBCURL_LIBRARIES})



#ImGUI
set(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
add_library(imgui STATIC
	vendor/imgui/backends/imgui_impl_opengl3.cpp
	vendor/imgui/backends/imgui_impl_glfw.cpp
	vendor/imgui/imgui.cpp
	vendor/imgui/imgui_demo.cpp
	vendor/imgui/imgui_draw.cpp
	vendor/imgui/imgui_widgets.cpp
	vendor/imgui/imgui_tables.cpp    
)
include_directories(vendor/imgui)
target_link_libraries(${CMAKE_PROJECT_NAME} imgui ${IMGUI_LIBRARIES})

