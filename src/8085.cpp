#include <8085.h>

emu8085::emu8085() {
  mem = new byte[65536]();

  // error handling for if the mem allocation fails
  if (!mem) {
    std::cout << "Memory allocation failed\n" << std::endl;
  }
}
void emu8085::reset_reg() {
  // Initialize all registers to zero essentially resetting the cpu context
  A = B = C = D = E = H = L = 0x00;
  SPU = 0xFF;
  SPL = 0xFF; // Standard initial stack pointer value
  PCU = 0x00;
  PCL = 0x00; // Start execution at 0000h
  S = Z = AC = P = CY = 0;
  I = 0x00; // Initialize instruction register
}
void emu8085::reset_mem() {
  // resetting the whole memory
  std::fill(mem, mem + 65536, 0);
}
void emu8085::reset() {
  reset_reg();
  reset_mem();
  initializeInstructionTable();
}

void emu8085::op_fetch() {

  mem_read(get_PC());

  load_reg(I, DB);
  INX_RP(PCU);
}
void emu8085::mem_read(word memLoc) {
  if (memLoc >= 65536) {
    std::cerr << "Invalid memory read at: " << memLoc << std::endl;
    return; // Or throw an exception
  }
  DB = mem[memLoc];
}

void emu8085::mem_write(word memLoc) {
  if (memLoc >= 65536) {
    std::cerr << "Invalid memory read at: " << memLoc << std::endl;
    return;
  }
  mem[memLoc] = DB;
}

void emu8085::execute() {
  running = true;
  while (running == true) {

    op_fetch();

    function_recognizer(I)();
  }
}

void emu8085::print_reg() {
  std::cout << '\n'
            << "A : " << std::hex << static_cast<int>(A) << std::dec
            << std::endl
            << "B : " << std::hex << static_cast<int>(B)
            << "\tC : " << static_cast<int>(C) << std::dec << '\n'
            << "D : " << std::hex << static_cast<int>(D)
            << "\tE : " << static_cast<int>(E) << std::dec << '\n'
            << "H : " << std::hex << static_cast<int>(H)
            << "\tL : " << static_cast<int>(L) << std::dec << '\n'
            << "SP : " << std::hex << (word)((SPU << 8) | SPL)
            << "\tPC : " << (word)((PCU << 8) | PCL)
            << "\tI : " << static_cast<int>(I) << std::dec << '\n'
            << "S : " << static_cast<int>(S) << " Z : " << static_cast<int>(Z)
            << " AC : " << static_cast<int>(AC)
            << " P : " << static_cast<int>(P)
            << " CY : " << static_cast<int>(CY) << '\n';
}

void emu8085::set_PC(word memLoc) {
  byte upperByte = byte(memLoc >> 8);
  byte lowerByte = byte(memLoc);
  PCU = upperByte;
  PCL = lowerByte;
}

word emu8085::get_PC() {
  word upperByte = PCU << 8;
  word lowerByte = PCL;

  word PC = upperByte + lowerByte;

  return PC;
}

void emu8085::print(word memLoc) {

  for (int i = 0; i < 8; i++) {
    mem_read(memLoc + i);
    std::cout << std::hex << static_cast<int>(DB) << " ";
  }
}

emu8085::~emu8085() { delete[] mem; }