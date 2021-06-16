
// client.cc -- a simple socket client 
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
int main(int argc, char *argv[]) {     
    int sockfd, numbytes;     
    char buf[MAXDATASIZE];     
    struct addrinfo hints, *servinfo;     
    int rv;     
    char s[INET_ADDRSTRLEN];     
    if(argc != 3) {         
        fprintf(stderr, "usage: client hostname portnum\n");         
        exit(1);     
    }     
    memset(&hints, 0, sizeof hints);     
    hints.ai_family = AF_UNSPEC;     
    hints.ai_socktype = SOCK_STREAM;     
    if((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0) {         
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));         
        return 1;     
    }
    if((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,servinfo->ai_protocol)) == -1) 
    {         
        perror("client: socket");         
        return 2;     
    }     
    
    if(connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) 
    {         
        close(sockfd);         
        perror("client: connect");
        return 2;
    }
    
    inet_ntop(servinfo->ai_family, &((struct sockaddr_in*)servinfo->ai_addr)- >sin_addr, s, sizeof s);
    printf("client: connecting to %s\n", s);
    freeaddrinfo(servinfo);     
    strcpy(buf, "hello");     
    if(send(sockfd, buf, strlen(buf), 0) == -1) 
    {         
        perror("send");         
        close(sockfd);         
        exit(1);     
        }

    if((numbytes = recv(sockfd, buf, sizeof buf, 0)) == -1) 
    {         
        perror("recv");         
        close(sockfd);         
        exit(1);     
    }
    buf[numbytes] = '\0';     
    printf("client: received '%s'\n", buf);
    close(sockfd);     
    return 0; 
    }

/* // client.cc -- a simple socket client

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

//cspro IP : 163.239.27.151

#define MAXDATASIZE 1000 //버퍼의 사이즈 지정 (메세지 받거나 전송 할 때), 버퍼 단위로 끊어져서 받게 됨

int main (int argc, char *argv[]){
    int sockfd; //socket file descripter - 소켓을 지칭하는 번호(int) 저장
    int numbytes; //function return 을 받기 위해
    char buf[MAXDATASIZE]; //char를 쓰는 이유는 숫자이던, string을 받던 받을 수 있기 때문
    struct addrinfo hints, *servinfo; //*이게 핵심. 소켓을 만들면 정보를 담고있는 구조체. address info이다.
    int rv; //functiond의 return value
    char s[INET_ADDRSTRLEN]; //IP 주소를 담기위함

    if(argc !=3){ //client 실행시킬때 arg2개 받을거임. ip 주소, 포트넘버가 안들어오면 진행하면 안되기 때문에 종료한다.
        fprintf(stderr, "usage : client hostname portnum\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints); //구조체의 값을 0으로 초기화 시켜준다.
    hints.ai_family = AF_UNSPEC; //ipv4(32비트), ipv6(보급이 많이 되긴됐는데 128비트), unspecified이냐. 아직까지는 ipv4를 사용.
    hints.ai_socktype = SOCK_STREAM; //TCP,(Sock_STREAM) UDP(SOCK_DGRAM)

    //함수를 불러서 인자를 넘겨준다. argv1 : 서버의 ip 주소, 포트, hints값, 서브info는 포인트만 넘겨주고 getaddr이 servinfo에 값을 넘겨주긴함.
    if((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo))!=0){ 
    //제대로 돌아오면 0값을 return 받는다.)
        fprintf(stderr, "getaddrinfo : %s\n", gai_strerror(rv));
        return 1;
    }

    //create socket
    //socket번호가 return, -1이면 소켓 생성 실패
    if((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol))==-1){
        perror("client: socket");
        return 2;
    }

    //connect to server
    if(connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen)==-1){
        close(sockfd);
        perror("client:connect");
        return 2;
    }

    // ^^^^^ 여기까지는 연결하는 부분

    // print to screen (없어도 되는 부분)
    //저장되어있는 주소를 string으로 바꿔서 그냥 화면에 찍어줌
    inet_ntop(servinfo->ai_family, &((struct sockaddr_in*)servinfo->ai_addr)->sin_addr, s, sizeof s);
    printf("client : connecting to %s\n",s);

    // free allocated memory for servinfo
    freeaddrinfo(servinfo);

    //send message
    strcpy(buf, "hello");
    if((send(sockfd, buf, strlen(buf), 0))==-1){
        perror("send");
        close(sockfd);
        exit(1);
    }

    //receive message(blocking) **blocking function에 대한 개념 챙기고 가기
    //receive function을 콜하면 메세지를 받을때가지 이 펑션이 멈추어 있음. 안오면 뒤로 넘어가지 않음. 올때까지 기다림.
    //receive를 쓸때는 blocking 을 기억, 내가 원래는 receive 기다리면서 또 send 할 수 있게 짜줘야 한다. (이렇게 짜면 안됨)
    if((numbytes == recv(sockfd, buf, sizeof buf, 0)) == -1){
        perror("recv");
        close(sockfd);
        exit(1);
    }

    buf[numbytes] = '\0'; // add null character at the end. 메세지가 올때는 뒤에 NULL이 안붙어서 온다. 그런데 아래에서 %s로 출력할거기때문에 \0을 넣어준것. string으로 안찍으면 상관없다.
    printf("client: received '%s'\n", buf);

    close(sockfd);
    return 0;

    



}
 */