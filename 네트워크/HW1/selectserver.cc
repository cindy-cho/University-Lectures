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

    /*server와 비교해서 달라진 점*/
    //소켓을 위한 자료구조
    fd_set master;
    fd_set read_fds;
    int fdmax;

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

    
    if((rv = getaddrinfo(NULL, argv[1], &hints, &servinfo))!=0){
        fprintf(stderr,"getaddrinfo:%s\n",gai_strerror(rv));
        exit(1);
    }

    if((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol))==-1){
        perror("server : socket");
        exit(1);
    }

    //client는 connect  server는 bind
    //bind라는것은 portnumber와  이 socket을 바인딩 하겠다.
    if(bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen)==-1){
        close(sockfd);
        perror("server: bind");
        exit(1);
    }

    freeaddrinfo(servinfo);

    
    if(listen(sockfd, BACKLOG)==-1){
        perror("listen");
        exit(1);
    }

    FD_ZERO(&master);//값 초기화
    FD_SET(sockfd, &master);
    fdmax = sockfd;

    while(1){
        read_fds = master; //갖고있는 소켓정보를 read_fds에 copy해서 읽어서 쓴다.
        if(select(fdmax+1, &read_fds, NULL, NULL, NULL)==-1){
            perror("select");
            exit(1); 
        }
    }

    for(int i=0;i<=fdmax;i++){
        if(FD_ISSET(i, &read_fds)){ //read fd에 불이 켜져있는가를 확인.불이켜져있으면 메세지가 도착했다는 얘기
            if(i==sockfd){ //sockfd서버가 만들어졌을때 (주로 3번) 바인딩되고 리슨하는 소켓 (receptionist socket)
            //reception socket이 불이 들어왔다는 것은 클라이언트한테 connection 요구과 왔다는 뜻임
                sin_size = sizeof their_addr;
                new_fd = accept(sockfd, (struct sockaddr*)&their_addr,&sin_size);
                //취하는 적절한 액션이 accept이다. 새소켓이 만들어진다.

                if(new_fd == -1){
                    perror("accept");
                    exit(1);
                }
                else{//이 아래 세줄이 중요
                    FD_SET(new_fd, &master);
                    if(new_fd > fdmax){
                        fdmax = new_fd;
                    }
                    printf("selectserver : new connection from %s on socket %d\n",inet_ntop(their_addr.ss_family, &((struct sockaddr_in*)&their_addr)->sin_addr,s,sizeof s),new_fd);
                }
            }
            else{
                if(numbytes = rec(i,buf,sizeof buf, 0)) <= 0){
                    if(numbytes == 0){
                        printf("selectserver : socket %d hung up\n",i);
                    }else{
                        perror("recv");
                    }
                    close(i);
                    FD_CLR(i, &master);
                }
                else{
                    buf[numbytes] = '\0';
                    printf("server received: %s\n",buf);

                    if(send(i,buf,strlen(buf), 0)==-1){
                        perror("send");
                    }
                }
            }
        }
    }
}
//FD_ZERO(&master);
//2줄짜리 위에