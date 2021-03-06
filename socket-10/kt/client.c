#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_PROT 8080
#define SERV_IP "192.168.152.128"

int main(void)
{
    int cfd,len;
    struct sockaddr_in saddr;
    char buf[4096] = "helloworld";

    cfd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&saddr,sizeof(saddr));
    saddr.sin_family = AF_INET;
    inet_pton(AF_INET,SERV_IP,(void*)&saddr.sin_addr.s_addr);//目标器的ip地址
    saddr.sin_port = htons(SERV_PROT);

    connect(cfd,(struct sockaddr *)&saddr,sizeof(saddr));

    write(cfd,buf,strlen(buf));
    len = read(cfd,buf,sizeof(buf));
    write(STDOUT_FILENO,buf,len);
    
    close(cfd);

    return 0;
}
