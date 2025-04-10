#include <8085.h>
#include <iostream>

int main(int argc, char *argv[]) {
  bool exit = 0;
  emu8085 test;
  std::string arg;
  test.reset();
  test.MVI_R_D(test.A, 19);
  test.MVI_R_D(test.B, 20);
  test.MVI_R_D(test.C, 0);
  test.SUB_R(test.B);
  if (test.CY == 0) {
    goto skip;
  }
  test.INR_R(test.C);
  test.CMA();
  test.INR_R(test.A);
skip:
  test.STA_M(2100);
  // test.MOV_R_R(test.A, test.C);

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