#include<8085.h>

void emu8085::MOV_R_R(byte &reg1 , byte &reg2)
{
    reg1 = reg2;
}
void emu8085::MOV_R_M(byte &reg1 ,word memLoc)
{
    reg1 = mem[memLoc];
}
void emu8085::MOV_M_R(word memLoc , byte &reg)
{
    mem[memLoc]=reg;
}
void emu8085::MVI_R_D(byte &reg , byte data)
{
    reg = data;
}