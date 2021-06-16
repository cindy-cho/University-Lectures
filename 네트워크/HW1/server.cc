// server.cc

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXDATASIZE 1000
#define BACKLOG 10 //client 가 connection request보낼때 대기 몇 번 까지 받을지. 10명 넘어가면 connection자체가 멈추도록(?) 한다.

int main(int argc, char *argv[]){
    int sockfd;
    int new_fd; //클라이언트 별로 소켓을 만든다. 1개는 기본적으로 있고, 올때마다 소켓을 만들어서 새 클라이언트에게 부여하게 되어있다.
    struct addrinfo hints, *servinfo;
    struct sockaddr_storage their_addr; //서버입장에서 클라이언트 주소를 저장
    socklen_t sin_size;
    char s[INET_ADDRSTRLEN];
    int rv;

    char buf[MAXDATASIZE];
    int numbytes;

    if(argc != 2){ //port넘버만 주면 된다. remote 한 서버가 없어서
        printf("usage: server portnum\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; //기다리는 쪽이니까 내 ipaddress로 기다리겠다. - 서버에는 필요
    //ai passive를 주고 NULL을 주는게 server 족이다
    rv = getaddrinfo(NULL, argv[1], &hints, &servinfo);
    sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    //client는 connect  server는 bind
    //bind라는것은 portnumber와  이 socket을 바인딩 하겠다.
    bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);

    freeaddrinfo(servinfo);

    
    listen(sockfd, BACKLOG);
    printf("server : waiting for connections on port %s...\n",argv[1]);
    
    sin_size = sizeof their_addr;
    //blocking
    new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size);

    if(new_fd == -1) {
        perror("accept");
        exit(1);
    }

    inet_ntop(their_addr.ss_family, &((struct sockaddr_in*)&their_addr)->sin_addr, s, sizeof s);
    printf("server : got connection from %s\n", s);
    close(sockfd);

    while(1){
        //blocking
        //서버는 numbytes를 보고 행동함
        numbytes = recv(new_fd, buf, sizeof buf, 0);
        if(numbytes==-1){ //error
            perror("recv");
            close(new_fd);
            exit(0);
        }
        if(numbytes==0){ //client kill the server
            close(new_fd);
            break;
        }
        
        buf[numbytes] = '\0';
        printf("server : received '%s'\n",buf);

        //client쪽으로 buf에 있는 msg를 보내준다. - echo server
        send(new_fd,buf, strlen(buf), 0);
    }

    close(new_fd);
    return 0;

}