#include<8085.h>

emu8085::emu8085()
{
    byte* mem = new byte[65536]();

    //error handling for if the mem allocation fails
    if(!mem)
    {
        std::cout << "Memory allocation failed\n"<<std::endl;

    }
};

emu8085::~emu8085()
{
    delete[] mem;
};

void emu8085::reset_reg()
{
    //Initialize all registers to zero essentially resetting the cpu context
    A = B = C = D = E = H = L = SP = PC = S = Z = AC = P = CY = 0;
}

void emu8085::op_fetch()
{
    inst = mem[PC];
}
byte emu8085::mem_read(word memloc)
{
    return mem[memloc];
}

void emu8085::mem_write(word memloc , byte mem)
{
    this->mem[ memloc ]=mem;
}

void emu8085::reset_mem()
{
    //resetting the whole memory
    std::fill( mem , mem + 65536 , 0 );
}

void emu8085::reset()
        {
            reset_reg();
            reset_mem();
        }