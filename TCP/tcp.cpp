//
//  tcp.cpp
//  x_test
//
//  Created by wangjingkai on 2018/9/8.
//  Copyright © 2018年 wangjingkai. All rights reserved.
//

#include "tcp.hpp"

CTcpBase::~CTcpBase(){
    
    CloseSub();
    Close();
}
CTcpBase::CTcpBase(){
    isInitSuc = false;
    m_len = 0;
    m_sub_sock = 0;
    m_sock = 0;
}

CTcpBase::CTcpBase(const char * ip, const int port){
    size_t len = strlen(ip);
    
    m_len = 0;
    m_sub_sock = 0;
    m_sock = 0;
    
    if(!len  || port < 1000){
        isInitSuc = false;
        return ;
    }
    
    strcpy(sock_info.ip,ip);
    sock_info.port = port;
    
    strIp = ip;
    nPort = port;
    isInitSuc = true;
}

CTcpBase::CTcpBase(const struct sockinfo info){
    size_t len = strlen(info.ip);
    
    m_len = 0;
    m_sub_sock = 0;
    m_sock = 0;
    
    if(!len  || info.port < 1000){
        isInitSuc = false;
        return ;
    }
    
    sock_info = info;
    
    strIp = info.ip;
    nPort = info.port;
    isInitSuc = true;
}


int CTcpBase::CreateSocket(const struct sockinfo info){
  
    if(m_sock > 0)
    {
        printf("socket is not null \n");
        return 1;
    }
    
    m_sock = socket(PF_INET,SOCK_STREAM,0);
    
    if(m_sock <= 0)
    {
        printf("socket faild!\n");
        return -1;
    }

    struct sockaddr_in my_addr;
    
    my_addr.sin_family = PF_INET;
    my_addr.sin_port = htons(info.port);
    my_addr.sin_addr.s_addr = INADDR_ANY;//inet_addr("127.0.0.1");
    
    int ret = bind(m_sock,(const struct sockaddr *)&my_addr,(socklen_t)sizeof(my_addr));
    
    if(ret == -1){
        printf("bind faild!error [%d]\n",errno);
        return -2;
    }
    
    ret = listen(m_sock,MAX_SOCK);
    
    if(ret){
        printf("listren faild! error [%d]\n",errno);
        return -3;
    }

    return 0;
}

int CTcpBase::CreateSocket(const char * ip, const int port){
    
    strcpy(sock_info.ip,ip);
    sock_info.port = port;
    
    CreateSocket(sock_info);
    
    return 0;
}

int CTcpBase::Accept(void){
    
    isTcpClient = false;
    
    if(m_sub_sock > 0){
        close(m_sub_sock);
        m_sub_sock = 0;
    }
    
    CreateSocket(sock_info);
    
    m_sub_sock = accept(m_sock,(struct sockaddr *)&m_recv_addr,&m_len);
    
    return 0;
}

int CTcpBase::Service_w(const struct sockinfo info){
    
    CreateSocket(info);
    
    Accept();
    
    return 0;
}

int CTcpBase::Send(const char * buf){
    
    int sock = 0;
    
    if(isTcpClient)
    {
        sock = m_sock;
    }else{
        sock = m_sub_sock;
    }
    
    send(sock, (const void *)buf, strlen(buf), 0);
    
    return 0;
}

int CTcpBase::Recv(char * buf){
    
    int sock = 0;
    
    if(isTcpClient)
    {
        sock = m_sock;
    }else{
        sock = m_sub_sock;
    }
    
    int buf_len = 0;
    string strBuffer;
    char tmp[1024] = {0};
    do{
        
        buf_len = recv(sock, (void *)tmp,(ssize_t)sizeof(tmp),0);
        
        strBuffer += tmp;
        memset(tmp,0,sizeof(tmp));
    }while(buf_len > 0);
    
    strcpy(buf,strBuffer.c_str());
    
    return 0;
}


int CTcpBase::Service_w(void)
{
    int ret = Accept();
    return ret;
}

int CTcpBase::CloseSub(void){
    
    assert(!isTcpClient);
    
    if(m_sub_sock <= 0){
        return 0;
    }
    close(m_sub_sock);
    m_sub_sock = 0;
    return 0;
}

int CTcpBase::Close(void){
    
    if(m_sock <= 0)
        return 0;
    
    close(m_sock);
    
    m_sock = 0;
    
    return 0;
}


int CTcpBase::Connect(const char *ip, const int port)
{
    
    isTcpClient = true;
    
    if(m_sock > 0 ){
        return 1;
    }
    
    m_sock = socket(PF_INET,SOCK_STREAM,0);
    
    if(m_sock <= 0){
        printf("socket faild!\n");
        return -1;
    }
    
    if(ip == nullptr){
        printf("ip is null\n");
    }else{
        strcpy(sock_info.ip,ip);
    }
    
    if(port < 1000){
        printf("port is no rule\n");
    }else{
        sock_info.port = port;
    }
    
    if(sock_info.port < 1000){
        printf("port faild!\n");
        return -3;
    }
    
    printf("ip : [%s]  port:[%d]\n",sock_info.ip,sock_info.port);
    
    m_sock_addr.sin_family = PF_INET;
    m_sock_addr.sin_port = htons(sock_info.port);
    m_sock_addr.sin_addr.s_addr = inet_addr(sock_info.ip);
    
    int ret = connect(m_sock, (const struct sockaddr *)&m_sock_addr, (socklen_t)sizeof(struct sockaddr));
    if(ret < 0){
        printf("connect faild!\n");
        return -2;
    }
    
    return 0;
}
