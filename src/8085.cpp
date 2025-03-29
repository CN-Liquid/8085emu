#include<8085.h>

emu8085::emu8085()
{
    byte* mem = new byte[65536];
    if(!mem)
    {
        std::cout << "Memory allocation failed\n"<<std::endl;

    }
};

emu8085::~emu8085()
{
    delete[] mem;
};

void emu8085::reset()
        {
            //Initialize all registers to zero essentially resetting the whole cpu
            A = B = C = D = E = H = L = SP = PC = S = Z = AC = P = CY = 0;
        }