

#ifndef UNTITLED11_UPDATING_H
#define UNTITLED11_UPDATING_H

#include "reg.h"
#include "instructions.h"
#include "RS.h"
#include "SLB.h"
#include "ROB.h"

void updating(){

    for(int i=0;i<32;i++)
    {
        lastreg[i]=newreg[i];
    }
    lastreg[0].reg=0,lastreg[0].busy=0;//0号寄存器强制为0
    lastinsq=newinsq;
    lastRS=newRS;
    lastSLB=newSLB;
    lastROB=newROB;
    lastBT[update_BHT_id]=newBT[update_BHT_id];

}
#endif //UNTITLED11_UPDATING_H
