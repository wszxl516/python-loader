#include "loader.h"
#include "config.h"

int main(int argc, char **argv)
{
    char *filename="__main__.py";
    wchar_t *tmp = L"/tmp";
    runPython(argc, argv, filename, tmp);
    return 0;
}
