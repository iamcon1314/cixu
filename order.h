
#ifndef UNTITLED11_ORDER_H
#define UNTITLED11_ORDER_H

#include "instructions.h"
#include "instype.h"

class Order{
public:
    instype type=END;
    unsigned int rd,rs1,rs2,imm;
    Order(){}
    Order(instype _type,unsigned int _rd,unsigned int _rs1,unsigned int _rs2, unsigned int _imm):type(_type),rd(_rd),rs1(_rs1),rs2(_rs2),imm(_imm){}
};


Order Decode(unsigned int s,bool tmp=0){
    Order order;
    if(s==(int)0x0ff00513){
        order.type=END;
        return order;
    }
    int type1=s&0x7f;
    int type2=(s>>12)&0x7;
    int type3=(s>>25)&0x7f;
    order.rd=(s>>7)&0x1f;
    order.rs1=(s>>15)&0x1f;
    order.rs2=(s>>20)&0x1f;
    if(type1==0x37||type1==0x17){//U类型
        if(type1==0x37)order.type=LUI;
        if(type1==0x17)order.type=AUIPC;
        order.imm=(s>>12)<<12;
    }
    if(type1==0x33){//R类型
        if(type2==0x0){
            if(type3==0x00)order.type=ADD;
            if(type3==0x20)order.type=SUB;
        }
        if(type2==0x1)order.type=SLL;
        if(type2==0x2)order.type=SLT;
        if(type2==0x3)order.type=SLTU;
        if(type2==0x4)order.type=XOR;
        if(type2==0x5){
            if(type3==0x00)order.type=SRL;
            if(type3==0x20)order.type=SRA;
        }
        if(type2==0x6)order.type=OR;
        if(type2==0x7)order.type=AND;
    }
    if(type1==0x67||type1==0x03||type1==0x13){//I类型
        if(type1==0x67)order.type=JALR;
        if(type1==0x03){
            if(type2==0x0)order.type=LB;
            if(type2==0x1)order.type=LH;
            if(type2==0x2)order.type=LW;
            if(type2==0x4)order.type=LBU;
            if(type2==0x5)order.type=LHU;
        }
        if(type1==0x13){
            if(type2==0x0)order.type=ADDI;
            if(type2==0x2)order.type=SLTI;
            if(type2==0x3)order.type=SLTIU;
            if(type2==0x4)order.type=XORI;
            if(type2==0x6)order.type=ORI;
            if(type2==0x7)order.type=ANDI;
            if(type2==0x1)order.type=SLLI;
            if(type2==0x5){
                if(type3==0x00)order.type=SRLI;
                if(type3==0x20)order.type=SRAI;
            }
        }
        order.imm=(s>>20);
        if(order.type==SRAI)order.imm-=1024;
    }
    if(type1==0x23){//S类型
        if(type2==0x0)order.type=SB;
        if(type2==0x1)order.type=SH;
        if(type2==0x2)order.type=SW;
        order.imm=((s>>25)<<5) | ((s>>7)&0x1f);
    }
    if(type1==0x6f){//J类型
        order.type=JAL;
        order.imm=(((s>>12)&0xff)<<12) | (((s>>20)&0x1)<<11) | (((s>>21)&0x3ff)<<1)  | (((s>>31)&1)<<20);
    }
    if(type1==0x63){//B类型
        if(type2==0x0)order.type=BEQ;
        if(type2==0x1)order.type=BNE;
        if(type2==0x4)order.type=BLT;
        if(type2==0x5)order.type=BGE;
        if(type2==0x6)order.type=BLTU;
        if(type2==0x7)order.type=BGEU;
        order.imm=(((s>>7)&0x1)<<11) | (((s>>8)&0xf)<<1) | (((s>>25)&0x3f)<<5)  | (((s>>31)&1)<<12);
    }
    if(order.type==JALR||order.type==LB||order.type==LH||order.type==LW||order.type==LBU||order.type==LHU){
        if(order.imm>>11)order.imm|=0xfffff000;
    }
    if(order.type==ADDI||order.type==SLTI||order.type==SLTIU||
       order.type==XORI||order.type==ORI||order.type==ANDI){
        if(order.imm>>11)order.imm|=0xfffff000;
    }
    if(order.type==SB||order.type==SH||order.type==SW){
        if(order.imm>>11)order.imm|=0xfffff000;
    }
    if(order.type==JAL){
        if(order.imm>>20)order.imm|=0xfff00000;
    }
    if(order.type==BEQ||order.type==BNE||order.type==BLT||order.type==BGE||order.type==BLTU||order.type==BGEU){
        if(order.imm>>12)order.imm|=0xffffe000;
    }
    return order;
}
#endif //UNTITLED11_ORDER_H
