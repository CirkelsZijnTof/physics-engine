#include "phys_1.hpp"
#include "consoleUtil.hpp"
#include "function_evaluator.hpp"

#include <limits>

// D:\msys\ucrt64\bin\g++.exe phys_1.cpp icons\app.res -o executables\phys_1.exe

int main() 
{

    Phys_Framework ENGINE;
    Phys_Object_v1 OBJECT;
    ConsoleUtils UTILS;
    Probe PROBE;

    std::array<double, 2> start_position = {0, 100}; // create start position (x, y)

    OBJECT.setPosition(start_position); // set the position of the object

    ENGINE.setEnvironmentVariables();

    OBJECT.setEnvironmentVariables();

    while(ENGINE.steps > 0) 
    {
        
        ENGINE.move(OBJECT);
        ENGINE.updateStepCounter();

        if (OBJECT.has_landed) 
        {
            break;
        }

    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    
    return 0;
};