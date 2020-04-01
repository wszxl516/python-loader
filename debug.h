#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define INFO "\033[32m[INFO]"
#define ERROR   "\033[31m[EROOR]"
#define WARRING "\033[33m[WARRING]"

void get_time(char *buffer, size_t st)
{
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer, 128,"%Y/%m/%d %H:%M:%S",timeinfo);
}

void Log(const char *file,const int line, const char *name, const char *level,const char *fmt,...)
{


	char buf[1024] = {0};
	char buffer[10];
	va_list ap;
	va_start(ap,fmt);

	while(*fmt != '\0')
	{
		if(*fmt == '%')
		{
			fmt++;
			if(*fmt == 's')
			{
                char *s;
				s = va_arg(ap,char *);
				strcat(buf,s);
			}
			else if(*fmt == 'd')
			{
                int d;
				d = va_arg(ap,int);
				memset(buffer,0,10);
				sprintf(buffer,"%d",d);
				strcat(buf,buffer);
			}
            else if(*fmt == 'l')
            {
                fmt++;
                if(*fmt == 's')
                {
                    wchar_t *wc;
                    wc = va_arg(ap, wchar_t *);
                    sprintf(buffer, "%ls", wc);
                    strcat(buf, buffer);
                }

            }
		}
		else
		{
			memset(buffer,0,10);
			sprintf(buffer,"%c",*fmt);
			strcat(buf,buffer);
		}
		fmt++;
	}

    char stime[128];
    get_time(stime, 128);
    fprintf(stdout,"%s %s file [%s] , line[%d], func [%s] , %s", level, stime, file, line, name, buf);
    printf("\033[0m\n");
	va_end(ap);
	return;
}

#define info(...) Log(__FILE__,__LINE__,__func__,INFO,##__VA_ARGS__)
#define warring(...) Log(__FILE__,__LINE__,__func__,WARRING,##__VA_ARGS__)
#define error(...) Log(__FILE__,__LINE__,__func__,ERROR,##__VA_ARGS__)

