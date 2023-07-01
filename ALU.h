
#ifndef UNTITLED11_ALU_H
#define UNTITLED11_ALU_H

#include "RS.h"

void do_ALU(RS_node tmp, unsigned int &value, unsigned int &jumppc) {
    switch (tmp.ordertype) {
        case LUI:
            value = tmp.imm;
            break;
        case AUIPC:
            value = tmp.pc + tmp.imm;
            break;
        case ADD:
            value = tmp.vj + tmp.vk;
            break;
        case SUB:
            value = tmp.vj - tmp.vk;
            break;
        case SLL:
            value = tmp.vj << (tmp.vk & 0x1f);
            break;
        case SLT:
            value = ((int) tmp.vj < (int) tmp.vk) ? 1 : 0;
            break;
        case SLTU:
            value = (tmp.vj < tmp.vk) ? 1 : 0;
            break;
        case XOR:
            value = tmp.vj ^ tmp.vk;
            break;
        case SRL:
            value = tmp.vj >> (tmp.vk & 0x1f);
            break;
        case OR:
            value = tmp.vj | tmp.vk;
            break;
        case SRA:
            value = (int) tmp.vj >> (tmp.vk & 0x1f);
            break;
        case AND:
            value = tmp.vj & tmp.vk;
            break;
        case JALR:
            jumppc = (tmp.vj + tmp.imm) & (~1);
            value = tmp.pc + 4;
            break;
        case ADDI:
            value = tmp.vj + tmp.imm;
            break;
        case XORI:
            value = tmp.vj ^ tmp.imm;
            break;
        case ANDI:
            value = tmp.vj & tmp.imm;
            break;
        case SLTI:
            value = ((int) tmp.vj < (int) tmp.imm) ? 1 : 0;
            break;
        case SLTIU:
            value = (tmp.vj < tmp.imm) ? 1 : 0;
            break;
        case ORI:
            value = tmp.vj | tmp.imm;
            break;
        case SLLI:
            value = tmp.vj << tmp.imm;
            break;
        case SRLI:
            value = tmp.vj >> tmp.imm;
            break;
        case SRAI:
            value = (int) tmp.vj >> tmp.imm;
            break;
        case JAL:
            value = tmp.pc + 4;
            break;
        case BNE:
            value = (tmp.vj != tmp.vk ? 1 : 0);
            break;
        case BEQ:
            value = (tmp.vj == tmp.vk ? 1 : 0);
            break;
        case BGE:
            value = ((int) tmp.vj >= (int) tmp.vk ? 1 : 0);
            break;
        case BGEU:
            value = (tmp.vj >= tmp.vk ? 1 : 0);
            break;
        case BLT:
            value = ((int) tmp.vj < (int) tmp.vk ? 1 : 0);
            break;
        case BLTU:
            value = (tmp.vj < tmp.vk ? 1 : 0);
    }
}
#endif //UNTITLED11_ALU_H
