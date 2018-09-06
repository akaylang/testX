//
//  findfile.cpp
//  x_test
//
//  Created by wangjingkai on 2018/9/6.
//  Copyright © 2018年 wangjingkai. All rights reserved.
//

#include "findfile.hpp"


int findfilefromdir(const char * path, std::vector<std::string> & filelist , int type)
{
    std::string strFormat;
    if(type == FORMAT_JPG){
        strFormat = ".jpg";
    }else if(type == FORMAT_BMP){
        strFormat = ".bmp";
    }else{
        strFormat = "";
    }
    
    struct dirent * pdirent;
    DIR *pdir;
    
    struct stat status = {0};
    
    if(path == nullptr){
        return  -1;
    }
    
    pdir = opendir(path);
    
    if(pdir == nullptr){
        return -2;
    }
    
    while(true){
        
        std::string fullname;
        fullname = path;
        if(fullname.at(fullname.size() - 1) != '/'){
            fullname += "/";
        }
    
        pdirent = readdir(pdir);
        
        if(pdirent == nullptr){
            break;
        }
        
        if(strcmp(pdirent->d_name,".") == 0 || strcmp(pdirent->d_name,"..") == 0 || (strlen(pdirent->d_name) && pdirent->d_name[0] == '.')){
            continue;
        }
        
        fullname += pdirent->d_name;
        
#if _DEBUG
        printf("name [%s] fullname [%s]\n",pdirent->d_name,fullname.c_str());
#endif
        if(stat(fullname.c_str(),&status) < 0){
            printf("ERROR [%s]\n",fullname.c_str());
            return -4;
        }
        
        if(S_ISDIR(status.st_mode)){
            //dir
            findfilefromdir(fullname.c_str(), filelist,type);
        }
        
        int pos = fullname.rfind(".");
        
        std::string format1 = fullname.substr(pos,fullname.length());
        
        
        if(format1 == strFormat){
            filelist.push_back(fullname);
        }
        
        
    }
    
    return 0;
}
