#include <8085.h>

emu8085::emu8085()
    : regArray({&B, &C, &D, &E, &H, &L, &A, &A}),
      regPairArray({&B, &D, &H, &SPU})
{
  mem = new byte[65536]();

  // error handling for if the mem allocation fails
  if (!mem)
  {
    std::cout << "Memory allocation failed\n"
              << std::endl;
  }
}

emu8085::~emu8085() { delete[] mem; }

void emu8085::reset_reg()
{
  // Initialize all registers to zero essentially resetting the cpu context
  A = B = C = D = E = H = L = 0x00;
  SPU = 0xFF;
  SPL = 0xFF; // Standard initial stack pointer value
  PCU = 0x00;
  PCL = 0x00; // Start execution at 0000h
  S = Z = AC = P = CY = 0;
  I = 0x00; // Initialize instruction register
}

void emu8085::op_fetch()
{
  mem_read(get_PC());
  I = DB;
}
void emu8085::mem_read(word memLoc)
{
  if (memLoc >= 65536)
  {
    std::cerr << "Invalid memory read at: " << memLoc << std::endl;
    return; // Or throw an exception
  }
  DB = mem[memLoc];
  INX_RP(PCU);
}
void emu8085::mem_access(word memLoc)
{
  if (memLoc >= 65536)
  {
    std::cerr << "Invalid memory read at: " << memLoc << std::endl;
    return; // Or throw an exception
  }
  DB = mem[memLoc];
}

void emu8085::mem_write(word memloc)
{
  if (memloc >= 65536)
  {
    std::cerr << "Invalid memory read at: " << memloc << std::endl;
    return;
  }
  this->mem[memloc] = DB;
}

void emu8085::reset_mem()
{
  // resetting the whole memory
  std::fill(mem, mem + 65536, 0);
}

void emu8085::reset()
{
  reset_reg();
  reset_mem();
}

void emu8085::execute()
{
  running = true;
  while (running == true)
  {
    op_fetch();
    function_recognizer(I);
  }
}

void emu8085::print_reg()
{
  std::cout << "A : " << std::hex << static_cast<int>(A) << std::dec
            << std::endl;
  std::cout << "B : " << std::hex << static_cast<int>(B)
            << "\tC : " << static_cast<int>(C) << std::dec << std::endl;
  std::cout << "D : " << std::hex << static_cast<int>(D)
            << "\tE : " << static_cast<int>(E) << std::dec << std::endl;
  std::cout << "H : " << std::hex << static_cast<int>(H)
            << "\tL : " << static_cast<int>(L) << std::dec << std::endl;
  std::cout << "SP : " << std::hex << (word)((SPU << 8) | SPL)
            << "\tPC : " << (word)((PCU << 8) | PCL)
            << "\tI : " << static_cast<int>(I) << std::dec << std::endl;
  std::cout << "S : " << static_cast<int>(S) << " Z : " << static_cast<int>(Z)
            << " AC : " << static_cast<int>(AC)
            << " P : " << static_cast<int>(P)
            << " CY : " << static_cast<int>(CY) << std::endl;
}

void emu8085::set_PC(word memLoc)
{
  byte upperByte = byte(memLoc >> 8);
  byte lowerByte = byte(memLoc);
  PCU = upperByte;
  PCL = lowerByte;
}

word emu8085::get_PC()
{
  word upperByte = PCU << 8;
  word lowerByte = PCL;

  word PC = upperByte + lowerByte;

  return PC;
}