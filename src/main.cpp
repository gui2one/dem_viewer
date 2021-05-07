#include "Core/Application.h"
#include <stdio.h>
#include <json.hpp>
// #include <curl/curl.h>
#include "Core/Utils.h"
#include "Core/PlatformUtils.h"
Application *app = Application::getInstance();
using json::JSON;
int main(int argc, char **argv)
{
    std::string json_source; // = "{ \"answer\" : 42}";
    std::ifstream inFile(RESOURCES_DIR "/python/data/test.json");
    if (inFile.is_open())
    {
        int length;
        inFile.seekg(0, std::ios::end); // go to the end
        length = inFile.tellg();        // report location (this is the length)
        inFile.seekg(0, std::ios::beg);

        length = inFile.tellg();
        std::string buffer;
        std::string line;
        while (inFile)
        {
            std::getline(inFile, line);
            buffer += line;
        }
        inFile.close();
        json_source = buffer;
        // std::cout << buffer << std::endl;
    }

    JSON json = JSON::Load(json_source);

    std::cout << json << std::endl;

    app->run();
    return 0;
}
