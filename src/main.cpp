// #include <pch.h>
#include "Core/Application.h"
#include <stdio.h>
#include <json.hpp>
// #include <curl/curl.h>
#include "Core/Utils.h"
#include "Core/PlatformUtils.h"
#include "Python/PythonHelper.h"

#include "poly2tri.h"
#include "ft2build.h"
Application *app = Application::getInstance();
using json::JSON;
int main(int argc, char **argv)
{

    std::vector<p2t::Point *> points;
    p2t::Point *pt = new p2t::Point(0.0, 0.0);
    points.push_back(pt);
    points.push_back(new p2t::Point(1.0, 0.0));
    points.push_back(new p2t::Point(1.0, 1.0));
    points.push_back(new p2t::Point(0.0, 1.0));

    p2t::CDT cdt = p2t::CDT(points);

    cdt.Triangulate();
    std::vector<p2t::Triangle *> triangles = cdt.GetTriangles();

    for (size_t i = 0; i < triangles.size(); i++)
    {
        p2t::Triangle *cur_tri = triangles[i];
        std::cout << "Triangle " << i << " :" << std::endl;
        std::cout << "\t X : " << cur_tri->GetPoint(0)->x << " -- Y : " << cur_tri->GetPoint(0)->y << std::endl;
        std::cout << "\t X : " << cur_tri->GetPoint(1)->x << " -- Y : " << cur_tri->GetPoint(1)->y << std::endl;
        std::cout << "\t X : " << cur_tri->GetPoint(2)->x << " -- Y : " << cur_tri->GetPoint(2)->y << std::endl;
    }
    std::vector<std::string> paths = Utils::getHGTFilesList();

    std::cout << " num files : " << paths.size() << std::endl;
    app->run();
    return 0;
}
