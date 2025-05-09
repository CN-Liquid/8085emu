#include <8085.h>

void emu8085::load_reg_pair(byte &regPair, word data) {
  regPair = byte(data >> 8);
  *(&regPair + sizeof(regPair)) = byte(data);
}
void emu8085::load_reg(byte &reg, byte data) { reg = data; }
void emu8085::load_DB(byte data) { DB = data; }