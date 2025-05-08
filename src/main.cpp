#include <8085.h>
#include <iostream>

int main(int argc, char *argv[]) {
  bool exit = 0;
  emu8085 test;
  std::string arg;
  test.reset();

  byte arr[] = {0x3A, 0x10, 0x20, 0x0E, 0x08, 0x16, 0x00, 0x1E, 0x00, 0x0F,
                0xD2, 0x14, 0x00, 0xDA, 0x10, 0x00, 0x14, 0xC3, 0x18, 0x00,
                0x1C, 0xC3, 0x18, 0x00, 0x0D, 0xC2, 0x09, 0x00, 0x76};
  test.load_DB(0x9E);
  test.mem_write(0x2010);
  for (int i = 0; i < 29; i++) {
    test.load_DB(arr[i]);
    test.mem_write(i);
  }
  test.print(0x2010);

  // test.execute();

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