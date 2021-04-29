#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <pch.h>
#include <core.h>
namespace Utils
{
    static void refreshFileList()
    {
        std::cout << "[debug] refreshing list\n";
        std::string script = RESOURCES_DIR "/python/list_hgt_files.py";
        std::string command = "python ";

        command += script;
        FILE *in = _popen(command.c_str(), "r");

        // fscanf(in, "%s\n", ); // or some other method of reading

        _pclose(in);
        std::cout << "[debug] Done refreshing list\n";
    }

    static std::vector<std::string> getFilesList()
    {
        std::vector<std::string> result;

        std::ifstream inFile(RESOURCES_DIR "/python/files_list.txt");

        if (!inFile)
        {
            std::cerr << "problem with files list";
            exit(1);
        }

        std::string line;
        while (std::getline(inFile, line))
        {
            result.push_back(line);
            // std::cout << line;
        }
        std::cout << result.size() << " hgt files Found.\n";
        return result;
    }
}

#endif /* UTILS_H */