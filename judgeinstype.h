
#ifndef UNTITLED11_JUDGEINSTYPE_H
#define UNTITLED11_JUDGEINSTYPE_H

#include "instructions.h"

bool isCalc(instype type){
    return type==LUI||type==AUIPC||type==ADD||type==SUB||type==SLL||type==SLT||type==SLTU||
           type==XOR||type==SRL||type==SRA||type==OR||type==AND||type==ADDI||type==SLTI||type==SLTIU||
           type==XORI||type==ORI||type==ANDI||type==SLLI||type==SRLI||type==SRAI;
}
bool isBranch(instype type){
    return type==BEQ||type==BNE||type==BLT||type==BGE||type==BLTU||type==BGEU||type==JAL||type==JALR;
}
bool isLoad(instype type){
    return type==LB||type==LH||type==LW||type==LBU||type==LHU;
}
bool isStore(instype type){
    return type==SB||type==SH||type==SW;
}
#endif //UNTITLED11_JUDGEINSTYPE_H
