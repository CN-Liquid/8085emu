#include <8085.h>
#include <iostream>

int main(int argc, char *argv[])
{
  bool exit = 0;
  emu8085 test;
  std::string arg;
  test.reset();
  test.mem[0] = 0b00111110;
  test.mem[1] = 1;
  test.mem[2] = 0b01110110;
  test.execute();

  test.print_reg();
  std::cout << int(test.mem[2100]);

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