#include<iostream>
#include<8085.h>

int main(int argc , char* argv[])
{
    emu8085 test;
    test.reset();
    test.print_reg();
    return 0;
}