#ifndef UTILS_H
#define UTILS_H
#include <pch.h>
#include <core.h>

#include <stdio.h>
#include <json.hpp>

#include "Python/PythonHelper.h"
namespace Utils
{
    using json::JSON;

    struct Point
    {
        double x, y;
    };
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

    std::vector<std::string> getHGTFilesList()
    {

        std::string script_output;
        PythonHelper::runScrcript(RESOURCES_DIR "/python/list_hgt_files.py", script_output);

        JSON json = JSON::Load(script_output);

        // std::cout << json << std::endl;

        std::vector<std::string> paths;
        paths.reserve(json.length());

        for (size_t i = 0; i < json.length(); i++)
        {
            paths.emplace_back(json[i].ToString());
        }

        return paths;
    }

    static std::vector<std::string> getFilesList()
    {
        std::vector<std::string> result;

        std::ifstream inFile(RESOURCES_DIR "/python/hgt_files_list.txt");

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

    static float radians(float degrees)
    {
        return degrees / 360.0f * PI * 2.0;
    }
    static float degreeSizeAtLatitude(float latitude)
    {
        const float one_degree_at_equator = 111.319f;
        return one_degree_at_equator * cosf(radians(abs(latitude)));
    }

    static double lerp(double val1, double val2, double t)
    {

        return (val2 - val1) * t - val1;
    }

    static std::vector<Point> conicCurve(Point pt1, Point pt2, Point ctrl, int num_iter)
    {
        std::vector<Point> points;

        for (size_t i = 0; i < num_iter; i++)
        {
            double t = (double)i / (num_iter - 1);

            double x1 = lerp(pt1.x, ctrl.x, t);
            double y1 = lerp(pt1.y, ctrl.y, t);
            double x2 = lerp(ctrl.x, pt2.x, t);
            double y2 = lerp(ctrl.y, pt2.y, t);

            double x3 = lerp(x1, x2, t);
            double y3 = lerp(y1, y2, t);

            Point p = {x3, y3};
            points.push_back(p);
        }

        return points;
    }

    static std::vector<Point> cubicCurve(Point pt1, Point pt2, Point ctrl1, Point ctrl2, int num_iter)
    {
        std::vector<Point> points;
        for (size_t i = 0; i < num_iter; i++)
        {
            double t = (double)i / (num_iter - 1);

            double x1 = lerp(pt1.x, ctrl1.x, t);
            double y1 = lerp(pt1.y, ctrl1.y, t);
            double x2 = lerp(ctrl1.x, ctrl2.x, t);
            double y2 = lerp(ctrl1.y, ctrl2.y, t);
            double x3 = lerp(ctrl2.x, pt2.x, t);
            double y3 = lerp(ctrl2.x, pt2.y, t);

            double x11 = lerp(x1, x2, t);
            double y11 = lerp(y1, y2, t);

            double x22 = lerp(x2, x3, t);
            double y22 = lerp(y2, y3, t);

            double finalx = lerp(x11, x22, t);
            double finaly = lerp(y11, y22, t);

            Point p = {finalx, finaly};

            points.push_back(p);
        }
        return points;
    }
}

#endif /* UTILS_H */