#ifndef PYTHON_HELPER_H
#define PYTHON_HELPER_H

#include <pch.h>
#include <Python.h>
namespace PythonHelper
{
    static void runScrcript(std::string script_path)
    {
        std::string stdOutErr =
            "import sys\n\
class CatchOutErr:\n\
    def __init__(self):\n\
        self.value = ''\n\
    def write(self, txt):\n\
            self.value += txt\n\
catchOutErr = CatchOutErr()\n\
sys.stdout = catchOutErr\n\
sys.stderr = catchOutErr\n\
"; //this is python code to redirect stdouts/stderr

        // std::cout << "Hello python ?!? __ ?." << std::endl;

        FILE *file = fopen(script_path.c_str(), "r");

        Py_Initialize();
        PyObject *catcher = nullptr;
        PyObject *pModule = PyImport_AddModule("__main__"); //create main module
        if (file)
        {
            PyRun_SimpleString(stdOutErr.c_str()); //invoke code to redirect
            // PyRun_SimpleString("1+a");             //this creates an error
            PyRun_SimpleFile(file, script_path.c_str());
            catcher = PyObject_GetAttrString(pModule, "catchOutErr"); //get our catchOutErr created above

            fclose(file);
        }

        PyErr_Print(); //make python print any errors

        PyObject *output = PyObject_GetAttrString(catcher, "value"); //get the stdout and stderr from our catchOutErr
        PyObject *encoded = PyUnicode_AsEncodedString(output, "utf-8", "strict");
        // printf("Here's the output:\n %s", PyBytes_AsString(encoded));
        // PyRun_SimpleString("import os\nprint(os)\nprint('Hello Python!')");
        Py_Finalize();
    }

    static void runScrcript(std::string script_path, std::string &out)
    {
        std::string stdOutErr =
            "import sys\n\
class CatchOutErr:\n\
    def __init__(self):\n\
        self.value = ''\n\
    def write(self, txt):\n\
            self.value += txt\n\
catchOutErr = CatchOutErr()\n\
sys.stdout = catchOutErr\n\
sys.stderr = catchOutErr\n\
"; //this is python code to redirect stdouts/stderr

        // std::cout << "Hello python ?!? __ ?." << std::endl;

        FILE *file = fopen(script_path.c_str(), "r");

        Py_Initialize();
        PyObject *catcher = nullptr;
        PyObject *pModule = PyImport_AddModule("__main__"); //create main module
        if (file)
        {
            PyRun_SimpleString(stdOutErr.c_str()); //invoke code to redirect
            // PyRun_SimpleString("1+a");             //this creates an error
            PyRun_SimpleFile(file, script_path.c_str());
            catcher = PyObject_GetAttrString(pModule, "catchOutErr"); //get our catchOutErr created above

            fclose(file);
        }

        PyErr_Print(); //make python print any errors

        PyObject *output = PyObject_GetAttrString(catcher, "value"); //get the stdout and stderr from our catchOutErr
        PyObject *encoded = PyUnicode_AsEncodedString(output, "utf-8", "strict");
        // printf("Here's the output:\n %s", PyBytes_AsString(encoded));
        // PyRun_SimpleString("import os\nprint(os)\nprint('Hello Python!')");
        Py_Finalize();

        out = (std::string)PyBytes_AsString(encoded);
    }
}
#endif /* PYTHON_HELPER_H */