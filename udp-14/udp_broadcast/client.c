#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <net/if.h>

//#define SERVER_PORT 8000
#define MAXLINE 4096

#define CLIENT_PORT 9000

int main(int argc,char *argv[])
{
    struct sockaddr_in localaddr;
    int confd;
    ssize_t len;
    char buf[MAXLINE];

    //1.创建一个socket
    confd = socket(AF_INET,SOCK_DGRAM,0);

    //2、初始化本地端地址
    bzero(&localaddr,sizeof(localaddr));
    localaddr.sin_family = AF_INET;
    inet_pton(AF_INET,"0.0.0.0",&localaddr.sin_addr.s_addr);
    localaddr.sin_port = htons(CLIENT_PORT);
    bind(confd,(struct sockaddr *)&localaddr,sizeof(localaddr));

    while(1)
    {
        len = recvfrom(confd,buf,sizeof(buf),0,NULL,0);
        write(STDOUT_FILENO,buf,len);
    }

    close(confd);
    return 0;
}
