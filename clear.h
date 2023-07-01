

#ifndef UNTITLED11_CLEAR_H
#define UNTITLED11_CLEAR_H

#include "instructions.h"
#include "RS.h"
#include "SLB.h"
#include "ROB.h"
#include "reg.h"
#include "BRANCH.h"
void clearins(){
    newinsq.L=1,newinsq.R=0,newinsq.size=0;
}
void clearRS(){
        for(int i=0;i<32;i++){
            newRS.s[i].busy=0;
            newRS.s[i].qj=newRS.s[i].qk=-1;
        }
};
void clearROB(){
    newROB.L=1,newROB.R=0,newROB.size=0;
    for(int i=0;i<32;i++)newROB.s[i].ready=0;
};
void clearSLB(){
    newSLB.L=1,newSLB.R=0,newSLB.size=0;
    SLcycle=0;
    for(int i=0;i<32;i++){
        newSLB.s[i].qj=newSLB.s[i].qk=-1;
    }
}
void clearreg(){
    for(int i=0;i<32;i++)
    {
        newreg[i].busy=0;
    }
}
void ClearAll(){
    clearins();
    clearRS();
    clearROB();
    clearSLB();
    clearreg();
    newending=0;
}
bool ifclear=0;
#endif //UNTITLED11_CLEAR_H
