//
//  tcp.hpp
//  x_test
//
//  Created by wangjingkai on 2018/9/8.
//  Copyright © 2018年 wangjingkai. All rights reserved.
//

#ifndef tcp_hpp
#define tcp_hpp

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

using namespace std;

#define         MAX_SOCK        200

struct sockinfo{
    char ip[64];
    int port;
 
    sockinfo(){
        memset(ip,0,sizeof(ip));
        port = -1;
    }
};

class CTcpBase {
public:
    CTcpBase();
    CTcpBase(const sockinfo info);
    CTcpBase(const char * ip, const int port);
    ~CTcpBase();
private:
    bool isInitSuc;
    bool isTcpClient;
    string strIp;
    int nPort;
    
    int m_sock;
    int m_sub_sock;
    
    socklen_t m_len;
    
    struct sockaddr_in m_sock_addr, m_recv_addr;
    
    struct sockinfo sock_info;
    
private:
    int CreateSocket(const struct sockinfo info);
    
public:
    int CreateSocket(const char * ip, const int port);
    int Service_w(void);
    int Accept(void);
    int Service_w(const struct sockinfo info);
    
    int Send(const char * buf);
    int Recv(char * buf);
    int CloseSub(void);
    int Close(void);
    
    int Connect(const char *ip = nullptr, const int port = 9001);
    
    int GetRecvIP(char * reip, int & report);
    
};


#endif /* tcp_hpp */
