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

#define MAXDATASIZE 10000

//String으로 저장한 ContentLength를 int로 변환하여 준다
int stringToInt(char *contentLength){
    int target=0,dec=1;
    for(int i=strlen(contentLength)-1;i>=0;i--){
        target += dec * (contentLength[i]-'0');
        dec *=10;
    }
    return target;
}

//Content-Length를 포함하고 있는지 판별하기 위해 모두 대문자->소문자로 변환한 후 content-length가 있다면 return 1을 한다, 반대의 경우 return 0
int isContentLength(char *input){
    char *temp=input;
    for(int i=0;i<strlen(temp);i++){
        if(temp[i]>='A' && temp[i]<='Z'){
            temp[i] = temp[i] - ('A'-'a');
        }
    }
    if(strstr(temp,"content-length")==NULL) return 0;
    return 1;
}

//전달받은 buf에서 헤더 부분 파싱하는 부분
char* parsingHeader(char *buf,char **contentLength,int *findContentLength){
    char *headerContent;

    //한 줄 씩 읽어들어오는 부분, content-length를 찾기 위해 isContentLength함수로 한 줄 씩 넘겨준다.
    headerContent = strtok(buf,"\n");
    printf("%s\n",headerContent); //첫 줄은 값이 변경되면 안되니까 일단 출력한다. (HTTP/1.1 라인)
    
    headerContent = strtok(NULL,"\n");
    while(headerContent!=NULL){
        if(strlen(headerContent)==1) break;
        if(isContentLength(headerContent)==1){
            *findContentLength = 1;
            headerContent+=16;
            *contentLength = (char*)malloc(sizeof(char)*strlen(headerContent));
            strcpy(*contentLength,headerContent);
        }
        headerContent = strtok(NULL,"\n");
    }

    if(*findContentLength==-1) return 0;
    
    //헤더 처리 후 나머지 본문 값을 가지고 있다.
    headerContent = strtok(NULL,"\0");
    return headerContent;    
}

int main(int argc, char *argv[]){
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo;
    int rv;
    char s[INET_ADDRSTRLEN];

    //입력받은 arg를 parsing하여 호스트네임, 포트, 파일패쓰로 나눠 각각 저장한다.
    char *hostname,*port,*pathToFile,*editedPathToFile;
    char changeLine[] = "\r\n";

    //header부분 parsing할 때 사용
    int isHeaderParsed = -1; //헤더 부분 찾아서 처리했으면 값을 1로 바꾼다.
    char *headerContent, *contentLength;
    int findContentLength = -1; //content-length가 존재하면 findContentLength 값을 1로 바꾼다.
    
    //본문 
    int intContentLength; //본문의 길이
    int receivedContent=0; //전달받은 길이

    //File Write 관련
    FILE *fp;
    
    //프로그램에 들어가는 인자가 없거나 두개 이상, 인자부분에 http://없는 경우의 에러표시
    if(argc != 2 || strstr(argv[1],"http://")==NULL){
        fprintf(stderr, "usage: http_client http://hostname[:port][/path/to/file]\n");
        exit(1);
    }

    strtok(argv[1],"/");
    hostname = strtok(NULL,":");
    hostname++;
    port = strtok(NULL,"/");
    if(port==NULL){
        hostname = strtok(hostname,"/");
        pathToFile = strtok(NULL,"");
        if(pathToFile!=NULL){
            editedPathToFile = (char*)malloc(sizeof(char)*strlen(pathToFile));
            editedPathToFile[0] = '/';
            strcat(editedPathToFile,pathToFile);
            pathToFile = editedPathToFile;
        }
        
        //port가 NULL일 경우 기본 port 80번 부여
        port = (char*)malloc(sizeof(char)*3);
        strcpy(port,"80"); 
    }

    
    else {
        pathToFile = strtok(NULL,"");
    }
    
    //filepath가 NULL인 경우 기본값 / 부여
    if(pathToFile==NULL){
        pathToFile = (char*)malloc(sizeof(char)*2);
        strcpy(pathToFile,"/");
    }

    // printf("hostname : %s\n",hostname);
    // printf("port : %s\n",port);
    // printf("pathToFile : %s\n",pathToFile);
    
    memset(&hints, 0 , sizeof hints);
  
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
  
    //hostname부분을 domain name으로 썼을 경우, DNS에서 해당 domain name에 대한 IP address를 찾지 못한 경우
    if((rv = getaddrinfo(hostname, port, &hints, &servinfo)) !=0 ){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    //servinfo구조체를 이용하여 socket을 만드는 부분. 실패할 경우 에러 처리
    if((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1){
        perror("client: socket");
        return 2;
    }
    
    //IP address는 얻었는데 서버와의 TCP연결에 실패 한 경우
    if(connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1){
        close(sockfd);
        perror("connect");
        exit(1);
    }
    
    //서버로 연결했다는 메시지를 출력하기 위한 부분. 본 과제에서는 사용하지 않아서 주석 처리
    // inet_ntop(servinfo->ai_family, &((struct sockaddr_in*)servinfo->ai_addr)->sin_addr, s, sizeof s);
    // printf("client: connecting to %s\n",s);

    //연결에 성공했다면 서버의 정보를 담고 있는 servinfo 구조체는 더 이상 필요 없으므로 free 시켜준다.
    freeaddrinfo(servinfo);
   
    //HTTP request message보내는 부분 
    strcpy(buf,"GET ");
    strcat(buf,pathToFile);
    strcat(buf," HTTP/1.1\r\n");
    strcat(buf,"Host: ");
    strcat(buf,hostname);
    strcat(buf,":");
    strcat(buf,port);
    strcat(buf,"\r\n\r\n");
    strcat(buf,"\0");
    
    if(send(sockfd, buf, strlen(buf), 0) == -1){
        perror("send");
        close(sockfd);
        exit(1);
    }

    numbytes = recv(sockfd, buf, sizeof buf, 0);
    while(1){
        receivedContent += numbytes;
        if(numbytes==-1)
        {   
            perror("recv");
            close(sockfd);
            break;
            exit(1);
        }
        else if(numbytes<=0) {
            break;
        }
        else{
            if(isHeaderParsed==-1){ // 헤더 부분이 처리가 안됐으면
                buf[numbytes] = '\0';
                isHeaderParsed = 1;
                headerContent = parsingHeader(buf,&contentLength,&findContentLength);

                if(findContentLength==-1){
                    printf("Content-Length not specified.\n");
                    break;
                }
                
                else{
                    contentLength[strlen(contentLength)-1]='\0';
                    intContentLength = stringToInt(contentLength);
                    fp = fopen("20151610.out","w");

                    //파일 열기 실패한 경우
                    if(fp == NULL){
                        printf("FAIL TO CREATEE OUTPUT FILE\n");
                        exit(1);
                    }
                    
                    if(headerContent!=NULL){
                        fprintf(fp,"%s",headerContent);
                    }
                }
            } 
            else{
                buf[numbytes] = '\0';
                fprintf(fp,"%s",buf);
            }
        }
        
        //recv는 blocking함수인데, 0을 돌려주지 않는 경우도 있어서 입력받은 길이와, header에서 parsing한 content-length 값을 비교하여 같거나 초과했을 경우 recv호출을 그만한다.
        if(receivedContent>=intContentLength) break;;
        numbytes = recv(sockfd, buf, sizeof buf, 0);

    }

    if(findContentLength==1){
        printf("%s bytes written to 20151610.out\n",contentLength);
        fclose(fp);
    }
    close(sockfd);
    
    return 0;
}