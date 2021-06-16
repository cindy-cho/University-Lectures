#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

// string caculateModulo2(string A, string B){

// }
int main(int argc, char *argv[]){
    //프로그램에 들어갈 인자 : input_file / output_file / generator / dataword_size

    //인자의 수가 맞지 않을 경우
    if(argc!=5){
        printf("usage: ./crc_encoder input_file output_file generator dataword_size\n");
        return 0;
    }

    //input_file open
    FILE *fop = fopen(argv[1],"rb");
    if(fop == NULL){
        printf("input file open error.\n");
        return 0;
    }

    //output_file open
    FILE *fcs = fopen(argv[2],"w");
    if(fcs == NULL){
        printf("output file open error.\n");
        return 0;
    }

    int datawordSize = argv[4][0]-'0';

    //dataword size check
    if(datawordSize!=4 && datawordSize!=8){
        printf("dataword size must be 4 or 8\n");
        return 0;
    }
    printf("\n");
    
    fseek(fop,0,SEEK_END);
    int fSize = ftell(fop); //input file size 확인
    fseek(fop,0,SEEK_SET);
    string generator = argv[3];
    int generatorSize = generator.length();
    vector<int> content(fSize);
    int outputSize = fSize*(8/datawordSize)*(datawordSize+generatorSize);
    int paddingSize = datawordSize - (outputSize%datawordSize);
    printf("outputSize : %d\n",outputSize);
    printf("paddingSize : %d\n",paddingSize);
    // vector<int> outputContent((fSize*(8/datawordSize)*(datawordSize+)))
    for(int i=0;i<fSize;i++){
        content[i] = fgetc(fop);
    }
    
    fclose(fop);
    fclose(fcs);
    
    
    
    return 0;
}       