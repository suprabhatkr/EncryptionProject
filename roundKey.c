#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
char binaryKey[257]="\0",binaryMsg[129]="\0";
char toHexArray[16][5];
char message[33]="\0";
char k1[65]="\0",k2[65]="\0";
char code[4]="0000",hexMsg[33]="\0";
char sum[4][65];
char IV[65];
char s1[33],s2[33],s3[33],p1[33],p2[33],p3[33];
FILE *fptr,*encoderfptr; 
void increment(){
    for(int i=3;i>=0;i--){
        if(code[i]=='0'){
            code[i]='1';
            break;
        }
        else if(code[i]=='1'){
            code[i]='0';
        }
    }
}
void copy32(char a1[],char a2[]){
    for(int i=0;i<32;i++){
        a2[i]=a1[i];
    }
}
void copy64(char a1[],char a2[]){
    for(int i=0;i<64;i++){
        a2[i]=a1[i];
    }
}
void printing128bit(char k[]){
    for(int i=0;i<128;i++){
        fprintf(fptr,"%c",k[i]);
    }
    fprintf(fptr,"\n");
}
void printing64bit(char k[]){
    for(int i=0;i<64;i++){
        fprintf(fptr,"%c",k[i]);
    }
    fprintf(fptr,"\n");
}
void printing32bit(char k[]){
    for(int i=0;i<32;i++){
        fprintf(fptr,"%c",k[i]);
    }
    fprintf(fptr,"\n");
}
void printingPartkey(char mat[][8]){
    for(int k=0;k<8;k++){
        for(int l=0;l<8;l++){
            fprintf(fptr,"%c",mat[k][l]);
        }
    }
    fprintf(fptr,"\n");
}
void printingMatrix(char mat[][8]){
    for(int k=0;k<8;k++){
        for(int l=0;l<8;l++){
            fprintf(fptr,"%c ",mat[k][l]);
        }
        fprintf(fptr,"\n");
    }
}
void bintohexPrnt(){
    char unit[5]="\0";
    for(int i=0;i<32;i++){
        for(int j=0;j<4;j++){
            unit[j]=message[i*4+j];
        }
        unit[4]='\0';
        if(strcmp(unit,"0000")==0)
            hexMsg[i]='0';
        else if(strcmp(unit,"0001")==0)
            hexMsg[i]='1';
        else if(strcmp(unit,"0010")==0)
            hexMsg[i]='2';
        else if(strcmp(unit,"0011")==0)
            hexMsg[i]='3';
        else if(strcmp(unit,"0100")==0)
            hexMsg[i]='4';
        else if(strcmp(unit,"0101")==0)
            hexMsg[i]='5';
        else if(strcmp(unit,"0110")==0)
            hexMsg[i]='6';
        else if(strcmp(unit,"0111")==0)
            hexMsg[i]='7';
        else if(strcmp(unit,"1000")==0)
            hexMsg[i]='8';
        else if(strcmp(unit,"1001")==0)
            hexMsg[i]='9';
        else if(strcmp(unit,"1010")==0)
            hexMsg[i]='a';
        else if(strcmp(unit,"1011")==0)
            hexMsg[i]='b';
        else if(strcmp(unit,"1100")==0)
            hexMsg[i]='c';
        else if(strcmp(unit,"1101")==0)
            hexMsg[i]='d';
        else if(strcmp(unit,"1110")==0)
            hexMsg[i]='e';
        else if(strcmp(unit,"1111")==0)
            hexMsg[i]='f';
    }
    //fprintf(fptr,"hexmessage%s\n",hexMsg);
}
void bintohexPrntk1(){
    char unit[5]="\0";
    for(int i=0;i<32;i++){
        for(int j=0;j<4;j++){
            unit[j]=k1[i*4+j];
        }
        unit[4]='\0';
        if(strcmp(unit,"0000")==0)
            hexMsg[i]='0';
        else if(strcmp(unit,"0001")==0)
            hexMsg[i]='1';
        else if(strcmp(unit,"0010")==0)
            hexMsg[i]='2';
        else if(strcmp(unit,"0011")==0)
            hexMsg[i]='3';
        else if(strcmp(unit,"0100")==0)
            hexMsg[i]='4';
        else if(strcmp(unit,"0101")==0)
            hexMsg[i]='5';
        else if(strcmp(unit,"0110")==0)
            hexMsg[i]='6';
        else if(strcmp(unit,"0111")==0)
            hexMsg[i]='7';
        else if(strcmp(unit,"1000")==0)
            hexMsg[i]='8';
        else if(strcmp(unit,"1001")==0)
            hexMsg[i]='9';
        else if(strcmp(unit,"1010")==0)
            hexMsg[i]='a';
        else if(strcmp(unit,"1011")==0)
            hexMsg[i]='b';
        else if(strcmp(unit,"1100")==0)
            hexMsg[i]='c';
        else if(strcmp(unit,"1101")==0)
            hexMsg[i]='d';
        else if(strcmp(unit,"1110")==0)
            hexMsg[i]='e';
        else if(strcmp(unit,"1111")==0)
            hexMsg[i]='f';
    }
    fprintf(fptr,"%s\n",hexMsg);
}
int toint(char c){
    if((int)c>=48 && (int)c<=57){
        return (int)c-48;
    }
    else{
        return (int)c-97+10;
    }
}
void initialiseHexArray(){
    for(int i=0;i<16;i++){
        for(int j=0;j<4;j++){
            toHexArray[i][j]=code[j];
        }
        toHexArray[i][4]='\0';
        increment();
    }
}
char* toBin(char c){
    if(c>='0' && c<='9'){
        return toHexArray[(int)c-48];;
    }
    else{
        return toHexArray[(int)c-87];
    }
}
void getBinaryMessage(char message[]){
    initialiseHexArray();
    for(int i=0;i<32;i++){
        char* tempKey=toBin(message[i]);
        strcat(binaryMsg,tempKey);
    }
    binaryMsg[128]='\0';
}
void getBinaryKey(char key[]){
    initialiseHexArray();
    for(int i=0;i<64;i++){
        char* tempKey=toBin(key[i]);
        strcat(binaryKey,tempKey);
    }
    binaryKey[256]='\0';
}
void verticalShift(char partKey[][8]){
    int temp[8];
    for(int i=0;i<8;i++){
        temp[i]=partKey[7][i];
    }
    for(int i=6;i>=0;i--){
        for(int j=0;j<8;j++){
            partKey[i+1][j]=partKey[i][j];
        }
    }
    for(int i=0;i<8;i++){
        partKey[0][i]=temp[i];
    }
}
void horizontalShift(char partKey[][8]){
    int temp[8];
    for(int i=0;i<8;i++){
        temp[i]=partKey[i][7];
    }
    for(int i=6;i>=0;i--){
        for(int j=0;j<8;j++){
            partKey[j][i+1]=partKey[j][i];
        }
    }
    for(int i=0;i<8;i++){
        partKey[i][0]=temp[i];
    }
}
void rotation(char partKey[][8],char code[]){
    if(code[0]=='1')
        horizontalShift(partKey);
    if(code[1]=='1')
        verticalShift(partKey);
    if(code[2]=='1')
        horizontalShift(partKey);
    if(code[3]=='1')
        verticalShift(partKey);
}
void Xor(char partKey1[][8],char partKey2[][8],char generatedKey[]){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(partKey1[i][j]==partKey2[i][j])
                generatedKey[i*8+j]='0';
            else
                generatedKey[i*8+j]='1';
        }
    }
}
void stringXor(char s1[],char s2[]){
    for(int i=0;i<64;i++){
        if(s1[i]==s2[i])
            s1[i]='0';
        else
            s1[i]='1';
    }
    s1[64]='\0';
}
void stringXor32(char s1[],char s2[]){
    for(int i=0;i<32;i++){
        if(s1[i]==s2[i])
            s1[i]='0';
        else
            s1[i]='1';
    }
    s1[64]='\0';
}
void roundKeyGeneration(){
    char partKey[4][8][8];//for dividing key into four parts;
    //printf("%s\n",binaryKey);
    int keyIndex=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            for(int k=0;k<8;k++){
                partKey[i][j][k]=binaryKey[i*64+j*8+k];
                keyIndex++;
            }
        }
    }
    for(int i=0;i<4;i++){
        code[0]='1';code[1]='0';code[2]='0';code[3]='0';
        // fprintf(fptr,"partkey%d : ",i);
        // printingPartkey(partKey[i]);
        for(int j=0;j<4;j++){
            rotation(partKey[i],code);
            // fprintf(fptr,"code=%s\n",code);
            // printingMatrix(partKey[i]);
            increment();
        }
        code[0]='1';code[1]='1';code[2]='0';code[3]='0';
        for(int j=0;j<4;j++){
            rotation(partKey[i],code);
            // fprintf(fptr,"code=%s\n",code);
            // printingMatrix(partKey[i]);
            increment();
        }
        char tempkey[64];
        for(int j=0;j<8;j++){
            for(int k=0;k<8;k++){
                tempkey[j*8+k]=partKey[i][j][k];
                keyIndex++;
            }
        }
        // fprintf(fptr,"genkey%i : ",i);
        // printing64bit(tempkey);
    }
    //xor of partkey0 and partkey1 will store in k1
    Xor(partKey[0],partKey[1],k1);
    // fprintf(fptr,"k1 : ");
    // printing64bit(k1);
    Xor(partKey[2],partKey[3],k2);
    // fprintf(fptr,"k1 : ");
    // printing64bit(k2);
}
void additionModulo32(char s1[],char s2[],char sm[]){
    char carry='0';
    for(int i=31;i>=0;i--){
        if(carry=='1'){
            if(s1[i]=='1' && s2[i]=='1'){
                sm[i]='1';
                carry='1';
            }
            else if(s1[i]!=s2[i]){
                sm[i]='0';
                carry='1';
            }
            else{
                sm[i]='1';
                carry='0';
            }
        }
        else{
            if(s1[i]=='1' && s2[i]=='1'){
                sm[i]='0';
                carry='1';
            }
            else if(s1[i]!=s2[i]){
                sm[i]='1';
                carry='0';
            }
            else{
                sm[i]='0';
                carry='0';
            }
        }
    }
}
void additionModulo64(char s1[],char s2[],char sm[]){
    char carry='0';
    for(int i=63;i>=0;i--){
        if(carry=='1'){
            if(s1[i]=='1' && s2[i]=='1'){
                sm[i]='1';
                carry='1';
            }
            else if(s1[i]!=s2[i]){
                sm[i]='0';
                carry='1';
            }
            else{
                sm[i]='1';
                carry='0';
            }
        }
        else{
            if(s1[i]=='1' && s2[i]=='1'){
                sm[i]='0';
                carry='1';
            }
            else if(s1[i]!=s2[i]){
                sm[i]='1';
                carry='0';
            }
            else{
                sm[i]='0';
                carry='0';
            }
        }
    }
}
int new_encode(){
    char partMsg[4][33],expandMsg[4][65];
    fprintf(encoderfptr,"original message = %s\n",binaryMsg);
    for(int i=0;i<4;i++){
        for(int j=0;j<32;j++){
            partMsg[i][j]=binaryMsg[i*32+j];
        }
        partMsg[i][32]='\0';
        fprintf(encoderfptr,"part message %d = %s\n",i+1,partMsg[i]);
    } 
    copy32(s1,partMsg[0]);
    copy32(s2,partMsg[1]);
    copy32(s3,partMsg[2]); 
    stringXor32(s1,partMsg[2]);
    stringXor32(s1,partMsg[3]);
    stringXor32(s2,partMsg[0]);
    stringXor32(s2,partMsg[2]);
    stringXor32(s3,partMsg[1]);
    stringXor32(s3,partMsg[3]);
    fprintf(encoderfptr,"msg_1 = %s\n",s1);
    fprintf(encoderfptr,"msg_2 = %s\n",s2);
    fprintf(encoderfptr,"msg_3 = %s\n",s3);
    int parity1=0,parity2=0,parity3=0,parity; 
    for(int i=0;i<32;i++){
        if (s1[i]=='1'){
            parity1=parity1^1;
        }
    }
    fprintf(encoderfptr,"parity 1 = %d\n",parity1);
    for(int i=0;i<32;i++){
        if (s2[i]=='1'){
            parity2=parity2^1;
        }
    }
    fprintf(encoderfptr,"parity 2 = %d\n",parity2);
    for(int i=0;i<32;i++){
        if (s2[i]=='1'){
            parity3=parity3^1;
        }
    }
    fprintf(encoderfptr,"parity 3 = %d\n",parity3);
    parity=parity1^parity2^parity3;
    fprintf(encoderfptr,"final parity = %d\n",parity);
    return parity;
}
void eachRound(){
    char partMsg[4][33],expandMsg[4][65];
    for(int i=0;i<4;i++){
        for(int j=0;j<32;j++){
            partMsg[i][j]=binaryMsg[i*32+j];
        }
        partMsg[i][32]='\0';
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<16;j++){
            expandMsg[i][j]=partMsg[i][j+16];
        }
        for(int j=0;j<32;j++){
            if(partMsg[i][j]=='0')
                expandMsg[i][j+16]='1';
            else
                expandMsg[i][j+16]='0';
        }
        for(int j=0;j<16;j++){
            expandMsg[i][j+48]=partMsg[i][j];
        }
        expandMsg[i][64]='\0';
    }
    // for(int i=0;i<4;i++){
    //     fprintf(fptr,"message_part%d : ",i);
    //     printing32bit(partMsg[i]);
    //     fprintf(fptr,"expand_msg%d : ",i);
    //     printing64bit(expandMsg[i]);
    // }
    strcpy(IV,"0000000100100011010001010110011110001001101010111100110111101111");
    for (int i=0;i<4;i++){
        additionModulo64(expandMsg[i],IV,sum[i]);
        copy64(sum[i],IV);
    }
    // fprintf(fptr,"B1 : ");
    // printing64bit(sum[0]);
    // fprintf(fptr,"B2 : ");
    // printing64bit(sum[1]);
    //xor of k1 and sum0 will be store in sum[0]
    stringXor(sum[0],sum[1]);
    stringXor(sum[2],sum[3]);
    stringXor(sum[0],k1);
    stringXor(sum[2],k2);
    copy64(sum[1],sum[2]);
    // fprintf(fptr,"half_message 1 : ");
    // printing64bit(sum[0]);
    // fprintf(fptr,"half_message 2 : ");
    // printing64bit(sum[1]);
    for(int i=0;i<2;i++){
        for(int j=0;j<64;j++){
            binaryMsg[i*64+j]=sum[i][j];
        }
    }
    // fprintf(fptr,"encrypted message : ");
}
void shuffleKey(){
    char temp[8]="\0";
    for(int i=0;i<8;i++){
        temp[i]=binaryKey[i];
    }
    for(int i=0;i<248;i++){
        binaryKey[i]=binaryKey[i+4];
    }
    for(int i=0;i<8;i++){
        binaryKey[i+248]=temp[i];
    }
}
void encryption(){
    eachRound();
    fprintf(fptr,"%s\n",binaryMsg);
    //bintohexPrnt();
}
int main(){
    fptr = fopen("hexout.txt","w+");
    encoderfptr = fopen("encodeout.txt","w+");
    clock_t start_t,end_t;
    char key[]="0123abcdefabcdeffedcba98765432100123456789abcdef0246813579abcdef";
    double timeElapsed=0.0;
    time_t begin=time(NULL);
    printf("enter the messages : ");
    for (int i=0;i<32;i++){
        scanf("%c",&message[i]);
    }
    start_t = clock();
    getBinaryKey(key);
    // fprintf(fptr,"original key : %s,\n",binaryKey);
    getBinaryMessage(message);
    new_encode();
    // fprintf(fptr,"original message : %s\n",binaryMsg);
    for(int i=0;i<32;i++){
        fprintf(fptr,"%d\n",i);
        fprintf(fptr,"%s\n",binaryMsg);
        // fprintf(fptr,"Round %d begin.............................................\n",i);
        bintohexPrnt();
        fprintf(fptr,"%s\n",binaryKey);
        roundKeyGeneration();
        shuffleKey();
        //printf("k1=%s\nk2=%s\n",k1,k2);
        //bintohexPrnt();
        encryption();
    }
    end_t = clock();
    printf("%f",end_t-start_t);
    return 0;
}