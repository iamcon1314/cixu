
#ifndef UNTITLED11_INS_TO_DO_H
#define UNTITLED11_INS_TO_DO_H
#include "instructions.h"
#include "ROB.h"
#include "SLB.h"
#include "reg.h"
#include "RS.h"
void revise(int tmppp,Ins_node &tmp){
    newROB.s[tmppp].pc=tmp.pc;
    newROB.s[tmppp].inst=tmp.inst;
    newROB.s[tmppp].ordertype=tmp.ordertype;
    newROB.s[tmppp].ready=0;
}
void ins_to_run(){
    if(lastinsq.size==0)
    {
        return;
    }
    if(lastROB.size==32)
    {
        return;
    }
    Ins_node tmp=lastinsq.s[lastinsq.L];
    if(isLoad(tmp.ordertype)||isStore(tmp.ordertype))
    {
        if(lastSLB.size==32)return;
        int r=(lastSLB.R+1)%32;
        newSLB.R=r,newSLB.size++;
        int b=(lastROB.R+1)%32;
        newROB.R=b,newROB.size++;
        newinsq.L=(lastinsq.L+1)%32;
        newinsq.size--;
        Order order=Decode(tmp.inst);
        revise(b,tmp);
        newROB.s[b].dest=order.rd ;
        if(lastreg[order.rs1].busy){
            unsigned int h=lastreg[order.rs1].reorder;
            if(lastROB.s[h].ready)
            {
                newSLB.s[r].vj=lastROB.s[h].value,newSLB.s[r].qj=-1;
            }
            else
            {
                newSLB.s[r].qj=h;
            }
        }
        else
        {
            newSLB.s[r].vj=lastreg[order.rs1].reg,newSLB.s[r].qj=-1;
        }

        if(isStore(tmp.ordertype)){
            if(lastreg[order.rs2].busy){
                unsigned int h=lastreg[order.rs2].reorder;
                if(lastROB.s[h].ready)
                {
                    newSLB.s[r].vk=lastROB.s[h].value,newSLB.s[r].qk=-1;
                }
                else
                {
                    newSLB.s[r].qk=h;
                }
            }
            else
            {
                newSLB.s[r].vk=lastreg[order.rs2].reg,newSLB.s[r].qk=-1;
            }
        }
        else
        {
            newSLB.s[r].qk=-1;
        }
        newSLB.s[r].inst=tmp.inst ;
        newSLB.s[r].ordertype=tmp.ordertype;
        newSLB.s[r].pc=tmp.pc;
        newSLB.s[r].imm=order.imm ;
        newSLB.s[r].reorder=b;
        if(isStore(tmp.ordertype))
        {
            newSLB.s[r].ready=0;
        }
        if(!isStore(tmp.ordertype)){
            newreg[order.rd].reorder=b,newreg[order.rd].busy=1;
        }
    }
    else {
        int r=-1;
        for(int i=0;i<32;i++){
            if(!lastRS.s[i].busy){r=i;break;}
        }
        if(r==-1)return;
        int b=(lastROB.R+1)%32;
        newROB.R=b,newROB.size++;
        newinsq.L=(lastinsq.L+1)%32;
        newinsq.size--;
        Order order=Decode(tmp.inst);
        newROB.s[b].inst=tmp.inst, newROB.s[b].ordertype=tmp.ordertype;
        newROB.s[b].pc=tmp.pc, newROB.s[b].jumppc=tmp.jumppc , newROB.s[b].isjump=tmp.isjump;
        newROB.s[b].dest=order.rd , newROB.s[b].ready=0;
        if( (tmp.inst&0x7f)!=0x37&&(tmp.inst&0x7f)!=0x17 && (tmp.inst&0x7f)!=0x6f ){
            if(lastreg[order.rs1].busy){
                unsigned int h=lastreg[order.rs1].reorder;
                if(lastROB.s[h].ready){
                    newRS.s[r].vj=lastROB.s[h].value,newRS.s[r].qj=-1;
                }
                else newRS.s[r].qj=h;
            }
            else newRS.s[r].vj=lastreg[order.rs1].reg,newRS.s[r].qj=-1;
        }
        else newRS.s[r].qj=-1;
        if( (tmp.inst&0x7f)==0x33 || (tmp.inst&0x7f)==0x63){
            if(lastreg[order.rs2].busy){
                unsigned int h=lastreg[order.rs2].reorder;
                if(lastROB.s[h].ready)newRS.s[r].vk=lastROB.s[h].value,newRS.s[r].qk=-1;
                else newRS.s[r].qk=h;
            }
            else newRS.s[r].vk=lastreg[order.rs2].reg,newRS.s[r].qk=-1;
        }
        else newRS.s[r].qk=-1;
        newRS.s[r].inst=tmp.inst , newRS.s[r].ordertype=tmp.ordertype;
        newRS.s[r].pc=tmp.pc , newRS.s[r].jumppc=tmp.jumppc;
        newRS.s[r].imm=order.imm , newRS.s[r].reorder=b;
        newRS.s[r].busy=1;
        if((tmp.inst&0x7f)!=0x63)
        {
            newreg[order.rd].reorder=b,newreg[order.rd].busy=1;
        }
    }
}
#endif //UNTITLED11_INS_TO_DO_H
