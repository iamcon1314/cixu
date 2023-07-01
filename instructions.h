#ifndef UNTITLED11_INSTRUCTIONS_H
#define UNTITLED11_INSTRUCTIONS_H


#include "BRANCH.h"
#include "order.h"
#include "instype.h"
#include "judgeinstype.h"
#include "little.h"

unsigned int newpc;
unsigned int lastpc;
unsigned char insmem[500000];
class Ins_node{
public:
    unsigned int inst,pc,jumppc;
    bool isjump;
    instype ordertype;
};
class Insturction_Queue{
public:
    Ins_node s[32];
    int L=1,R=0,size=0;
}lastinsq,newinsq;

void getinss(){
    if(lastinsq.size==32)return;
    unsigned int s=(unsigned int)insmem[lastpc]+((unsigned int)insmem[lastpc+1]<<8)+((unsigned int)insmem[lastpc+2]<<16)+((unsigned int)insmem[lastpc+3]<<24);
    Order order=Decode(s,1);
    if(order.type==END){newending=1;return;}
    Ins_node tmp;
    tmp.inst=s,tmp.ordertype=order.type,tmp.pc=lastpc;
    if(isBranch(order.type)){
        if(order.type==JAL) {
            newpc= lastpc + order.imm;
            int debug=9;
            debug+=1;
        }
        else {
            if(order.type==JALR)newpc=lastpc+4;
            else {

                tmp.jumppc=lastpc+order.imm;
                if(BranchJudge(tmp.inst&0xfff))newpc=lastpc+order.imm,tmp.isjump=1;
                else newpc=lastpc+4,tmp.isjump=0;
            }
        }
    }
    else newpc=lastpc+4;
    int g=(lastinsq.R+1)%32;
    newinsq.R=g;
    newinsq.s[g]=tmp;
    newinsq.size++;
}
#endif //UNTITLED11_INSTRUCTIONS_H
