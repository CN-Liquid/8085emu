#include<iostream>
#include<8085.h>

int main(int argc , char* argv[])
{
    emu8085 test;
    std::cout<<"struct size : "<< sizeof(test)<<std::endl;
    return 0;
}