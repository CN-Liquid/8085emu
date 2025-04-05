#pragma once
#include<stdint.h>
#include<iostream>

typedef uint8_t byte;
typedef uint16_t word;

class emu8085
{
    public:
        //main registers
        byte A,B,C,D,E,H,L;

        //stack register
        word SP;

        //program counter register
        word PC;

        //status register
        byte S : 1; //sign
        byte Z : 1; //zero
        byte AC : 1; //auxiliary carry
        byte P : 1; //parity
        byte CY : 1; //carry

        //The 16KB memory for the CPU
        byte* mem;

        //Instruction register
        byte I;

        //The fetch-decode-execute-store cycle for the 8085
        void op_fetch();
        byte mem_read(word memloc);
        void mem_write(word memloc , byte mem);



        emu8085();
        
        ~emu8085();

        void reset_reg();

        void reset_mem();

        void reset();

        void print_reg();

        void execute();

        //Data transfet instsructions
        void MOV_R_R(byte &reg1,byte &reg2);
        void MOV_R_M(byte &reg );
        void MOV_M_R( byte &reg);

        void MVI_R_D(byte &reg , byte data);
        void MVI_M_D(byte data);

        void LXI_RP_D(byte &regPair,word data);

        void LDA_M(word memLoc);

        void LDAX_RP(byte &regPair);

        void LHLD_D(word memLoc);

        void STA_M(word memLoc);

        void STAX_RP(byte &regpair);

        void SHLD_M(word memLoc);

        void XCHG();

        //Arithmetic Instructions
        void ADD_R(byte &reg);
        void ADD_M(word memLoc);

        void ADC_R(byte &reg);
        void ADC_M(word memLoc);

        void ADI_D(byte data);

        void ACI_D(byte data);

        void DAD_RP(byte &regPair);

        void SUB_R(byte &reg);
        void SUB_M(word memLoc);

        void SBB_R(byte &reg);
        void SBB_M(word memLoc);

        void SUI_D(byte data);

        void SBI_D(byte data);

        void INR_R(byte &reg);
        void INR_M(word memLoc);

        void INX_RP(byte &bytePair);

        void DCR_R(byte &reg);
        void DCR_M(word memLoc);

        void DCX_RP(byte &bytePair);

        //Logical instructions

        void CMP_R(byte &reg);
        void CMP_M(word memLoc);

        void CPI_D(byte data);

        void ANA_R(byte &reg);
        void ANA_M(word memLoc);

        void ANI_D(byte data);

        void XRA_R(byte &reg);
        void XRA_M(word memLoc);

        void XRI_D(byte data);

        void ORA_R(byte &reg);
        void ORA_M(word memLoc);

        void ORI_D(byte data);

        void RLC();

        void RRC();

        void RAL();

        void RAR();

        void CMA();

        void CMC();

        void STC();





};