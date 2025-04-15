#include <8085.h>

// 1-byte instructions
void emu8085::function_recognizer(byte opcode)
{
  // MVI
  if ((opcode & 0b11000000) == 0b01000000 && opcode != 0b01110110)
  {
    if ((opcode >> 3) & 0b00000111 == 0b00000110)
    {
      MOV_M_R(*regArray[(opcode) & 0b00000111]);
    }
    if ((opcode & 0b00000111) == 0b00000110)
    {
      MOV_R_M(*regArray[(opcode >> 3) & 0b00000111]);
    }

    else
    {
      MOV_R_R(*regArray[(opcode >> 3) & 0b00000111],
              *regArray[(opcode) & 0b00000111]);
    }
  }

  // MVI
  else if ((opcode & 0b11000111) == 0b00000110 && opcode != 0b01110110)
  {
    if ((opcode & 0b00111000) == 0b00110000)
    {
      MVI_M_D(DB);
    }
    else
    {
      MVI_R_D(*regArray[(opcode >> 3) & 0b00000111]);
    }
  }
  // LXI
  else if ((opcode & 0b11001111) == 0b00000001)
  {

    LXI_RP_D(*regPairArray[(opcode >> 4) & 0b00000011]);
  }
  // LDA
  else if (opcode == 0b00111010)
  {
    LDA_M();
  }
  // LDAX
  else if ((opcode & 0b11001111) == 0b00001010)
  {
    LDAX_RP(*regArray[(opcode >> 4) & 0b00000011]);
  }

  // LHLD
  else if (opcode == 0b00101010)
  {
    LHLD_D();
  }

  // STA
  else if (opcode == 0b00110010)
  {
    STA_M();
  }

  // STAX
  else if ((opcode >> 3) & 0b00000011 == 0b0000010)
  {
    STAX_RP(*regArray[(opcode >> 3) & 0b00000011]);
  }

  // SHLD
  else if (opcode == 0b00100010)
  {
    SHLD_M();
  }
  // XCHG
  else if (opcode == 0b11101011)
  {
    XCHG();
  }

  // ADD
  else if ((opcode & 0b11111000) == 0b10000000)
  {
    if ((opcode & 0b00000111) == 0b00000110)
    {
      ADD_M();
    }
    else
    {
      ADD_R(*regArray[opcode & 0b00000111]);
    }
  }
  // ADC
  else if ((opcode & 0b11111000) == 0b10001000)
  {
    if ((opcode & 0b00000111) == 0b00000110)
    {
      ADC_M();
    }
    else
    {
      ADC_R(*regArray[opcode & 0b00000111]);
    }
  }
  // ADI
  else if (opcode == 0b11000110)
  {
    ADI_D();
  }

  else if (opcode == 0b11001110)
  {
    ACI_D();
  }
  // DAD
  else if ((opcode & 0b11000111) == 0b00000001)
  {
    DAD_RP(*regPairArray[(opcode >> 3) & 0b00000111]);
  }
  // SUB
  else if ((opcode & 0b11111000) == 0b10010000)
  {
    if ((opcode & 0b00000111) == 0b00000110)
    {
      SUB_M();
    }
    else
    {
      SUB_R(*regArray[opcode & 0b00000111]);
    }
  }
  // SBB
  else if ((opcode & 0b11111000) == 0b10011000)
  {
    if ((opcode & 0b00000111) == 0b00000110)
    {
      SBB_M();
    }
    else
    {
      SBB_R(*regArray[opcode & 0b00000111]);
    }
  }
  // SUI
  else if (opcode == 0b11010110)
  {
    SUI_D();
  }
  // SBI
  else if (opcode == 0b11011110)
  {
    SBI_D();
  }
  // INR
  else if ((opcode & 0b11000111) == 0b00000100)
  {

    if ((opcode & 0b00111000) == 0b00110000)
    {
      INR_M();
    }
    else
    {
      INR_R(*regArray[(opcode >> 3) & 0b00000111]);
    }
  }
  // INX
  else if ((opcode & 0b11001111) == 0b00000011)
  {
    INX_RP(*regPairArray[int((opcode >> 4) & 0b00000011)]);
  }
  // DCR
  else if ((opcode & 0b11000111) == 0b00000101)
  {
    if ((opcode & 0b00111000) == 0b00110000)
    {
      DCR_M();
    }
    else
    {
      DCR_R(*regArray[(opcode >> 3) & 0b00000111]);
    }
  }

  // DCX
  else if ((opcode & 0b11001111) == 0b00001011)
  {
    DCX_RP(*regPairArray[(opcode >> 4) & 0b00000011]);
  }
  // CMP
  else if ((opcode & 0b11111000) == 0b10111000)
  {
    if ((opcode & 0b00000111) == 0b00000110)
    {
      CMP_M();
    }
    else
    {
      CMP_R(*regArray[opcode & 0b00000111]);
    }
  }
  // CPI
  else if (opcode == 0b11111110)
  {
    CPI_D();
  }
  // ANA
  else if ((opcode & 0b11111000) == 0b10100000)
  {
    if ((opcode & 0b00000111) == 0b00000110)
    {
      ANA_M();
    }
    else
    {
      ANA_R(*regArray[opcode & 0b00000111]);
    }
  }
  // ANI
  else if (opcode == 0b11100110)
  {
    ANI_D();
  }
  // XRA
  else if ((opcode & 0b11111000) == 0b10101000)
  {
    if ((opcode & 0b00000111) == 0b00000110)
    {
      XRA_M();
    }
    else
    {
      XRA_R(*regArray[opcode & 0b00000111]);
    }
  }
  // XRI
  else if (opcode == 0b11101110)
  {
    XRI_D();
  }

  // ORA
  else if ((opcode & 0b11111000) == 0b10110000)
  {
    if ((opcode & 0b00000111) == 0b00000110)
    {
      ORA_M();
    }
    else
    {
      ORA_R(*regArray[opcode & 0b00000111]);
    }
  }
  // ORI
  else if (opcode == 0b11110110)
  {
    ORI_D();
  }
  // RLC
  else if (opcode == 0b00000111)
  {
    RLC();
  }
  // RRC
  else if (opcode == 0b00001111)
  {
    RRC();
  }
  // RAL
  else if (opcode == 0b00010111)
  {
    RAL();
  }
  // RAR
  else if (opcode == 0b00011111)
  {
    RAR();
  }
  // CMA
  else if (opcode == 0b00101111)
  {
    CMA();
  }
  // CMC
  else if (opcode == 0b00111111)
  {
    CMC();
  }
  // STC
  else if (opcode == 0b00110111)
  {
    STC();
  }
  // JMP
  else if (opcode == 0b11000011)
  {
    JMP_M();
  }
  // JC
  else if (opcode == 0b11011010)
  {
    JC_M();
  }
  // JNC
  else if (opcode == 0b11010010)
  {
    JNC_M();
  }
  // JZ
  else if (opcode == 0b11001010)
  {
    JZ_M();
  }
  // JNZ
  else if (opcode == 0b11000010)
  {
    JNZ_M();
  }
  // JP
  else if (opcode == 0b11110010)
  {
    JP_M();
  }
  // JM
  else if (opcode == 0b11111010)
  {
    JM_M();
  }
  // JPE
  else if (opcode == 0b11101010)
  {
    JPE_M();
  }
  // JPO
  else if (opcode == 0b11100010)
  {
    JPO_M();
  }
  // CALL
  else if (opcode == 0b11001101)
  {
    CALL_M();
  }
  // CC
  else if (opcode == 0b11011100)
  {
    CC_M();
  }
  // CNC
  else if (opcode == 0b11010100)
  {
    CNC_M();
  }
  // CZ
  else if (opcode == 0b11001100)
  {
    CZ_M();
  }
  // CNZ
  else if (opcode == 0b11000100)
  {
    CNZ_M();
  }
  // CP
  else if (opcode == 0b11110100)
  {
    CP_M();
  }
  // CM
  else if (opcode == 0b11111100)
  {
    CM_M();
  }
  // CPE
  else if (opcode == 0b11101100)
  {
    CPE_M();
  }
  // CPO
  else if (opcode == 0b11100100)
  {
    CPO_M();
  }
  // RET
  else if (opcode == 0b11001001)
  {
    RET();
  }
  // RC
  else if (opcode == 0b11011000)
  {
    RC();
  }
  // RNC
  else if (opcode == 0b11010000)
  {
    RNC();
  }
  // RZ
  else if (opcode == 0b11001000)
  {
    RZ();
  }
  // RNZ
  else if (opcode == 0b11000000)
  {
    RNZ();
  }
  // RP
  else if (opcode == 0b11110000)
  {
    RP();
  }
  // RM
  else if (opcode == 0b11111000)
  {
    RM();
  }
  // RPE
  else if (opcode == 0b11101000)
  {
    RPE();
  }
  // RPO
  else if (opcode == 0b11100000)
  {
    RPO();
  }
  // NOP
  else if (opcode == 0b00000000)
  {
    NOP();
  }
  // HLT
  else if (opcode == 0b01110110)
  {
    HLT();
  }

  // PUSH
  else if ((opcode & 0b11001111) == 0b11000101)
  {
    PUSH_RP(*regPairArray[(opcode >> 4) & 0b00000011]);
  }
  // POP
  else if ((opcode & 0b11001111) == 0b11000001)
  {
    POP_RP(*regPairArray[(opcode >> 4) & 0b00000011]);
  }

  // Group-3

  else
  {
    std::cout << "Invalid opcode" << std::endl;
  }
}
