
#ifndef UNTITLED11_RS_H
#define UNTITLED11_RS_H

#include "instructions.h"

class RS_node{
public:
    instype ordertype;
    unsigned int inst,pc,jumppc,vj,vk,qj,qk,imm,reorder;
    bool busy;
};

class RS{
public:
    RS_node s[32];
}
lastRS,newRS;



#endif //UNTITLED11_RS_H
