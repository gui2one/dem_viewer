#include "Core/Application.h"
#include <stdio.h>
// #include <curl/curl.h>
#include "Core/Utils.h"
Application *app = Application::getInstance();

int main(int argc, char **argv)
{
    float radians = Utils::radians(180.0);
    float degree_size = Utils::degreeSizeAtLatitude(0.0f);
    std::cout << radians << " radians\n ";
    std::cout << degree_size << " degree_size\n ";
    app->run();
    return 0;
}
