
#ifndef UNTITLED11_INITIAL_H
#define UNTITLED11_INITIAL_H

#include "RS.h"
#include "SLB.h"
#include "debug.h"

unsigned int getins(char *s, int l, int r);

void init(){
    for(int i=0;i<32;i++){
        newRS.s[i].qj=newRS.s[i].qk=-1;
        lastRS.s[i].qj=lastRS.s[i].qk=-1;
    }
    for(int i=0;i<32;i++){
        newSLB.s[i].qj=newSLB.s[i].qk=-1;
        lastSLB.s[i].qj=lastSLB.s[i].qk=-1;
    }
    waiting();
    char tmp[20];
    int pos;
    while(~scanf("%s",tmp)) {
        if (tmp[0] == '@')pos = getins(tmp, 1, strlen(tmp) - 1);
        else {
            insmem[pos] =getins(tmp, 0, strlen(tmp) - 1);
            pos++;
        }
    }
}

unsigned int getins(char *s, int l, int r) {
    unsigned int tmppp=0;
    for(int i=l;i<=r;i++){
        if(s[i]>='0'&&s[i]<='9')
        {
            tmppp=(tmppp<<4)|(s[i]-'0');
        }
        else
        {
            tmppp=(tmppp<<4)|(s[i]-'A'+10);
        }
    }
    return tmppp;
}

#endif //UNTITLED11_INITIAL_H
