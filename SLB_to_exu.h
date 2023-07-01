
#ifndef UNTITLED11_SLB_TO_EXU_H
#define UNTITLED11_SLB_TO_EXU_H

#include "SLB.h"
#include "ROB.h"
#include "RS.h"

void SLB_runing(){
    if(SLcycle){
        SLcycle--;
        if(SLcycle==0){

            int r=lastSLB.L;
            if(isLoad(lastSLB.s[r].ordertype)){
                unsigned int loadvalue;

                Loading(lastSLB.s[r],loadvalue);
                int b=lastSLB.s[r].reorder;
                newROB.s[b].value=loadvalue , newROB.s[b].ready=1;
                for(int j=0;j<32;j++){
                    if(lastRS.s[j].busy){
                        if(lastRS.s[j].qj==b)
                        {
                            newRS.s[j].qj=-1,newRS.s[j].vj=loadvalue;
                        }
                        if(lastRS.s[j].qk==b)
                        {
                            newRS.s[j].qk=-1,newRS.s[j].vk=loadvalue;
                        }
                    }
                }
                newSLB.size--,newSLB.L=(lastSLB.L+1)%32;
                newSLB.s[lastSLB.L].qj=-1,newSLB.s[lastSLB.L].qk=-1;
                for(int j=0;j<32;j++){
                    if(lastSLB.s[j].qj==b)newSLB.s[j].qj=-1,newSLB.s[j].vj=loadvalue;
                    if(lastSLB.s[j].qk==b){
                        newSLB.s[j].qk=-1,newSLB.s[j].vk=loadvalue;
                    }
                }
            }
            else {
                int b=lastSLB.s[r].reorder;
                newROB.s[b].ready=1;
                newSLB.size--,newSLB.L=(lastSLB.L+1)%32;
                newSLB.s[lastSLB.L].qj=-1,newSLB.s[lastSLB.L].qk=-1;
                Storing(lastSLB.s[r]);
            }
        }
        return;
    }
    if(!lastSLB.size)return;
    int r=lastSLB.L;
    if(isLoad(lastSLB.s[r].ordertype)){
        if(lastSLB.s[r].qj==-1){
            SLcycle=3;
        }
    }
    else {
        if(lastSLB.s[r].qj==-1&&lastSLB.s[r].qk==-1&&lastSLB.s[r].ready){
            SLcycle=3;
        }
    }
}
#endif //UNTITLED11_SLB_TO_EXU_H
