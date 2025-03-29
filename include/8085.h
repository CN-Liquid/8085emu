#pragma once
#include<stdint.h>
#include<iostream>

typedef uint8_t byte;
typedef uint16_t word;

class emu8085
{
    private:
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

    public:
        emu8085();
        
        ~emu8085();

        void reset_reg();

        void reset_mem();

        void reset();

        void print_reg();
    
};