#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int next;
    int cost;
}data;

//프로젝트 1을 했을때 사용했던 함수를 사용하였다
//String으로 저장한 ContentLength를 int로 변환하여 준다
int stringToInt(char *contentLength){
    int target=0,dec=1;
    for(int i=strlen(contentLength)-1;i>=0;i--){
        target += dec * (contentLength[i]-'0');
        dec *=10;
    }
    return target;
}

int main(int argc, char *argv[]){

    if(argc!=4){
        printf("usage: distvec topologyfile messagesfile changesfile\n");
        return 0;
    }
    
    //파일 오픈 관련. 순서대로 (topologyfile, messagesfile, changesfile)
    FILE *tf[3];
    for(int i=0;i<3;i++){
        tf[i] = fopen(argv[i+1],"r");
        //파일 열기 실패한 경우
        if(tf[i] == NULL){
            printf("Error: open input file\n");
            return 0;
        }
    }

    //output file 저장
    FILE *fp;
    fp = fopen("output_dv.txt","w");

    int nodeSize,start,end,cost,mid;

    //Topology file에서 노드의 총 개수를 받아온다.
    fscanf(tf[0], "%d", &nodeSize);

    data networkMap[101][101],connectedMap[101][101];

    //network간 정보 저장하는 networkMap값 초기화
    for(int i=0;i<nodeSize;i++){
        for(int j=0;j<nodeSize;j++){
            //자기자신일 경우에는 cost 0으로 초기화
            if(i==j){
                networkMap[i][j].next=j;
                networkMap[i][j].cost=0;
            }
            else{
                networkMap[i][j].next=j;
                networkMap[i][j].cost=999;
            }
        }
    }

    while(fscanf(tf[0],"%d %d %d",&start,&end,&cost)!=EOF){
        //network간의 연결정보를 저장하는 맵에 값을 넣어준다.
        networkMap[start][end].next = end;
        networkMap[start][end].cost = cost;
        networkMap[end][start].next = start;
        networkMap[end][start].cost = cost;
    }

    for(int i=0;i<nodeSize;i++){
        for(int j=0;j<nodeSize;j++) connectedMap[i][j]=networkMap[i][j];
    }
    
    for(int k=0;k<nodeSize;k++){
        for(int i=0;i<nodeSize;i++){
            for(int j=0;j<nodeSize;j++){
                if(connectedMap[i][k].cost!=999 && connectedMap[k][j].cost!=999 && connectedMap[i][j].cost!=0){
                    //기존 값이 작을 경우 갱신
                    if(connectedMap[i][k].cost+connectedMap[k][j].cost < connectedMap[i][j].cost){
                        connectedMap[i][j].cost = connectedMap[i][k].cost+connectedMap[k][j].cost;
                        connectedMap[i][j].next = connectedMap[i][k].next;
                    }
                }
            }
        }
    }

    for(int i=0;i<nodeSize;i++){
        for(int j=0;j<nodeSize;j++){
            if(connectedMap[i][j].cost!=999) fprintf(fp,"%d %d %d\n",j,connectedMap[i][j].next,connectedMap[i][j].cost);
        }
        fprintf(fp,"\n");
    }
    char messageLine[255];
    char *cStart, *cEnd, *cMessage;

    //message 읽어들어오는 부분
    while(fgets(messageLine,sizeof(messageLine),tf[1])!=NULL){
        cStart = strtok(messageLine," ");
        cEnd = strtok(NULL," ");
        cMessage = strtok(NULL,"");
        start = stringToInt(cStart);
        end = stringToInt(cEnd);
        //송신자 x로 부터 수신자 y로의 경로가 존재하지 않는 경우
        if(connectedMap[start][end].cost==999){
            fprintf(fp,"from %d to %d cost infinite hops unreachable message %s",start,end,cMessage);
        }
        else{
            mid = start;
            fprintf(fp,"from %d to %d cost %d hops %d ",start,end,connectedMap[start][end].cost,start);
            while(connectedMap[mid][end].next!=end){
                mid = connectedMap[mid][end].next;
                fprintf(fp,"%d ",mid); 
            }
            fprintf(fp,"message %s",cMessage);
        }
    }
    fprintf(fp,"\n");
    rewind(tf[1]);

    //changes.txt의 바뀐 노드들을 적용시킨다
    while(fscanf(tf[2],"%d %d %d",&start,&end,&cost)!=EOF){
        //네트워크 간 연결이 끊어졌을 경우
        if(cost==-999){
            networkMap[start][end].cost=999;
            networkMap[end][start].cost=999;
        }
        else{
            networkMap[start][end].cost=cost;
            networkMap[end][start].cost=cost;
        }
        for(int i=0;i<nodeSize;i++){
            for(int j=0;j<nodeSize;j++) connectedMap[i][j]=networkMap[i][j];
        }
        
        for(int k=0;k<nodeSize;k++){
            for(int i=0;i<nodeSize;i++){
                for(int j=0;j<nodeSize;j++){
                    if(connectedMap[i][k].cost!=999 && connectedMap[k][j].cost!=999 && connectedMap[i][j].cost!=0 && connectedMap[i][k].cost+connectedMap[k][j].cost < connectedMap[i][j].cost){
                        connectedMap[i][j].cost = connectedMap[i][k].cost+connectedMap[k][j].cost;
                        connectedMap[i][j].next = connectedMap[i][k].next;
                    }
                }
            }
        }

        for(int i=0;i<nodeSize;i++){
            for(int j=0;j<nodeSize;j++){
                if(connectedMap[i][j].cost!=999) fprintf(fp,"%d %d %d\n",j,connectedMap[i][j].next,connectedMap[i][j].cost);
            }
            fprintf(fp,"\n");
        }

        while(fgets(messageLine,sizeof(messageLine),tf[1])!=NULL){
            cStart = strtok(messageLine," ");
            cEnd = strtok(NULL," ");
            cMessage = strtok(NULL,"");
            start = stringToInt(cStart);
            end = stringToInt(cEnd);
            //송신자 x로 부터 수신자 y로의 경로가 존재하지 않는 경우
            if(connectedMap[start][end].cost==999){
                fprintf(fp,"from %d to %d cost infinite hops unreachable message %s",start,end,cMessage);
            }
            else{
                mid = start;
                fprintf(fp,"from %d to %d cost %d hops %d ",start,end,connectedMap[start][end].cost,start);
                while(connectedMap[mid][end].next!=end){
                    mid = connectedMap[mid][end].next;
                    fprintf(fp,"%d ",mid); 
                }
                fprintf(fp,"message %s",cMessage);
            }   
        }
        fprintf(fp,"\n");
        rewind(tf[1]);
        
    }

    for(int i=0;i<3;i++){
        fclose(tf[i]);
    }
    fclose(fp);

    printf("Complete. Output file written to output_dv.txt.\n");

    return 0;
}