

#ifndef UNTITLED11_ROB_H
#define UNTITLED11_ROB_H

#include "instructions.h"

class ROB_node{
public:
    instype ordertype;
    unsigned int inst,pc,jumppc,dest,value;
    bool isjump;
    bool ready;
};
class ROB{
public:
    ROB_node s[32];
    int L=1,R=0,size=0;
}lastROB,newROB;



#endif //UNTITLED11_ROB_H
