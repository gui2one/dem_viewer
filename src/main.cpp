#include "Core/Application.h"
#include <stdio.h>
// #include <curl/curl.h>
#include "Core/Utils.h"
Application *app = Application::getInstance();

int main(int argc, char **argv)
{
    // Utils::refreshFileList();
    // std::vector<std::string> files = Utils::getFilesList();

    // int inc = 0;
    // for (auto file : files)
    // {
    //     std::cout << inc + 1 << "--" << file << "\n";

    //     inc++;
    // }
    app->run();
    return 0;
}
