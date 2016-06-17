#include <iostream>
#include <map>
#include <fstream>
#include <cassert>

#include "CPU.h"

std::map<std::string, CPU::Instruction> strToIns =
{
    { "PUSH", CPU::Instruction::PUSH        },
    { "POP",  CPU::Instruction::POP         },
    { "ADD",  CPU::Instruction::ADD         },
    { "SUB",  CPU::Instruction::SUB         },
    { "PRINT",  CPU::Instruction::PRINT     },
    { "EXIT", CPU::Instruction::EXIT        }
};

std::vector<byte> instructions;
int intput;
std::string input;

byte
toByte ( const CPU::Instruction i );

void
addInstr ();

/*
    The main functions reads a file and parses into "bytes" that my
    "CPU" can understand
*/
int main()
{
    std::ifstream inFile;
    inFile.open( "test.hop" );

    while ( inFile >> input )
    {
        if ( input == "PUSH" )
        {
            addInstr();
            inFile >> intput;
            instructions.push_back( intput );
        }
        else
        {
            addInstr();
        }

    }

    assert ( instructions.size() > 0 );

    CPU::Virtual_CPU cpu( instructions );

    while( cpu.isRunning() )
    {
        cpu.tick();
    }


    return 0;
}

byte
toByte ( const CPU::Instruction i )
{
    return static_cast<byte>(i);
}

void
addInstr()
{
    try {
        instructions.push_back( toByte ( strToIns.at ( input ) ) );
    }
    catch ( std::out_of_range e )
    {
        std::cout << "The word " << input << " is not an instruction!" << std::endl;
    }
}
