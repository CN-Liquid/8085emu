#include<iostream>
#include<8085.h>



int main(int argc , char* argv[])
{
    bool exit = 0;
    emu8085 test;
    std::string arg;
    test.reset();
    test.LXI_RP_D(test.H , 2000);
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