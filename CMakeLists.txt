cmake_minimum_required(VERSION 3.2)


set(project_name dem_viewer)
project(${project_name})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "/MP /arch:AVX2 /EHsc")
# add_definitions(-DDEBUG)

file(GLOB_RECURSE src_files "src/*.rc" "src/*.cpp" "src/*.c" "src/*.h")

add_executable( ${project_name} #SHARED

    ${src_files}
)

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}\\resources
        $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>\\resources
)

target_precompile_headers(${project_name}
    PUBLIC
        src/pch.cpp
)

target_include_directories(${project_name}
	PUBLIC
		src/
		vendor/
		vendor/glad/include

)
# GLAD
add_subdirectory(vendor/glad)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC vendor/glad/include)
target_link_libraries(${project_name} glad ${GLAD_LIBRARIES})

#GLM
include_directories(vendor/glm)

# GLFW
add_subdirectory(vendor/glfw)

include_directories(vendor/glfw/include)
target_link_libraries(${project_name} glfw ${GLFW_LIBRARIES})


# CURL
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
add_subdirectory(vendor/curl)

include_directories(vendor/curl/include)
target_link_libraries(${project_name} libcurl ${LIBCURL_LIBRARIES})



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
target_link_libraries(${project_name} imgui ${IMGUI_LIBRARIES})

