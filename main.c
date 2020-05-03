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
    status = mkdir(PY_PATH, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); 
    status = mkdir(PY_LIB, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); 
    fp = fopen(PY_BASE_LIB, "wb");
    fwrite((void*)data, 1, sizeof(data)/sizeof(char), fp); 
    fclose(fp);
    main = fopen(PY_MAIN, "wb");
    fwrite((void*)main_data, 1, sizeof(main_data)/sizeof(char), main);
    fclose(main);

}
void cleanenv()
{
    remove(PY_BASE_LIB);
    remove(PY_LIB);
    remove(PY_MAIN);
    remove(PY_PATH);
}

int main(int argc, char **argv)
{
    mkenv();
    runPython(argc, argv, PY_MAIN, PY_BASE_LIB":"PY_LIB, PY_PATH);
    cleanenv();
    return 0;
}
