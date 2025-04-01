#include<8085.h>
void emu8085::MOV_R_R(byte &reg1 , byte &reg2)
{
    reg1 = reg2;
}
void emu8085::MOV_R_M(byte &reg1)
{
    word memLoc = H * 100000000 + L;
    reg1 = mem[memLoc];
}
void emu8085::MOV_M_R(byte &reg)
{
    word memLoc = H * 100000000 + L;
    mem[memLoc]=reg;
}
void emu8085::MVI_R_D(byte &reg , byte data)
{
    reg = data;
}
void emu8085::MVI_M_D(byte data)
{
    word memLoc = H * 100000000 + L;
    mem[memLoc] = data;
}
void emu8085::LXI_RP_D(byte &regPair,word data)
{
   regPair = data >> 8;
   *(&regPair + sizeof(regPair)) = data ;
}
void emu8085::LDA_M(word memloc)
{
    A = mem[memloc];
}
void emu8085::LDAX_RP(byte &regPair)
{
    word memLoc = regPair + *(&regPair + sizeof(regPair));
    A = mem [ memLoc];
}
void emu8085::LHLD_D(word memLoc)
{
    L = mem[memLoc];
    H = mem[memLoc + 1];
}
void emu8085::STA_M(word memLoc)
{
    mem[memLoc] = A;
}
void emu8085::STAX_RP(byte &regPair)
{
    word memLoc = regPair + *(&regPair + sizeof(regPair));
    mem[memLoc] = A ;
}
void emu8085::SHLD_M(word memLoc)
{
    mem[memLoc] = L;
    mem[memLoc + 1] = H;
}
void emu8085::XCHG()
{
    byte temp;
    temp = H;
    H = D;
    D = temp;

    temp = E;
    E = L;
    L = temp;
}
