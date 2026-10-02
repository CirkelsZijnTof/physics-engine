#include "phys_1.hpp"
#include "consoleUtil.hpp"
#include "function_evaluator.hpp"

// D:\msys\ucrt64\bin\g++.exe phys_1.cpp icons\app.res -o executables\phys_1.exe

int main() {

    Phys_Framework ENGINE;
    Phys_Object_v1 OBJECT;
    ConsoleUtils UTILS;
    Probe PROBE;

    while(true) 
    {
        
        ENGINE.update(OBJECT, 0.001, true);

    }    

    std::cin.get();
    
    return 0;
};