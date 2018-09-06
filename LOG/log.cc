//
//  log.cpp
//  x_test
//
//  Created by wangjingkai on 2018/8/25.
//  Copyright © 2018年 wangjingkai. All rights reserved.
//

#include <stdio.h>
#include "log.h"

Log::Log(const char * path){
    m_path = path;
    m_type_name = "LOG";
}

Log::Log(){
    m_path = PATH_LOG;
    m_type_name = "LOG";
}

Log::Log(const char * path,const char *type_name){
    m_path = path;
    m_type_name = type_name;
}

Log::Log(std::string path){
    m_path = path;
    m_type_name = "LOG";
}

Log::Log(std::string path,std::string type_name){
    m_path = path;
    m_type_name = type_name;
}


std::string Log::format_string(char *fmt,...)
{
    std::string str_fmt;
    va_list ap;
    va_start(ap,*fmt);
    
    char *s,c;
    int d;
    
    while(*fmt){
        if(*fmt != '%'){
            str_fmt += *fmt;
            fmt ++;
            continue;
        }
        char tmp[1024] = {0};
        switch(*(++fmt)){
            case 's':
                s = va_arg(ap, char *);
                str_fmt += s;
                fmt++;
                break;
            case 'c':
                c = va_arg(ap, char);
                str_fmt += c;
                fmt++;
                break;
            case 'd':
                d = va_arg(ap, int);
                sprintf(tmp,"%d",d);
                str_fmt += tmp;
                fmt++;
                break;
            default:
                break;
        }
    }
    va_end(ap);
    return str_fmt;
}

void Log::WriteToLog(const char * fmt,...){
    
    std::string str_fmt;
    va_list ap;
    va_start(ap,*fmt);
    
    char *s,c;
    int d;
    
    while(*fmt){
        if(*fmt != '%'){
            str_fmt += *fmt;
            fmt ++;
            continue;
        }
        char tmp[1024] = {0};
        switch(*(++fmt)){
            case 's':
                s = va_arg(ap, char *);
                str_fmt += s;
                fmt++;
                break;
            case 'c':
                c = va_arg(ap, char);
                str_fmt += c;
                fmt++;
                break;
            case 'd':
                d = va_arg(ap, int);
                sprintf(tmp,"%d",d);
                str_fmt += tmp;
                fmt++;
                break;
            default:
                break;
        }
    }
    va_end(ap);
    
    std::string str_time = GetLocalTransferToString();
    std::string filename = GetFilenameFromTime(m_type_name.c_str());
    std::string fullname = m_path + filename;
    
    char *buffer = new char[LOG_BUFFER_LEN];
    sprintf(buffer,"[%s] [%s] : %s \n",m_type_name.c_str(), str_time.c_str(),str_fmt.c_str());
    SaveToFile(fullname.c_str(),  buffer);
    delete [] buffer;
    
}


void Log::WriteToLog(std::string fmt){
    WriteToLog(fmt.c_str());
    
}

void Log::SaveToFile(const char * path,  const char * buffer)
{
    FILE *fp = fopen(path,"a+");
    
    if(!fp){
        fp = fopen(path, "a+");
        
        if(!fp)
        {
            return ;
        }
    }
    
    char *log = new char[LOG_BUFFER_LEN];
    
    fwrite(buffer, strlen(buffer), sizeof(char), fp);
    
    fclose(fp);
    
    delete [] log;
}


std::string Log::GetLocalTransferToString()
{
    std::string str_time;
    
    time_t t = time(NULL);
    
    struct tm * ptm = localtime(&t);
    
    char *buffer = new char[LOG_BUFFER_LEN];
    
    sprintf(buffer,"%04d-%02d-%02d %02d:%02d:%02d",ptm->tm_year + 1900, ptm->tm_mon + 1, \
            ptm->tm_mday,ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
    
    str_time = buffer;
    
    delete[] buffer;
    return str_time;
    
}

//
//
//
//
//
std::string Log::GetFilenameFromTime(const char * name_type)
{
    std::string str_name;
    
    time_t t = time(NULL);
    struct tm *ptm = localtime(&t);
    
    char *buffer = new char[LOG_BUFFER_LEN];
    
    sprintf(buffer,"%s-%04d-%02d-%02d.log",name_type,ptm->tm_year + 1900, ptm->tm_mon + 1, \
            ptm->tm_mday);
    
    str_name = buffer;
    
    delete [] buffer;
    
    return str_name;
}

int Log::SetPath(const char *path){
    m_path = path;
    return 0;
}

int Log::SetPath(std::string path){
    m_path = path;
    return 0;
}

int Log::SetTypeName(const char * type_name){
    m_type_name = type_name;
    return 0;
}

int Log::SetTypeName(std::string type_name){
    m_type_name = type_name;
    return 0;
}

