#include <8085.h>

static std::unordered_map<byte, std::function<void()>> instructions;

void emu8085::initializeInstructionTable() {

  instructions[0x00] = std::bind(&emu8085::NOP, this);
  instructions[0x3A] = std::bind(&emu8085::LDA_M, this);
  instructions[0x2A] = std::bind(&emu8085::LHLD_D, this);
  instructions[0x32] = std::bind(&emu8085::STA_M, this);
  instructions[0x22] = std::bind(&emu8085::SHLD_M, this);
  instructions[0xEB] = std::bind(&emu8085::XCHG, this);
  instructions[0x36] = std::bind(&emu8085::MVI_M_D, this);

  instructions[0x86] = std::bind(&emu8085::ADD_M, this);
  instructions[0x8E] = std::bind(&emu8085::ADC_M, this);
  instructions[0xC6] = std::bind(&emu8085::ADI_D, this);
  instructions[0xCE] = std::bind(&emu8085::ACI_D, this);

  instructions[0x96] = std::bind(&emu8085::SUB_M, this);
  instructions[0x9E] = std::bind(&emu8085::SBB_M, this);
  instructions[0xD6] = std::bind(&emu8085::SUI_D, this);
  instructions[0xDE] = std::bind(&emu8085::SBI_D, this);

  instructions[0x34] = std::bind(&emu8085::INR_M, this);

  instructions[0x35] = std::bind(&emu8085::DCR_M, this);

  instructions[0xBD] = std::bind(&emu8085::CMP_M, this);
  instructions[0xFE] = std::bind(&emu8085::CPI_D, this);
  instructions[0xA6] = std::bind(&emu8085::ANA_M, this);
  instructions[0xE6] = std::bind(&emu8085::ANI_D, this);
  instructions[0xAE] = std::bind(&emu8085::XRA_M, this);
  instructions[0xEE] = std::bind(&emu8085::XRI_D, this);
  instructions[0xB6] = std::bind(&emu8085::ORA_M, this);
  instructions[0xF6] = std::bind(&emu8085::ORI_D, this);

  instructions[0x07] = std::bind(&emu8085::RLC, this);
  instructions[0x0F] = std::bind(&emu8085::RRC, this);
  instructions[0x17] = std::bind(&emu8085::RAL, this);
  instructions[0x1F] = std::bind(&emu8085::RAR, this);
  instructions[0x2F] = std::bind(&emu8085::CMA, this);
  instructions[0x3F] = std::bind(&emu8085::CMC, this);
  instructions[0x37] = std::bind(&emu8085::STC, this);

  instructions[0xC3] = std::bind(&emu8085::JMP_M, this);
  instructions[0xDA] = std::bind(&emu8085::JC_M, this);
  instructions[0xD2] = std::bind(&emu8085::JNC_M, this);
  instructions[0xF2] = std::bind(&emu8085::JP_M, this);
  instructions[0xFA] = std::bind(&emu8085::JM_M, this);
  instructions[0xCA] = std::bind(&emu8085::JZ_M, this);
  instructions[0xC2] = std::bind(&emu8085::JNZ_M, this);
  instructions[0xEA] = std::bind(&emu8085::JPE_M, this);
  instructions[0xE2] = std::bind(&emu8085::JPO_M, this);

  instructions[0xCD] = std::bind(&emu8085::CALL_M, this);
  instructions[0xDC] = std::bind(&emu8085::CC_M, this);
  instructions[0xD4] = std::bind(&emu8085::CNC_M, this);
  instructions[0xF4] = std::bind(&emu8085::CP_M, this);
  instructions[0xFC] = std::bind(&emu8085::CM_M, this);
  instructions[0xDA] = std::bind(&emu8085::CZ_M, this);
  instructions[0xCC] = std::bind(&emu8085::CNZ_M, this);
  instructions[0xEC] = std::bind(&emu8085::CPE_M, this);
  instructions[0xE4] = std::bind(&emu8085::CPO_M, this);

  instructions[0xC9] = std::bind(&emu8085::RET, this);
  instructions[0xD8] = std::bind(&emu8085::RC, this);
  instructions[0xD0] = std::bind(&emu8085::RNC, this);
  instructions[0xF0] = std::bind(&emu8085::RP, this);
  instructions[0xF8] = std::bind(&emu8085::RM, this);
  instructions[0xC8] = std::bind(&emu8085::RZ, this);
  instructions[0xC0] = std::bind(&emu8085::RNZ, this);
  instructions[0xE8] = std::bind(&emu8085::RPE, this);
  instructions[0xE0] = std::bind(&emu8085::RPO, this);

  instructions[0x76] = std::bind(&emu8085::HLT, this);
  instructions[0x00] = std::bind(&emu8085::NOP, this);

  /******One Argument Instructions******/

  instructions[0x7E] = std::bind(&emu8085::MOV_R_M, this, std::ref(this->A));
  instructions[0x46] = std::bind(&emu8085::MOV_R_M, this, std::ref(this->B));
  instructions[0x4E] = std::bind(&emu8085::MOV_R_M, this, std::ref(this->C));
  instructions[0x56] = std::bind(&emu8085::MOV_R_M, this, std::ref(this->D));
  instructions[0x5E] = std::bind(&emu8085::MOV_R_M, this, std::ref(this->E));
  instructions[0x66] = std::bind(&emu8085::MOV_R_M, this, std::ref(this->H));
  instructions[0x6E] = std::bind(&emu8085::MOV_R_M, this, std::ref(this->L));

  instructions[0x77] = std::bind(&emu8085::MOV_R_M, this, std::ref(this->A));
  instructions[0x70] = std::bind(&emu8085::MOV_R_M, this, std::ref(this->B));
  instructions[0x71] = std::bind(&emu8085::MOV_R_M, this, std::ref(this->C));
  instructions[0x72] = std::bind(&emu8085::MOV_R_M, this, std::ref(this->D));
  instructions[0x73] = std::bind(&emu8085::MOV_R_M, this, std::ref(this->E));
  instructions[0x74] = std::bind(&emu8085::MOV_R_M, this, std::ref(this->H));
  instructions[0x75] = std::bind(&emu8085::MOV_R_M, this, std::ref(this->L));

  instructions[0x3E] = std::bind(&emu8085::MVI_R_D, this, std::ref(this->A));
  instructions[0x06] = std::bind(&emu8085::MVI_R_D, this, std::ref(this->B));
  instructions[0x0E] = std::bind(&emu8085::MVI_R_D, this, std::ref(this->C));
  instructions[0x16] = std::bind(&emu8085::MVI_R_D, this, std::ref(this->D));
  instructions[0x1E] = std::bind(&emu8085::MVI_R_D, this, std::ref(this->E));
  instructions[0x26] = std::bind(&emu8085::MVI_R_D, this, std::ref(this->H));
  instructions[0x2E] = std::bind(&emu8085::MVI_R_D, this, std::ref(this->L));

  instructions[0x01] = std::bind(&emu8085::LXI_RP_D, this, std::ref(this->B));
  instructions[0x11] = std::bind(&emu8085::LXI_RP_D, this, std::ref(this->D));
  instructions[0x21] = std::bind(&emu8085::LXI_RP_D, this, std::ref(this->E));
  instructions[0x31] = std::bind(&emu8085::LXI_RP_D, this, std::ref(this->SPU));

  instructions[0x0A] = std::bind(&emu8085::LDAX_RP, this, std::ref(this->B));
  instructions[0x1A] = std::bind(&emu8085::LDAX_RP, this, std::ref(this->D));

  instructions[0x02] = std::bind(&emu8085::STAX_RP, this, std::ref(this->B));
  instructions[0x12] = std::bind(&emu8085::STAX_RP, this, std::ref(this->D));

  instructions[0x87] = std::bind(&emu8085::ADD_R, this, std::ref(this->A));
  instructions[0x80] = std::bind(&emu8085::ADD_R, this, std::ref(this->B));
  instructions[0x81] = std::bind(&emu8085::ADD_R, this, std::ref(this->C));
  instructions[0x82] = std::bind(&emu8085::ADD_R, this, std::ref(this->D));
  instructions[0x83] = std::bind(&emu8085::ADD_R, this, std::ref(this->E));
  instructions[0x84] = std::bind(&emu8085::ADD_R, this, std::ref(this->H));
  instructions[0x85] = std::bind(&emu8085::ADD_R, this, std::ref(this->L));

  instructions[0x8F] = std::bind(&emu8085::ADC_R, this, std::ref(this->A));
  instructions[0x88] = std::bind(&emu8085::ADC_R, this, std::ref(this->B));
  instructions[0x89] = std::bind(&emu8085::ADC_R, this, std::ref(this->C));
  instructions[0x8A] = std::bind(&emu8085::ADC_R, this, std::ref(this->D));
  instructions[0x8B] = std::bind(&emu8085::ADC_R, this, std::ref(this->E));
  instructions[0x8C] = std::bind(&emu8085::ADC_R, this, std::ref(this->H));
  instructions[0x8D] = std::bind(&emu8085::ADC_R, this, std::ref(this->L));

  instructions[0x09] = std::bind(&emu8085::DAD_RP, this, std::ref(this->B));
  instructions[0x19] = std::bind(&emu8085::DAD_RP, this, std::ref(this->D));
  instructions[0x29] = std::bind(&emu8085::DAD_RP, this, std::ref(this->H));
  instructions[0x39] = std::bind(&emu8085::DAD_RP, this, std::ref(this->SPU));

  instructions[0x97] = std::bind(&emu8085::SUB_R, this, std::ref(this->A));
  instructions[0x90] = std::bind(&emu8085::SUB_R, this, std::ref(this->B));
  instructions[0x91] = std::bind(&emu8085::SUB_R, this, std::ref(this->C));
  instructions[0x92] = std::bind(&emu8085::SUB_R, this, std::ref(this->D));
  instructions[0x93] = std::bind(&emu8085::SUB_R, this, std::ref(this->E));
  instructions[0x94] = std::bind(&emu8085::SUB_R, this, std::ref(this->H));
  instructions[0x95] = std::bind(&emu8085::SUB_R, this, std::ref(this->L));

  instructions[0x9F] = std::bind(&emu8085::SBB_R, this, std::ref(this->A));
  instructions[0x98] = std::bind(&emu8085::SBB_R, this, std::ref(this->B));
  instructions[0x99] = std::bind(&emu8085::SBB_R, this, std::ref(this->C));
  instructions[0x9A] = std::bind(&emu8085::SBB_R, this, std::ref(this->D));
  instructions[0x9B] = std::bind(&emu8085::SBB_R, this, std::ref(this->E));
  instructions[0x9C] = std::bind(&emu8085::SBB_R, this, std::ref(this->H));
  instructions[0x9D] = std::bind(&emu8085::SBB_R, this, std::ref(this->L));

  instructions[0x3C] = std::bind(&emu8085::INR_R, this, std::ref(this->A));
  instructions[0x04] = std::bind(&emu8085::INR_R, this, std::ref(this->B));
  instructions[0x0C] = std::bind(&emu8085::INR_R, this, std::ref(this->C));
  instructions[0x14] = std::bind(&emu8085::INR_R, this, std::ref(this->D));
  instructions[0x1C] = std::bind(&emu8085::INR_R, this, std::ref(this->E));
  instructions[0x24] = std::bind(&emu8085::INR_R, this, std::ref(this->H));
  instructions[0x2C] = std::bind(&emu8085::INR_R, this, std::ref(this->L));

  instructions[0x03] = std::bind(&emu8085::INX_RP, this, std::ref(this->B));
  instructions[0x13] = std::bind(&emu8085::INX_RP, this, std::ref(this->D));
  instructions[0x23] = std::bind(&emu8085::INX_RP, this, std::ref(this->H));
  instructions[0x33] = std::bind(&emu8085::INX_RP, this, std::ref(this->SPU));

  instructions[0x3D] = std::bind(&emu8085::DCR_R, this, std::ref(this->A));
  instructions[0x05] = std::bind(&emu8085::DCR_R, this, std::ref(this->B));
  instructions[0x0D] = std::bind(&emu8085::DCR_R, this, std::ref(this->C));
  instructions[0x15] = std::bind(&emu8085::DCR_R, this, std::ref(this->D));
  instructions[0x1D] = std::bind(&emu8085::DCR_R, this, std::ref(this->E));
  instructions[0x25] = std::bind(&emu8085::DCR_R, this, std::ref(this->H));
  instructions[0x2D] = std::bind(&emu8085::DCR_R, this, std::ref(this->L));

  instructions[0x0B] = std::bind(&emu8085::DCX_RP, this, std::ref(this->B));
  instructions[0x1B] = std::bind(&emu8085::DCX_RP, this, std::ref(this->D));
  instructions[0x2B] = std::bind(&emu8085::DCX_RP, this, std::ref(this->H));
  instructions[0x3B] = std::bind(&emu8085::DCX_RP, this, std::ref(this->SPU));

  instructions[0xBF] = std::bind(&emu8085::CMP_R, this, std::ref(this->A));
  instructions[0xB8] = std::bind(&emu8085::CMP_R, this, std::ref(this->B));
  instructions[0xB9] = std::bind(&emu8085::CMP_R, this, std::ref(this->C));
  instructions[0xBA] = std::bind(&emu8085::CMP_R, this, std::ref(this->D));
  instructions[0xBB] = std::bind(&emu8085::CMP_R, this, std::ref(this->E));
  instructions[0xBC] = std::bind(&emu8085::CMP_R, this, std::ref(this->H));
  instructions[0xBD] = std::bind(&emu8085::CMP_R, this, std::ref(this->L));

  instructions[0xA7] = std::bind(&emu8085::ANA_R, this, std::ref(this->A));
  instructions[0xA0] = std::bind(&emu8085::ANA_R, this, std::ref(this->B));
  instructions[0xA1] = std::bind(&emu8085::ANA_R, this, std::ref(this->C));
  instructions[0xA2] = std::bind(&emu8085::ANA_R, this, std::ref(this->D));
  instructions[0xA3] = std::bind(&emu8085::ANA_R, this, std::ref(this->E));
  instructions[0xA4] = std::bind(&emu8085::ANA_R, this, std::ref(this->H));
  instructions[0xA5] = std::bind(&emu8085::ANA_R, this, std::ref(this->L));

  instructions[0xAF] = std::bind(&emu8085::XRA_R, this, std::ref(this->A));
  instructions[0xA8] = std::bind(&emu8085::XRA_R, this, std::ref(this->B));
  instructions[0xA9] = std::bind(&emu8085::XRA_R, this, std::ref(this->C));
  instructions[0xAA] = std::bind(&emu8085::XRA_R, this, std::ref(this->D));
  instructions[0xAB] = std::bind(&emu8085::XRA_R, this, std::ref(this->E));
  instructions[0xAC] = std::bind(&emu8085::XRA_R, this, std::ref(this->H));
  instructions[0xAD] = std::bind(&emu8085::XRA_R, this, std::ref(this->L));

  instructions[0xB7] = std::bind(&emu8085::ORA_R, this, std::ref(this->A));
  instructions[0xB0] = std::bind(&emu8085::ORA_R, this, std::ref(this->B));
  instructions[0xB1] = std::bind(&emu8085::ORA_R, this, std::ref(this->C));
  instructions[0xB2] = std::bind(&emu8085::ORA_R, this, std::ref(this->D));
  instructions[0xB3] = std::bind(&emu8085::ORA_R, this, std::ref(this->E));
  instructions[0xB4] = std::bind(&emu8085::ORA_R, this, std::ref(this->H));
  instructions[0xB5] = std::bind(&emu8085::ORA_R, this, std::ref(this->L));

  instructions[0xC5] = std::bind(&emu8085::PUSH_RP, this, std::ref(this->B));
  instructions[0xD5] = std::bind(&emu8085::PUSH_RP, this, std::ref(this->D));
  instructions[0xE5] = std::bind(&emu8085::PUSH_RP, this, std::ref(this->H));

  /******Two Argument Instructions******/

  instructions[0x7F] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->A), std::ref(this->A));
  instructions[0x78] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->A), std::ref(this->B));
  instructions[0x79] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->A), std::ref(this->C));
  instructions[0x7A] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->A), std::ref(this->D));
  instructions[0x7B] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->A), std::ref(this->E));
  instructions[0x7C] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->A), std::ref(this->H));
  instructions[0x7D] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->A), std::ref(this->L));

  instructions[0x47] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->B), std::ref(this->A));
  instructions[0x40] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->B), std::ref(this->B));
  instructions[0x41] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->B), std::ref(this->C));
  instructions[0x42] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->B), std::ref(this->D));
  instructions[0x43] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->B), std::ref(this->E));
  instructions[0x44] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->B), std::ref(this->H));
  instructions[0x45] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->B), std::ref(this->L));

  instructions[0x4F] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->C), std::ref(this->A));
  instructions[0x48] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->C), std::ref(this->B));
  instructions[0x49] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->C), std::ref(this->C));
  instructions[0x4A] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->C), std::ref(this->D));
  instructions[0x4B] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->C), std::ref(this->E));
  instructions[0x4C] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->C), std::ref(this->H));
  instructions[0x4D] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->C), std::ref(this->L));

  instructions[0x57] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->D), std::ref(this->A));
  instructions[0x50] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->D), std::ref(this->B));
  instructions[0x51] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->D), std::ref(this->C));
  instructions[0x52] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->D), std::ref(this->D));
  instructions[0x53] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->D), std::ref(this->E));
  instructions[0x54] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->D), std::ref(this->H));
  instructions[0x55] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->D), std::ref(this->L));

  instructions[0x5F] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->E), std::ref(this->A));
  instructions[0x58] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->E), std::ref(this->B));
  instructions[0x59] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->E), std::ref(this->C));
  instructions[0x5A] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->E), std::ref(this->D));
  instructions[0x5B] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->E), std::ref(this->E));
  instructions[0x5C] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->E), std::ref(this->H));
  instructions[0x5D] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->E), std::ref(this->L));

  instructions[0x67] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->H), std::ref(this->A));
  instructions[0x60] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->H), std::ref(this->B));
  instructions[0x61] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->H), std::ref(this->C));
  instructions[0x62] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->H), std::ref(this->D));
  instructions[0x63] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->H), std::ref(this->E));
  instructions[0x64] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->H), std::ref(this->H));
  instructions[0x65] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->H), std::ref(this->L));

  instructions[0x6F] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->L), std::ref(this->A));
  instructions[0x68] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->L), std::ref(this->B));
  instructions[0x69] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->L), std::ref(this->C));
  instructions[0x6A] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->L), std::ref(this->D));
  instructions[0x6B] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->L), std::ref(this->E));
  instructions[0x6C] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->L), std::ref(this->H));
  instructions[0x6D] =
      std::bind(&emu8085::MOV_R_R, this, std::ref(this->L), std::ref(this->L));
}

std::function<void()> emu8085::function_recognizer(byte opcode) {

  if (instructions.find(opcode) != instructions.end()) {
    return instructions.at(opcode);
  } else {
    std::cout << "Invalid opcode" << std::endl;
    exit(1);
  }
}