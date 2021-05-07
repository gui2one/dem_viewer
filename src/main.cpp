#include "Core/Application.h"
#include <stdio.h>

// #include <curl/curl.h>
#include "Core/Utils.h"
#include "Core/PlatformUtils.h"
Application *app = Application::getInstance();

int main(int argc, char **argv)
{

    app->run();
    return 0;
}
