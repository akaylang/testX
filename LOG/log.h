//
//  log.h
//  x_test
//
//  Created by wangjingkai on 2018/8/25.
//  Copyright © 2018年 wangjingkai. All rights reserved.
//

#ifndef log_h
#define log_h

#include <string>


#define     PATH_LOG                "./"
#define     LOG_BUFFER_LEN          1024

class Log
{
public:
    Log(const char * path);
    Log();
    Log(const char * path , const char * type_name = "LOG");
    Log(const std::string path);
    Log(const std::string path, const std::string type_name);
    ~Log(){}
    
public:
    void WriteToLog(const char * fmt, ...);
    void WriteToLog(std::string fmt);
    
    int SetPath(const char *path);
    int SetPath(std::string path);
    
    int SetTypeName(const char *type_name);
    int SetTypeName(std::string type_name);
    
private:
    std::string format_string(char *fmt,...);
    void SaveToFile(const char * path, const char * buffer);
    std::string GetLocalTransferToString();
    std::string GetFilenameFromTime(const char * name_type);
    
private:
    std::string m_path;
    int m_log_type;
    std::string m_type_name;
    
};

#endif /* log_h */
