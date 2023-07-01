

#ifndef UNTITLED11_SLB_H
#define UNTITLED11_SLB_H

#include "instructions.h"

class SLB_node{
public:
    instype ordertype;
    unsigned int inst,pc,vj,vk,qj,qk,imm,reorder;
    bool ready;
};
class SLB{
public:
    SLB_node s[32];
    int L=1,R=0,size=0;
}lastSLB,newSLB;
unsigned int SLcycle=0;

void Loading(SLB_node tmp,unsigned int &value) {
    switch (tmp.ordertype) {
        case LB: {
            int pos = tmp.vj + tmp.imm;
            value = (char) insmem[pos];
        }
            break;
        case LH: {
            int pos = tmp.vj + tmp.imm;
            value = (short) ((unsigned short) insmem[pos] + ((unsigned short) insmem[pos + 1] << 8));
        }
            break;
        case LW: {
            int pos = tmp.vj + tmp.imm;
            value = (int) ((unsigned int) insmem[pos] + ((unsigned int) insmem[pos + 1] << 8) +
                           ((unsigned int) insmem[pos + 2] << 16) + ((unsigned int) insmem[pos + 3] << 24));
        }
            break;
        case LBU: {
            int pos = tmp.vj + tmp.imm;
            value = insmem[pos];
        }
            break;
        case LHU: {
            int pos = tmp.vj + tmp.imm;
            value = (unsigned short) insmem[pos] + ((unsigned short) insmem[pos + 1] << 8);
        }
            break;
    }
}
void Storing(SLB_node tmp) {
    switch (tmp.ordertype) {
        case SB: {
            int pos = tmp.vj + tmp.imm;
            insmem[pos] = tmp.vk & 0xff;
        }
            break;
        case SH: {
            int pos = tmp.vj + tmp.imm;
            insmem[pos] = tmp.vk & 0xff, insmem[pos + 1] = (tmp.vk >> 8) & 0xff;
        }
            break;
        case SW: {
            int pos = tmp.vj + tmp.imm;
            insmem[pos] = tmp.vk & 0xff, insmem[pos + 1] = (tmp.vk >> 8) & 0xff, insmem[pos + 2] = (tmp.vk >> 16) & 0xff, insmem[
                    pos + 3] = (tmp.vk >> 24) & 0xff;
        }
            break;

    }
}

#endif //UNTITLED11_SLB_H
