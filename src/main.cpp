#include <8085.h>
#include <iostream>

int main(int argc, char *argv[]) {
  bool exit = 0;
  emu8085 test;
  std::string arg;
  test.reset();

  test.load_DB(0x3A);
  test.mem_write(0x0000);
  test.load_DB(0x00);
  test.mem_write(0x0001);
  test.load_DB(0x21);
  test.mem_write(0x0002);
  test.load_DB(0x47);
  test.mem_write(0x0003);
  test.load_DB(0x3A);
  test.mem_write(0x0004);
  test.load_DB(0x01);
  test.mem_write(0x0005);
  test.load_DB(0x21);
  test.mem_write(0x0006);
  test.load_DB(0x4F);
  test.mem_write(0x0007);
  test.load_DB(0x76);
  test.mem_write(0x0008);

  test.load_DB(0x10);
  test.mem_write(0x2100);
  test.load_DB(0x10);
  test.mem_write(0x2101);

  test.execute();

  test.print_reg();

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