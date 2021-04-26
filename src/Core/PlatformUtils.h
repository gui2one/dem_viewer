#ifndef PLATFORM_UTILS_H
#define PLATFORM_UTILS_H

#include <Windows.h>
#include <optional>
#include "pch.h"

// #define GLFW_EXPOSE_NATIVE_WIN32
// #include <GLFW/glfw3.h>
// #include <GLFW/glfw3native.h>

class PlatformUtils
{
public:
    static std::optional<std::string> openFileialog(std::string file_path = "", const char *filter = "All\0 *.*\0Text\0 *.TXT\0")
    {
        OPENFILENAMEA ofn;
        char szFile[260];
        HWND hwnd = nullptr;
        HANDLE hf = nullptr;

        // Initialize OPENFILENAME
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = NULL;
        ofn.lpstrFile = (LPSTR)szFile;
        // Set lpstrFile[0] to '\0' so that GetOpenFileName does not
        // use the contents of szFile to initialize itself.
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        if (GetOpenFileNameA(&ofn) == TRUE)
        {
            return ofn.lpstrFile;
        };

        return std::nullopt;
    }

    static std::optional<std::string> saveFileDialog(const char *filter = "All\0 *.*\0Text\0 *.TXT\0")
    {
        OPENFILENAMEA ofn;
        char szFile[260];
        HWND hwnd = nullptr;
        HANDLE hf = nullptr;

        // Initialize OPENFILENAME
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = NULL;
        ofn.lpstrFile = (LPSTR)szFile;
        // Set lpstrFile[0] to '\0' so that GetOpenFileName does not
        // use the contents of szFile to initialize itself.
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

        if (GetSaveFileNameA(&ofn) == TRUE)
        {
            return ofn.lpstrFile;
        };

        return std::nullopt;
    }

    static size_t getMemoryUsage()
    {

        PROCESS_MEMORY_COUNTERS_EX pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc)) && pmc.cb >= sizeof(pmc))
        {
            size_t virtualMemUsedByMe = pmc.PrivateUsage;
            // printf("Memory used %d\n", virtualMemUsedByMe);
            return virtualMemUsedByMe;
            // use virtualMemUsedByMe here
        }

        return -1;
    }

private:
};

#endif /* PLATFORM_UTILS_H */