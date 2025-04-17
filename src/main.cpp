#include <8085.h>
#include <iostream>

int main(int argc, char *argv[]) {
  bool exit = 0;
  emu8085 test;
  std::string arg;
  test.reset();

  byte arr[] = {0x3E, 0x1,  0x06, 0x2,  0x90, 0xD2, 0x00, 0xb,
                0x0C, 0x2F, 0x3C, 0x32, 0x21, 0x00, 0x79, 0x76};

  for (int i = 0; i < 16; i++) {
    test.DB = arr[i];
    test.mem_write(i);
  }

  test.execute();

  // test.print_reg();
  // std::cout << int(test.mem[2100]);

  /*
  while(!exit)
  {
      std::cout<<">>";
      std::getline(std::cin, arg);
      if(arg == "exit")
      {
          exit = 1;
      }
  }*/

  return 0;
}