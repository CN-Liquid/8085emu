#include<8085.h>

emu8085::emu8085()
{
    mem = new byte[65536]();

    //error handling for if the mem allocation fails
    if(!mem)
    {
        std::cout << "Memory allocation failed\n"<<std::endl;

    }
}

emu8085::~emu8085()
{
    delete[] mem;
}

void emu8085::reset_reg()
{
    //Initialize all registers to zero essentially resetting the cpu context
    A = B = C = D = E = H = L = 0x00;
    SP = 0xFFFF;  // Standard initial stack pointer value
    PC = 0x0000;  // Start execution at 0000h
    S = Z = AC = P = CY = 0;
    I = 0x00;  // Initialize instruction register
}

void emu8085::op_fetch()
{
    I = mem[PC];
}
byte emu8085::mem_read(word memloc)
{
    if (memloc >= 65536) {
        std::cerr << "Invalid memory read at: " << memloc << std::endl;
        return 0xFF;  // Or throw an exception
    }
    return mem[memloc];
}

void emu8085::mem_write(word memloc , byte mem)
{
    if (memloc >= 65536) {
        std::cerr << "Invalid memory read at: " << memloc << std::endl;
        return ;
    }
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

void emu8085::execute()
{
    
}

void emu8085::print_reg()
{
    std::cout << "A : " << std::hex << static_cast<int>(A) << std::dec << std::endl;
    std::cout << "B : " << std::hex << static_cast<int>(B) 
              << "\tC : " << static_cast<int>(C) << std::dec << std::endl;
    std::cout << "D : " << std::hex << static_cast<int>(D)
              << "\tE : " << static_cast<int>(E) << std::dec << std::endl;
    std::cout << "H : " << std::hex << static_cast<int>(H)
              << "\tL : " << static_cast<int>(L) << std::dec << std::endl;
    std::cout << "SP : " << std::hex << SP
              << "\tPC : " << PC
              << "\tI : " << static_cast<int>(I) << std::dec << std::endl;
    std::cout << "S : " << static_cast<int>(S) << " Z : " << static_cast<int>(Z) 
              << " AC : " << static_cast<int>(AC) << " P : " << static_cast<int>(P) << " CY : " << static_cast<int>(CY) << std::endl;

}