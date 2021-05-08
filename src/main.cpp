// #include <pch.h>
#include "Core/Application.h"
#include <stdio.h>
#include <json.hpp>
// #include <curl/curl.h>
#include "Core/Utils.h"
#include "Core/PlatformUtils.h"
#include "Python/PythonHelper.h"

Application *app = Application::getInstance();
using json::JSON;
int main(int argc, char **argv)
{

    std::vector<std::string> paths = Utils::getHGTFilesList();

    std::cout << " num files : " << paths.size() << std::endl;
    app->run();
    return 0;
}
