//
// Created by 陆鹏睿 on 2023/7/1.
//

#ifndef UNTITLED11_ROB_TO_RUN_H
#define UNTITLED11_ROB_TO_RUN_H

#include "ROB.h"
#include "little.h"
#include "reg.h"
#include "RS.h"
#include "SLB.h"
#include "clear.h"
#include "debug.h"

void run_ROB(){
    if(!lastROB.size)return;
    int b=lastROB.L;

    if(isBranch(lastROB.s[b].ordertype)){
        if(!lastROB.s[b].ready)return;
        OKnum++;
        newROB.size--,newROB.L=(lastROB.L+1)%32;
        if(lastROB.s[b].ordertype==JAL){
            int rd=lastROB.s[b].dest;
            newreg[rd].reg=lastROB.s[b].value;
            if(lastreg[rd].busy&&lastreg[rd].reorder==b)
            {
                newreg[rd].busy=0;
            }
            for(int j=0;j<32;j++){
                if(lastRS.s[j].busy){
                    if(lastRS.s[j].qj==b)
                    {
                        newRS.s[j].qj=-1,newRS.s[j].vj=lastROB.s[b].value;
                    }
                    if(lastRS.s[j].qk==b)
                    {
                        newRS.s[j].qk=-1,newRS.s[j].vk=lastROB.s[b].value;
                    }
                }
            }
            for(int j=0;j<32;j++){
                if(lastSLB.s[j].qj==b)
                {
                    newSLB.s[j].qj=-1,newSLB.s[j].vj=lastROB.s[b].value;
                }
                if(lastSLB.s[j].qk==b)
                {
                    newSLB.s[j].qk=-1,newSLB.s[j].vk=lastROB.s[b].value;
                }
            }
        }
        else {
            if(lastROB.s[b].ordertype!=JALR)
            {
                predictTot++;
            }
            if( (lastROB.s[b].value^lastROB.s[b].isjump)==1 || lastROB.s[b].ordertype==JALR){//预测失败

                int x=lastROB.s[b].inst&0xfff;
                if(lastBT[x].pan[0]==0&&lastBT[x].pan[1]==0)
                {
                    newBT[x].pan[0]=0,newBT[x].pan[1]=1;
                }
                if(lastBT[x].pan[0]==0&&lastBT[x].pan[1]==1)

                {
                    newBT[x].pan[0]=1,newBT[x].pan[1]=0;
                }
                if(lastBT[x].pan[0]==1&&lastBT[x].pan[1]==0)
                {
                    newBT[x].pan[0]=0,newBT[x].pan[1]=1;
                }
                if(lastBT[x].pan[0]==1&&lastBT[x].pan[1]==1)
                {
                    newBT[x].pan[0]=1,newBT[x].pan[1]=0;
                }
                update_BHT_id=x;

                if(lastROB.s[b].value)
                {
                    newpc=lastROB.s[b].jumppc;
                }
                else
                {
                    newpc=lastROB.s[b].pc+4;
                }
                ifclear=1;
                if(lastROB.s[b].ordertype==JALR){
                    int rd=lastROB.s[b].dest;
                    newreg[rd].reg=lastROB.s[b].value;
                    if(lastreg[rd].busy&&lastreg[rd].reorder==b)
                    {
                        newreg[rd].busy=0;
                    }

                }
                return;
            }
            else {
                predictSuccess++;
                int x=lastROB.s[b].inst&0xfff;
                if(lastBT[x].pan[0]==0&&lastBT[x].pan[1]==0)
                {
                    newBT[x].pan[0]=0,newBT[x].pan[1]=0;
                }
                if(lastBT[x].pan[0]==0&&lastBT[x].pan[1]==1)
                {
                    newBT[x].pan[0]=0,newBT[x].pan[1]=0;
                }
                if(lastBT[x].pan[0]==1&&lastBT[x].pan[1]==0)
                {
                    newBT[x].pan[0]=1,newBT[x].pan[1]=1;
                }
                if(lastBT[x].pan[0]==1&&lastBT[x].pan[1]==1)
                {
                    newBT[x].pan[0]=1,newBT[x].pan[1]=1;
                }
                update_BHT_id=x;
                return;
            }
        }
    }
    else if(isStore(lastROB.s[b].ordertype)){
        if(!lastROB.s[b].ready){
            for(int i=0;i<32;i++){
                if(lastSLB.s[i].reorder==b){
                    newSLB.s[i].ready=1;
                }
            }
            return;
        }
        OKnum++;
        newROB.size--,newROB.L=(lastROB.L+1)%32;
        return;
    }
    else {
        if(!lastROB.s[b].ready)return;
        OKnum++;
        newROB.size--,newROB.L=(lastROB.L+1)%32;
        int rd=lastROB.s[b].dest;
        newreg[rd].reg=lastROB.s[b].value;
        if(lastreg[rd].busy&&lastreg[rd].reorder==b) {
            newreg[rd].busy = 0;
        }
        for(int j=0;j<32;j++){
            if(lastRS.s[j].busy){
                if(lastRS.s[j].qj==b) {
                    newRS.s[j].qj = -1, newRS.s[j].vj = lastROB.s[b].value;
                }
                if(lastRS.s[j].qk==b) {
                    newRS.s[j].qk = -1, newRS.s[j].vk = lastROB.s[b].value;
                }
            }
        }
        for(int j=0;j<32;j++){
            if(lastSLB.s[j].qj==b)
            {
                newSLB.s[j].qj = -1, newSLB.s[j].vj = lastROB.s[b].value;
            }
            if(lastSLB.s[j].qk==b)
            {
                newSLB.s[j].qk = -1, newSLB.s[j].vk = lastROB.s[b].value;
            }
        }
        return;
    }
}
#endif //UNTITLED11_ROB_TO_RUN_H
