#include <Python.h>
#include <string>

int main(int argc, char** argv)
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

    Py_Initialize();
    PyObject *pModule = PyImport_AddModule("__main__"); //create main module
    PyRun_SimpleString(stdOutErr.c_str()); //invoke code to redirect
    PyRun_SimpleString("import test");
    //PyRun_SimpleString("f()"); 
    PyObject *catcher = PyObject_GetAttrString(pModule,"catchOutErr"); //get our catchOutErr created above

    PyObject *output = PyObject_GetAttrString(catcher,"value"); //get the stdout and stderr from our catchOutErr object
    printf("Here's the output:\n %s", PyString_AsString(output)); //it's not in our C++ portion

    Py_Finalize();


    return 0;

}
//g++ test.cpp -o test -I/usr/include/python3.7m -lpython3.7m

// #include <Python.h>

// int main() {
//     Py_Initialize();
//     PyRun_SimpleString("import sys; sys.path.append('.')");
//     PyRun_SimpleString("import main");
//     PyRun_SimpleString("print('hello world')");
//     Py_Finalize();

//     return 0;
// }

//g++ test.cpp -o test -I/usr/include/python3.7m -lpython3.7m