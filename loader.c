#include "Python.h"
#include <locale.h>
#include "config.h"
#include "debug.h"

int
runPython(int argc, char **argv, char *filename, const char *py_path, const char *py_home)
{


    if (DEBUG) info("Python %s\n", Py_GetVersion());
    const char *p;
    int i, sts = 1;
    int inspect = 0;
    int unbuffered = 0;
    char *oldloc = NULL;
    wchar_t **argv_copy = NULL;
    if (argc > 0) {
        argv_copy = PyMem_RawMalloc(sizeof(wchar_t*) * argc);
        if (!argv_copy ){
            error("out of memory\n");
            goto error;
        }
    }

    Py_FrozenFlag = 1; /* Suppress errors from getpath.c */

    if ((p = Py_GETENV("PYTHONINSPECT")) && *p != '\0')
        inspect = 1;
    if ((p = Py_GETENV("PYTHONUNBUFFERED")) && *p != '\0')
        unbuffered = 1;

    if (unbuffered) {
        setbuf(stdin, (char *)NULL);
        setbuf(stdout, (char *)NULL);
        setbuf(stderr, (char *)NULL);
    }

    oldloc = _PyMem_RawStrdup(setlocale(LC_ALL, NULL));
    if (!oldloc) {
        error("out of memory\n");
        goto error;
    }

    setlocale(LC_ALL, "");
    for (i = 0; i < argc; i++) {
        argv_copy[i] = Py_DecodeLocale(argv[i], NULL);
        if (!argv_copy[i]) {
            error("Unable to decode the command line argument #%i\n",
                            i + 1);
            argc = i;
            goto error;
        }
    }
    wchar_t *w_py_path = Py_DecodeLocale(py_path, NULL);
    wchar_t *w_py_home = Py_DecodeLocale(py_home, NULL);
    setlocale(LC_ALL, oldloc);
    PyMem_RawFree(oldloc);
    oldloc = NULL;





    if (argc >= 1)
        Py_SetProgramName(argv_copy[0]);
    Py_SetPythonHome(w_py_home);
    Py_SetPath(w_py_path);
    Py_Initialize();
    PySys_SetPath(w_py_path);

        if(DEBUG)
    {

        PyObject *sys_path = NULL;
        sys_path = PySys_GetObject("path"); 
        const char *syspath = PyUnicode_AsUTF8(PyObject_Str(sys_path));
        wchar_t *path = Py_GetPath();
        wchar_t *home = Py_GetPythonHome();
        wchar_t *program_path = Py_GetProgramFullPath();
        wchar_t *program_name = Py_GetProgramName();
        info("sys.path=%s, PythonPath=%ls, PythonHome=%ls , ProgramFullPath=%ls, GetProgramName=%ls", 
                syspath, path, home, program_path, program_name);
    }

    
    PySys_SetArgv(argc, argv_copy);

    FILE *fp=NULL;
    if((fp = fopen(filename, "r"))==NULL)
    {
        error("can not open %s\n", filename);;
        exit(0);
    }
    PyRun_SimpleFile(fp, filename);
    fclose(fp);

    if (inspect && isatty((int)fileno(stdin)))
        sts = PyRun_AnyFile(stdin, "<stdin>") != 0;

    if (Py_FinalizeEx() < 0) {
        sts = 120;
    }

error:
    PyMem_RawFree(argv_copy);
    PyMem_RawFree(oldloc);
    return sts;
}


