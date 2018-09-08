//
//  findfile.hpp
//  x_test
//
//  Created by wangjingkai on 2018/9/6.
//  Copyright © 2018年 wangjingkai. All rights reserved.
//

#ifndef findfile_hpp
#define findfile_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

enum{FORMAT_JPG = 0,FORMAT_BMP,FORMAT_NONE};

int findfilefromdir(const char * path, std::vector<std::string> & filelist , int type = FORMAT_NONE);


#endif /* findfile_hpp */
