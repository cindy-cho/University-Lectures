#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <vector>
#include <list>

using namespace std;

#define INF 2100000000

typedef struct{
    int next;
    int cost;
}data;

typedef struct{
    int start;
    int end;
    int cost;
}pqData;

//priority_queue 비교해주는 부분에서 tie-breaking rule2를 적용해주었다.
//Cost가 같을 경우는 ID가 작은 값을 가장 우선으로 return 한다.
struct compare{
    bool operator()(pqData A, pqData B){
        if(A.cost==B.cost) return A.end > B.end;
        return A.cost > B.cost;
    }
};

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
        printf("usage: linkstate topologyfile messagesfile changesfile\n");
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
    fp = fopen("output_ls.txt","w");

    int nodeSize,start,end,cost,mid;

    //Topology file에서 노드의 총 개수를 받아온다.
    fscanf(tf[0], "%d", &nodeSize);

    list<pqData> graph[nodeSize];
    vector<vector<data> > networkMap(nodeSize, vector<data> (nodeSize));
    priority_queue <pqData, vector<pqData>, compare> pq;
    list<pqData>::iterator it;
    pqData cur,tmp;

    //network연결 정보 초기화
    for(int i=0;i<nodeSize;i++){
        for(int j=0;j<nodeSize;j++){
            networkMap[i][j].next = j;
            networkMap[i][j].cost = INF;
        }
    }

    while(fscanf(tf[0],"%d %d %d",&start,&end,&cost)!=EOF){
        //network간의 연결정보를 저장하는 list에 값을 넣어준다.
        cur.start=start;
        cur.end=end;
        cur.cost=cost;
        graph[start].push_back(cur);
        cur.start=end;
        cur.end=start;
        graph[end].push_back(cur);
    }
    
    //다익스트라
    for(int i=0;i<nodeSize;i++){
        //자기자신은 0
        networkMap[i][i].cost=0;
        networkMap[i][i].next=i;
        cur.start=i;
        cur.end=i;
        cur.cost=0;
        pq.push(cur);
        while(!pq.empty()){
            cur = pq.top();
            pq.pop();
            it = graph[cur.end].begin();
            while(it!=graph[cur.end].end()){
                if(networkMap[i][(*it).end].cost > networkMap[i][cur.end].cost+(*it).cost){
                    networkMap[i][(*it).end].cost = networkMap[i][cur.end].cost+(*it).cost;
                    if(i==cur.end) networkMap[i][(*it).end].next = (*it).end;
                    else networkMap[i][(*it).end].next = networkMap[i][cur.end].next;
                    tmp.start=i;
                    tmp.end=(*it).end;
                    tmp.cost=networkMap[i][(*it).end].cost;
                    pq.push(tmp);
                }
                it++;
            }
        }
    }

    for(int i=0;i<nodeSize;i++){
        for(int j=0;j<nodeSize;j++){
            if(networkMap[i][j].cost!=INF) fprintf(fp,"%d %d %d\n",j,networkMap[i][j].next,networkMap[i][j].cost);
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
        if(networkMap[start][end].cost==INF){
            fprintf(fp,"from %d to %d cost infinite hops unreachable message %s",start,end,cMessage);
        }
        else{
            mid = start;
            fprintf(fp,"from %d to %d cost %d hops %d ",start,end,networkMap[start][end].cost,start);
            while(networkMap[mid][end].next!=end){
                mid = networkMap[mid][end].next;
                fprintf(fp,"%d ",mid); 
            }
            fprintf(fp,"message %s",cMessage);
        }
    }
    fprintf(fp,"\n");
    rewind(tf[1]);

    //changes.txt의 바뀐 노드들을 적용시킨다
    while(fscanf(tf[2],"%d %d %d",&start,&end,&cost)!=EOF){
        //list로 만들어진 값 업데이트
        //start list 업데이트
        it = graph[start].begin();
        int flag = 0;
        while(it != graph[start].end()){
            if((*it).end==end) {
                flag = 1;
                //-999면 연결이 끊긴 거여서 list에서 지워준다.
                if(cost==-999) graph[start].erase(it++);
                //반대의 경우에는 cost값을 업데이트
                else {
                    (*it).cost=cost;
                    it++;
                }
            }
            else it++;
        }
        //flag 가 0 인 경우에는 새롭게 노드가 추가된 것이므로
        if(flag==0){
            tmp.start=start;
            tmp.end=end;
            tmp.cost=cost;
            graph[start].push_back(tmp); //새롭게 노드를 추가해준다.
        }
        
        flag = 0;
        //end list 업데이트
        it = graph[end].begin();
        while(it != graph[end].end()){
            if((*it).end==start) {
                flag = 1;
                //-999면 연결이 끊긴 거여서 list에서 지워준다.
                if(cost==-999) graph[end].erase(it++);
                //반대의 경우에는 cost값을 업데이트
                else {
                    (*it).cost=cost;
                    it++;
                }
            }
            else it++;
        }

        //flag 가 0 인 경우에는 새롭게 노드가 추가된 것이므로
        if(flag==0){
            tmp.start=end;
            tmp.end=start;
            tmp.cost=cost;
            graph[end].push_back(tmp); //새롭게 노드를 추가해준다.
        }

        for(int i=0;i<nodeSize;i++){
            for(int j=0;j<nodeSize;j++) {
                networkMap[i][j].cost=INF;
                networkMap[i][j].next=j;
            }
        }

        //다익스트라
        for(int i=0;i<nodeSize;i++){
            //자기자신은 0
            networkMap[i][i].cost=0;
            networkMap[i][i].next=i;
            cur.start=i;
            cur.end=i;
            cur.cost=0;
            pq.push(cur);
            while(!pq.empty()){
                cur = pq.top();
                pq.pop();
                it = graph[cur.end].begin();
                while(it!=graph[cur.end].end()){
                    if(networkMap[i][(*it).end].cost > networkMap[i][cur.end].cost+(*it).cost){
                        networkMap[i][(*it).end].cost = networkMap[i][cur.end].cost+(*it).cost;
                        if(i==cur.end) networkMap[i][(*it).end].next = (*it).end;
                        else networkMap[i][(*it).end].next = networkMap[i][cur.end].next;
                        tmp.start=i;
                        tmp.end=(*it).end;
                        tmp.cost=networkMap[i][(*it).end].cost;
                        pq.push(tmp);
                    }
                    it++;
                }
            }
        }


        for(int i=0;i<nodeSize;i++){
            for(int j=0;j<nodeSize;j++){
                if(networkMap[i][j].cost!=INF) fprintf(fp,"%d %d %d\n",j,networkMap[i][j].next,networkMap[i][j].cost);
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
            if(networkMap[start][end].cost==INF){
                fprintf(fp,"from %d to %d cost infinite hops unreachable message %s",start,end,cMessage);
            }
            else{
                mid = start;
                fprintf(fp,"from %d to %d cost %d hops %d ",start,end,networkMap[start][end].cost,start);
                while(networkMap[mid][end].next!=end){
                    mid = networkMap[mid][end].next;
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

    printf("Complete. Output file written to output_ls.txt.\n");

    return 0;
}