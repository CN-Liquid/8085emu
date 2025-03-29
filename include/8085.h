#pragma once
#include<stdint.h>
#include<iostream>

typedef int8_t byte;
typedef int16_t word;

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

        byte* mem;

    public:
        emu8085(){}
        
        ~emu8085(){}

        void reset(){}


    
};