#include "loader.h"
#include "config.h"
#include "lib.h"
#include "main.h"
#include <sys/stat.h>
#include <stdio.h>
void mkenv()
{
    int status;
    FILE *fp,*main;                                                                  
    status = mkdir("/tmp/lib", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); 
    fp = fopen("/tmp/lib/python36.zip", "wb");
    fwrite((void*)data, 1, sizeof(data)/sizeof(char), fp); 
    fclose(fp);
    main = fopen("/tmp/__main__.py", "wb");
    fwrite((void*)main_data, 1, sizeof(main_data)/sizeof(char), main);
    fclose(main);

}

int main(int argc, char **argv)
{
    char *filename="/tmp/__main__.py";
    wchar_t *tmp = L"/tmp/lib/python36.zip";
    wchar_t *path = L"/tmp";
    mkenv();
    runPython(argc, argv, filename, tmp, path);
    return 0;
}
