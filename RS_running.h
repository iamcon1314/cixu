

#ifndef UNTITLED11_RS_RUNNING_H
#define UNTITLED11_RS_RUNNING_H

#include "RS.h"
#include "ROB.h"
#include "SLB.h"
#include "ALU.h"

void RS_exu(){
    for(int i=0;i<32;i++){
        if(lastRS.s[i].busy&&lastRS.s[i].qj==-1&&lastRS.s[i].qk==-1)
        {
            unsigned value,jumppc;
            do_ALU(lastRS.s[i],value,jumppc);
            int b=lastRS.s[i].reorder;

            newROB.s[b].value=value , newROB.s[b].ready=1;
            if(lastRS.s[i].ordertype==JALR)
            {
                newROB.s[b].jumppc = jumppc;
            }
            newRS.s[i].busy=0;
            for(int j=0;j<32;j++){
                if(lastRS.s[j].busy){
                    if(lastRS.s[j].qj==b)
                    {
                        newRS.s[j].qj = -1, newRS.s[j].vj = value;
                    }
                    if(lastRS.s[j].qk==b)
                    {
                        newRS.s[j].qk=-1,newRS.s[j].vk=value;
                    }
                }
            }
            for(int j=0;j<32;j++){
                if(lastSLB.s[j].qj==b)
                {
                    newSLB.s[j].qj=-1,newSLB.s[j].vj=value;
                }
                if(lastSLB.s[j].qk==b)
                {
                    newSLB.s[j].qk=-1,newSLB.s[j].vk=value;
                }
            }
            break;
        }
    }
}
#endif //UNTITLED11_RS_RUNNING_H
