#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>


//删除行尾的回车和换行
char *str_clear_crlf(char *s)
{
    int i = strlen(s) - 1;
    if(s)
    {
        for(int j = i;j >= 0;j--)
        {
            if(s[j] == '\n' || s[j] == '\r')
            {
                s[j] = 0;
            }
            else
            {
                break;
            }
        }
    }
    return  s;
}

void print_debug(const char *file, const char *funtion,int linenum,const char *fmt, ...)
{
    static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
    static int count=0;

    int flag = 0;

    char buf[512]={0};
    char buffer[1024]={0};
    int offset = 0;
    int level = 0;
    if(fmt[0] > 0 && fmt[0] < 7)
    {
        offset = 1;
        if(fmt[0] <= 1)//DEBUG_HIDDEN
        {
            goto end;
        }
        else
        {
            level = fmt[0];
        }
    }
    pthread_mutex_lock ( &log_mutex );
    va_list ap;
    va_start (ap, fmt);
    vsnprintf(buf,512,fmt,ap);
    va_end (ap);

    char *p = strrchr(file, '/');
    if(p != NULL)
    {
        p += 1;
    }
    else
    {
        p = (char *)file;
    }

    if(flag == 0)
    {
        fprintf(stderr,"[%d <%s> %d (%s)]: ",++count, p, linenum, funtion);
    }
    else
    {
        snprintf(buffer,1024,"[%d <%s> %d (%s)]: ", ++count, p, linenum, funtion);
    }
    if(level == 3 || level == 4 || level == 5 || level == 6)//DEBUG_FATAL DEBUG_LIGHT
    {
        fprintf(stderr,"\033[31;46;5m");//闪烁
        if(level == 3 || level == 4)
        {
            if(flag == 0)
            {
                fprintf(stderr,"\033[31;46;1m");
            }
            else
            {
                strcat(buffer,"\033[31;46;1m");
            }
        }
        else
        {
            if(flag == 0)
            {
                fprintf(stderr,"\033[31;42;1m");
            }
            else
            {
                strcat(buffer,"\033[31;42;1m");
            }
        }
    }
    str_clear_crlf(buf);
    if(flag == 0)
    {
        fprintf(stderr,"%s",buf + offset);
    }
    else
    {
        strcat(buffer,buf + offset);
    }
    if(level == 3 || level == 4 || level == 5 || level == 6)//DEBUG_FATAL DEBUG_LIGHT
    {
        if(flag == 0)
        {
            fprintf(stderr,"\033[39;49;0m");
        }
        else
        {
            strcat(buffer,"\033[39;49;0m");
        }
    }
    if(flag == 0)
    {
        fprintf(stderr,"\n");
    }
    if(level == 5)//DEBUG_FATAL
    {
        if(level == 5)
        {
            if(flag == 0)
            {
                fprintf(stderr,"\n");
                fprintf(stderr,"\033[31;46;5m");//闪烁
                fprintf(stderr,"======================FATAL ERROR======================");
                fprintf(stderr,"\033[39;49;0m");
                fprintf(stderr,"\n");
            }
            else
            {
                strcat(buffer,"\n");
                strcat(buffer,"\033[31;46;5m");//闪烁
                strcat(buffer,"======================FATAL ERROR======================");
                strcat(buffer,"\033[39;49;0m");
                strcat(buffer,"\n");
            }
        }
    }

    if(flag != 0)
    {
        //LOGI("%s",buffer);
        FILE *fp = fopen("log.txt", "ab+");
        if(fp)
        {
            fprintf(fp, "%s", buffer);

            fclose(fp);
        }
    }
    pthread_mutex_unlock ( &log_mutex );

end:
    return;
}

