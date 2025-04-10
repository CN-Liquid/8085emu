#pragma once
#include <iostream>
#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;

class emu8085 {
public:
  // main registers
  byte A, B, C, D, E, H, L;

  // stack register
  byte SPU, SPL;

  // program counter register
  byte PCU, PCL;

  // status register
  byte S : 1;  // sign
  byte Z : 1;  // zero
  byte AC : 1; // auxiliary carry
  byte P : 1;  // parity
  byte CY : 1; // carry

  // The 16KB memory for the CPU
  byte *mem;

  // Instruction register
  byte I;

  byte DB;

  // The fetch-decode-execute-store cycle for the 8085
  void op_fetch();
  void mem_read(word memloc);
  void mem_write(word memloc);

  emu8085();

  ~emu8085();

  void reset_reg();

  void reset_mem();

  void reset();

  void print_reg();

  void execute();

  void set_PC(word memLoc);

  // Data transfet instsructions
  void MOV_R_R(byte &reg1, byte &reg2);
  void MOV_R_M(byte &reg);
  void MOV_M_R(byte &reg);

  void MVI_R_D(byte &reg, byte data);
  void MVI_M_D(byte data);

  void LXI_RP_D(byte &regPair, word data);

  void LDA_M(word memLoc);

  void LDAX_RP(byte &regPair);

  void LHLD_D(word memLoc);

  void STA_M(word memLoc);

  void STAX_RP(byte &regpair);

  void SHLD_M(word memLoc);

  void XCHG();

  // Arithmetic Instructions
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

  // Logical instructions

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

  // Branching instructions
  void JMP_M(word memLoc);

  void JC_M(word memLoc);
  void JNC_M(word memLoc);
  void JP_M(word memLoc);
  void JM_M(word memLoc);
  void JZ_M(word memLoc);
  void JNZ_M(word memLoc);
  void JPE_M(word memLoc);
  void JPO_M(word memLoc);

  void CALL_M(word memLoc);

  void CC_M(word memLoc);
  void CNC_M(word memLoc);
  void CP_M(word memLoc);
  void CM_M(word memLoc);
  void CZ_M(word memLoc);
  void CNZ_M(word memLoc);
  void CPE_M(word memLoc);
  void CPO_M(word memLoc);

  void RET();

  void RC();
  void RNC();
  void RP();
  void RM();
  void RZ();
  void RNZ();
  void RPE();
  void RPO();

  // Control operations
  void NOP();

  void HLT();

  void DI();

  void EI();

  // Stack operations

  void PUSH_RP(byte &regpair);
  void PUSH_M(word memLoc);
  void POP_RP(byte &regPair);
  void POP_M(word memLoc);
};