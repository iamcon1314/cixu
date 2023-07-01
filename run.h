#ifndef UNTITLED11_RUN_H
#define UNTITLED11_RUN_H
#include "initial.h"
#include "bits/stdc++.h"
#include "order.h"
#include "BRANCH.h"
#include "judgeinstype.h"
#include "ROB.h"
#include "reg.h"
#include "ALU.h"
#include "clear.h"
#include "instructions.h"
#include "ins_to_do.h"
#include "updating.h"
#include "little.h"
#include "ROB_to_run.h"
#include "SLB_to_exu.h"
#include "RS_running.h"

using namespace std;


void flag_newing(){
    lastpc=newpc;
    ifclear=0;
    lastend=newending;
}
int cixu[3];

void run(){
    cixu[0]=0;
    cixu[1]=1;
    cixu[2]=2;
    init();
    newpc=lastpc=0;
    newending=lastend=0;
    while(1){

        unsigned seed = std::chrono::system_clock::now ().time_since_epoch ().count ();
        shuffle(cixu,cixu+3,std::default_random_engine (seed));

        Clock++;
        getinss();
        run_ROB();
        if(cixu[1]==0){
            ins_to_run();
            RS_exu();
            SLB_runing();
        }
        else if(cixu[1]==1){

            RS_exu();
            SLB_runing();
            ins_to_run();
        }
        else if(cixu[1]==2){
            SLB_runing();
            RS_exu();
            ins_to_run();
        }

        if(ifclear)ClearAll();
        flag_newing();
        updating();
        if(lastend&&lastinsq.size==0&&lastROB.size==0)break;
    }
    printf("%u\n",lastreg[10].reg&255u);
    return ;
}
#endif //UNTITLED11_RUN_H
