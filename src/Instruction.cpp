#include <8085.h>
bool hasEvenOnes(byte num) {
  num ^= num >> 4;   // Fold into 4 bits
  num ^= num >> 2;   // Fold into 2 bits
  num ^= num >> 1;   // Final fold into 1 bit
  return !(num & 1); // LSB = parity
}

byte emu8085::populate_arguments_byte() {
  mem_read(get_PC());
  INX_RP(PCU);
  byte data = DB;
  return data;
}
word emu8085::populate_arguments_word() {
  mem_read(get_PC());
  INX_RP(PCU);
  word data = DB;
  mem_read(get_PC());
  INX_RP(PCU);
  data = (data ) + word(DB<<8);
  return data;
}
void emu8085::MOV_R_R(byte &reg1, byte &reg2) { reg1 = reg2; }
void emu8085::MOV_R_M(byte &reg) {
  word memLoc = H * 100000000 + L;
  mem_read(memLoc);
  reg = DB;
}
void emu8085::MOV_M_R(byte &reg) {
  word memLoc = H * 100000000 + L;
  DB = reg;
  mem_write(memLoc);
}
void emu8085::MVI_R_D(byte &reg) {
  byte data = populate_arguments_byte();
  reg = data;
}
void emu8085::MVI_M_D() {

  word memLoc = H * 100000000 + L;
  DB = populate_arguments_byte();
  mem_write(memLoc);
}
void emu8085::LXI_RP_D(byte &regPair) {
  word data = populate_arguments_word();
  regPair = data >> 8;
  *(&regPair + sizeof(regPair)) = data;
}
void emu8085::LDA_M() {
  word memLoc = populate_arguments_word();
  mem_read(memLoc);
  A = DB;
}
void emu8085::LDAX_RP(byte &regPair) {
  word memLoc = regPair + *(&regPair + sizeof(regPair));
  mem_read(memLoc);
  A = DB;
}
void emu8085::LHLD_D() {
  word memLoc = populate_arguments_word();
  H = mem[memLoc];
  L = mem[memLoc + 1];
}
void emu8085::STA_M() {
  word memLoc = populate_arguments_word();
  DB = A;
  mem_write(memLoc);
}
void emu8085::STAX_RP(byte &regPair) {
  word memLoc = regPair + *(&regPair + sizeof(regPair));
  DB = A;
  mem_write(memLoc);
}
void emu8085::SHLD_M() {
  word memLoc = populate_arguments_word();
  DB = L;
  mem_write(memLoc);
  DB = H;
  mem_write(memLoc + 1);
}
void emu8085::XCHG() {
  byte temp;
  temp = H;
  H = D;
  D = temp;

  temp = E;
  E = L;
  L = temp;
}

void emu8085::ADD_R(byte &reg) {
  A = A + reg;

  // Flag checking
  (A == 0) ? Z=1: Z = 0;
  ((A & 0b10000000) != 0) ? S = 1 : S = 0;
  (hasEvenOnes(A) == 1) ? P = 1 : P = 0;
  CY = (A < reg);
  AC = (A & 0x0F + reg & 0x0F) & 0b00010000 != 0;
}
void emu8085::ADD_M() {
  word memLoc = populate_arguments_word();
  mem_read(memLoc);
  A = A + DB;

  // Flag checking
  (A == 0) ?Z=1:Z=0;
  ((A & 0b10000000 )!= 0) ? S = 1 : S = 0;
  (hasEvenOnes(A) == 1) ? P = 1 : P = 0;
  CY = (A < mem[memLoc]);
  AC = (A & 0x0F + mem[memLoc] & 0x0F) & 0b00010000 != 0;
}

void emu8085::ADC_R(byte &reg) {
  A = A + reg + CY;

  // Flag checking
  (A == 0) ?Z=1:Z=0;
  ((A & 0b10000000 )!= 0) ? S = 1 : S = 0;
  (hasEvenOnes(A) == 1) ? P = 1 : P = 0;
  CY = (A < reg);
  AC = (A & 0x0F + reg & 0x0F) & 0b00010000 != 0;
}
void emu8085::ADC_M() {
  word memLoc = populate_arguments_word();
  mem_read(memLoc);
  A = A + DB + CY;

  // Flag checking
  (A == 0) ?Z=1:Z=0;
  ((A & 0b10000000 )!= 0) ? S = 1 : S = 0;
  (hasEvenOnes(A) == 1) ? P = 1 : P = 0;
  CY = (A < mem[memLoc]);
  AC = (A & 0x0F + mem[memLoc] & 0x0F) & 0b00010000 != 0;
}

void emu8085::ADI_D() {
  byte data = populate_arguments_byte();
  A = A + data;

  // Flag checking
  (A == 0) ?Z=1:Z=0;
  ((A & 0b10000000 )!= 0) ? S = 1 : S = 0;
  (hasEvenOnes(A) == 1) ? P = 1 : P = 0;
  CY = (A < data);
  AC = (A & 0x0F + data & 0x0F) & 0b00010000 != 0;
}
void emu8085::ACI_D() {
  byte data = populate_arguments_byte();
  A = A + data + CY;

  // Flag checking
  (A == 0) ?Z=1:Z=0;
  ((A & 0b10000000 )!= 0) ? S = 1 : S = 0;
  (hasEvenOnes(A) == 1) ? P = 1 : P = 0;
  CY = (A < data);
  AC = (A & 0x0F + data & 0x0F) & 0b00010000 != 0;
}
void emu8085::DAD_RP(byte &regPair) {
  word HL = ((word)H << 8) | (word)L;
  word otherPair = ((word)regPair) << 8 | (word) * (&regPair + sizeof(regPair));
  word sum = HL + otherPair;
  H = (byte)(sum >> 8);
  L = (byte)sum;

  // flag checking
  CY = (sum < HL);
}
void emu8085::SUB_R(byte &reg) {
  CY = (A < reg);
  AC = ((A & 0x0f) < (reg & 0x0f));
  A = A - reg;

  // Flag checking
  (A == 0) ? Z = 1 : 0;
  ((A & 0b10000000 )!= 0) ? S = 1 : S = 0;
  (hasEvenOnes(A) == 1) ? P = 1 : P = 0;
}
void emu8085::SUB_M() {
  word memLoc = populate_arguments_word();
  mem_read(memLoc);
  CY = (A < mem[memLoc]);
  AC = ((A & 0x0f) < (mem[memLoc] & 0x0f));
  A = A - DB;

  // Flag checking
  (A == 0) ?Z=1:Z=0;
  ((A & 0b10000000 )!= 0) ? S = 1 : S = 0;
  (hasEvenOnes(A) == 1) ? P = 1 : P = 0;
}
void emu8085::SBB_R(byte &reg) {
  CY = ((A) < reg + CY);
  AC = ((A&0x0f) < (reg + CY & 0x0f));
  A = A - reg - CY;

  // Flag checking
  (A == 0) ?Z=1:Z=0;
  ((A & 0b10000000 )!= 0) ? S = 1 : S = 0;
  (hasEvenOnes(A) == 1) ? P = 1 : P = 0;
}
void emu8085::SBB_M() {
  word memLoc = populate_arguments_word();
  mem_read(memLoc);
  CY = ((A) < mem[memLoc] + CY);
  AC = ((A&0x0f) < (mem[memLoc] + CY & 0x0f));
  A = A - DB - CY;

  // Flag checking
  (A == 0) ?Z=1:Z=0;
  ((A & 0b10000000 )!= 0) ? S = 1 : S = 0;
  (hasEvenOnes(A) == 1) ? P = 1 : P = 0;
}
void emu8085::SUI_D() {
  byte data = populate_arguments_byte();
  CY = ((A) < data);
  AC = ((A&0x0f) < (data & 0x0f));
  A = A - data;

  // Flag checking
  (A == 0) ?Z=1:Z=0;
  ((A & 0b10000000 )!= 0) ? S = 1 : S = 0;
  (hasEvenOnes(A) == 1) ? P = 1 : P = 0;
}
void emu8085::SBI_D() {
  byte data = populate_arguments_byte();
  CY = ((A) < data + CY);
  AC = ((A&0x0f) < (data + CY & 0x0f));
  A = A - data - CY;

  // Flag checking
  (A == 0) ?Z=1:Z=0;
  ((A & 0b10000000 )!= 0) ? S = 1 : S = 0;
  (hasEvenOnes(A) == 1) ? P = 1 : P = 0;
}
void emu8085::INR_R(byte &reg) {
  AC = (((reg & 0x0F )+ 0b1) & 0b00010000) != 0;
  reg = reg + 1;

  // Flag checking
  (reg == 0) ?Z = 1: Z = 0;
  (reg & 0b10000000 != 0) ? S = 1 : S = 0;
  (hasEvenOnes(reg) == 1) ?P = 1: P = 0;
}
void emu8085::INR_M() {
  word memLoc = populate_arguments_word();
  mem_read(memLoc);
  AC = (mem[memLoc] & 0x0F) & 0b00010000 != 0;
  DB = DB + 1;
  mem_write(memLoc);

  // Flag checking
  (mem[memLoc] == 0) ?: Z = 0;
  (mem[memLoc] & 0b10000000 != 0) ? S = 1 : 0;
  (hasEvenOnes(mem[memLoc]) == 1) ?: P = 1;
}
void emu8085::INX_RP(byte &regPair) {
  word upperByte = regPair << 8;
  word lowerByte = *(&regPair + sizeof(regPair));
  word otherPair = upperByte + lowerByte;
  word sum = 1 + otherPair;
  regPair = (byte)(sum >> 8);
  *(&regPair + sizeof(regPair)) = (byte)sum;
}
void emu8085::DCR_R(byte &reg) {
  AC = ((reg & 0x0F) == 0);
  reg = reg - 1;

  // Flag checking
  (reg == 0) ?Z=1: Z = 0;
  ((reg & 0b10000000) != 0) ? S = 1 :S= 0;
  (hasEvenOnes(reg) == 1) ?P=1: P = 0;
}
void emu8085::DCR_M() {
  word memLoc = populate_arguments_word();
  AC = ((mem[memLoc]) & 0x0f < 0b1);
  mem_read(memLoc);
  DB = DB - 1;
  mem_write(memLoc);

  // Flag checking
  (mem[memLoc] == 0) ?: Z = 0;
  (mem[memLoc] & 0b10000000 != 0) ? S = 1 : 0;
  (hasEvenOnes(mem[memLoc]) == 1) ?: P = 1;
}
void emu8085::DCX_RP(byte &regPair) {
  word otherPair = ((word)regPair) << 8 | (word) * (&regPair + sizeof(regPair));
  word sum = otherPair - 1;
  regPair = (byte)(sum >> 8);
  *(&regPair + sizeof(regPair)) = (byte)sum;
}

void emu8085::CMP_R(byte &reg) {
  byte temp = A - reg;

  // Flag checking
  Z = (temp == 0);
  S = (temp >> 7);
  P = hasEvenOnes(temp);
  CY = (A < reg);
  AC = ((A & 0x0F) < (reg & 0x0F));
}
void emu8085::CMP_M() {
  word memLoc = populate_arguments_word();
  mem_read(memLoc);
  byte temp = A - DB;

  // Flag checking
  Z = (temp == 0);
  S = (temp >> 7);
  P = hasEvenOnes(temp);
  CY = (A < mem[memLoc]);
  AC = ((A & 0x0F) < (mem[memLoc] & 0x0F));
}
void emu8085::CPI_D() {
  byte data = populate_arguments_byte();
  byte temp = A - data;

  // Flag checking
  Z = (temp == 0);
  S = (temp >> 7);
  P = hasEvenOnes(temp);
  CY = (A < data);
  AC = ((A & 0x0F) < (data & 0x0F));
}
void emu8085::ANA_R(byte &reg) {
  A = A & reg;

  // Flag checking
  Z = (A == 0);
  S = (A >> 7);
  P = hasEvenOnes(A);
  CY = 0;
  AC = (A >> 3);
}
void emu8085::ANA_M() {
  word memLoc = populate_arguments_word();
  mem_read(memLoc);
  A = A & DB;

  // Flag checking
  Z = (A == 0);
  S = (A >> 7);
  P = hasEvenOnes(A);
  CY = 0;
  AC = (A >> 3);
}
void emu8085::ANI_D() {
  byte data = populate_arguments_byte();
  A = A & data;

  // Flag checking
  Z = (A == 0);
  S = (A >> 7);
  P = hasEvenOnes(A);
  CY = 0;
  AC = (A >> 3);
}
void emu8085::XRA_R(byte &reg) {
  A = A ^ reg;

  // Flag checking
  Z = (A == 0);
  S = (A >> 7);
  P = hasEvenOnes(A);
  CY = 0;
  AC = 0;
}
void emu8085::XRA_M() {
  word memLoc = populate_arguments_word();
  mem_read(memLoc);
  A = A ^ DB;

  // Flag checking
  Z = (A == 0);
  S = (A >> 7);
  P = hasEvenOnes(A);
  CY = 0;
  AC = 0;
}
void emu8085::XRI_D() {
  byte data = populate_arguments_byte();
  A = A ^ data;

  // Flag checking
  Z = (A == 0);
  S = (A >> 7);
  P = hasEvenOnes(A);
  CY = 0;
  AC = 0;
}
void emu8085::ORA_R(byte &reg) {
  A = A | reg;

  // Flag checking
  Z = (A == 0);
  S = (A >> 7);
  P = hasEvenOnes(A);
  CY = 0;
  AC = 0;
}
void emu8085::ORA_M() {
  word memLoc = populate_arguments_word();
  mem_read(memLoc);
  A = A | DB;

  // Flag checking
  Z = (A == 0);
  S = (A >> 7);
  P = hasEvenOnes(A);
  CY = 0;
  AC = 0;
}
void emu8085::ORI_D() {
  byte data = populate_arguments_byte();
  A = A | data;

  // Flag checking
  Z = (A == 0);
  S = (A >> 7);
  P = hasEvenOnes(A);
  CY = 0;
  AC = 0;
}
void emu8085::RLC() {
  // flag checking
  CY = (A >> 7);

  // implememtation
  A = A << 1;
  A = A + CY;
}
void emu8085::RRC() {
  // flag checking
  CY = A & 0b00000001;

  // implementation
  A = A >> 1;
  A = A + (CY << 7);
}
void emu8085::RAL() {
  byte tempCY = CY;

  CY = (A >> 7);
  A = A << 1;
  A = A + tempCY;
}
void emu8085::RAR() {
  byte temp = (A & 0x01);
  A = A >> 1;
  A = A + (CY << 7);
  CY = temp;
}
void emu8085::CMA() { A = ~A; }
void emu8085::CMC() { CY = ~CY; }
void emu8085::STC() { CY = CY + 1; }

void emu8085::PUSH_RP(byte &regPair) {
  byte upperByte = regPair;
  byte lowerByte = *(&regPair + sizeof(regPair));
  DB = lowerByte;
  mem_write(word(SPU << 8 | SPL));
  DCX_RP(SPU);
  DB = upperByte;
  mem_write(word(SPU << 8 | SPL));
  DCX_RP(SPU);
}

void emu8085::POP_RP(byte &regPair) {
  mem_read(word(SPU << 8 | SPL));
  byte upperByte = DB;
  INX_RP(SPU);
  mem_read(word(SPU << 8 | SPL));
  byte lowerByte = DB;
  INX_RP(SPU);

  load_reg_pair(SPU, word(upperByte << 8 | lowerByte));
}

void emu8085::JMP_M() {
  word memLoc = populate_arguments_word();
  load_reg_pair(PCU, memLoc);
}
void emu8085::JC_M() {
  word memLoc = populate_arguments_word();
  if (CY == 1) {
    PCL = memLoc;
    PCU = memLoc >> 8;
  }
}
void emu8085::JNC_M() {
  word memLoc = populate_arguments_word();
  if (CY == 0) {
    load_reg_pair(PCU, memLoc);
  }
}
void emu8085::JP_M() {
  word memLoc = populate_arguments_word();
  if (S == 0) {
    PCL = memLoc;
    PCU = memLoc >> 8;
  }
}
void emu8085::JM_M() {
  word memLoc = populate_arguments_word();
  if (S == 1) {
    PCL = memLoc;
    PCU = memLoc >> 8;
  }
}
void emu8085::JZ_M() {
  word memLoc = populate_arguments_word();
  if (Z == 1) {
    PCL = memLoc;
    PCU = memLoc >> 8;
  }
}
void emu8085::JNZ_M() {
  word memLoc = populate_arguments_word();
  if (Z == 0) {
    PCL = memLoc;
    PCU = memLoc >> 8;
  }
}
void emu8085::JPE_M() {
  word memLoc = populate_arguments_word();
  if (P == 1) {
    PCL = memLoc;
    PCU = memLoc >> 8;
  }
}
void emu8085::JPO_M() {
  word memLoc = populate_arguments_word();
  if (P == 0) {
    PCL = memLoc;
    PCU = memLoc >> 8;
  }
}

void emu8085::CALL_M() {
  word memLoc = populate_arguments_word();
  PUSH_RP(SPU);
  set_PC(memLoc);
}
void emu8085::CC_M() {
  word memLoc = populate_arguments_word();
  if (CY == 1) {
    PUSH_RP(SPU);
    set_PC(memLoc);
  }
}
void emu8085::CNC_M() {
  word memLoc = populate_arguments_word();
  if (CY == 0) {
    PUSH_RP(SPU);
    set_PC(memLoc);
  }
}
void emu8085::CP_M() {
  word memLoc = populate_arguments_word();
  if (S == 0) {
    PUSH_RP(SPU);
    set_PC(memLoc);
  }
}
void emu8085::CM_M() {
  word memLoc = populate_arguments_word();
  if (S == 1) {
    PUSH_RP(SPU);
    set_PC(memLoc);
  }
}
void emu8085::CZ_M() {
  word memLoc = populate_arguments_word();
  if (Z == 1) {
    PUSH_RP(SPU);
    set_PC(memLoc);
  }
}
void emu8085::CNZ_M() {
  word memLoc = populate_arguments_word();
  if (Z == 0) {
    PUSH_RP(SPU);
    set_PC(memLoc);
  }
}
void emu8085::CPE_M() {
  word memLoc = populate_arguments_word();
  if (P == 1) {
    PUSH_RP(SPU);
    set_PC(memLoc);
  }
}
void emu8085::CPO_M() {
  word memLoc = populate_arguments_word();
  if (P == 0) {
    PUSH_RP(SPU);
    set_PC(memLoc);
  }
}
void emu8085::RET() { POP_RP(PCU); }

void emu8085::RC() {
  if (CY == 1) {
    RET();
  }
}
void emu8085::RNC() {
  if (CY == 0) {
    RET();
  }
}
void emu8085::RP() {
  if (S == 0) {
    RET();
  }
}
void emu8085::RM() {
  if (S == 1) {
    RET();
  }
}
void emu8085::RZ() {
  if (Z == 1) {
    RET();
  }
}
void emu8085::RNZ() {
  if (Z == 0) {
    RET();
  }
}
void emu8085::RPE() {
  if (P == 1) {
    RET();
  }
}
void emu8085::RPO() {
  if (P == 0) {
    RET();
  }
}
void emu8085::NOP() {}

void emu8085::HLT() { running = false; }