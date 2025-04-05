#include<iostream>
#include<8085.h>



int main(int argc , char* argv[])
{
    bool exit = 0;
    emu8085 test;
    std::string arg;
    test.reset();
    test.MVI_R_D(test.H , 35);
    test.MVI_R_D(test.A , 20);
    test.CMP_R(test.H);
    test.print_reg();
    
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