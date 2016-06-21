#include "assembler.h"

#include <iostream>
#include <fstream>
#include <cassert>

const std::map<std::string, Virtual_Machine::Instruction> Assembler::strToIns =
{
    { "PUSH",   Virtual_Machine::Instruction::PUSH        },
    { "POP",    Virtual_Machine::Instruction::POP         },
    { "ADD",    Virtual_Machine::Instruction::ADD         },
    { "SUB",    Virtual_Machine::Instruction::SUB         },
    { "PRINT",  Virtual_Machine::Instruction::PRINT     },
    { "JUMP",   Virtual_Machine::Instruction::JUMP      },
    { "EXIT",   Virtual_Machine::Instruction::EXIT        }
};

//Assembles the .hop file into a list of unsigned char that the VM can
//understand
const Virtual_Machine::Program&
Assembler :: assemble ( const std::string& fileName )
{
    std::ifstream inFile;
    inFile.open( fileName );

    while ( inFile >> m_inputString )
    {
        if ( m_inputString == "PUSH" )
        {
            addInstr();
            inFile >> m_inputNumber;
            m_program.instructions.push_back( m_inputNumber );
            m_numInstructions++;
        }
        else if ( m_inputString == "JUMP" )
        {
            addInstr();
            inFile >> m_inputString;
            m_program.instructions.push_back( m_jumps.at( m_inputString ) );
            m_numInstructions++;
        }
        else if ( wordFound( ":" ) ) //A label
        {
            if ( m_numInstructions != 0 )
                addEnd();
            m_jumps.emplace( m_inputString.substr(0, m_inputString.size() - 1 ),
                             m_numInstructions );

            if ( wordFound( "main" ) )  //Entry point of the program found
                m_program.entryPoint = m_numInstructions;
        }
        else
        {
            addInstr();
        }
    }
    addEnd();

    assert ( m_program.instructions.size() > 0 );
    assert ( m_program.entryPoint != -1 );

    return m_program;
}

//Converts a enum into a "byte"
byte
Assembler :: toByte ( const Virtual_Machine::Instruction i )
{
    return static_cast<byte>(i);
}

//Adds an instruction into the list of them
void
Assembler :: addInstr()
{
    try {
        m_program.instructions.push_back( toByte ( strToIns.at ( m_inputString ) ) );
        m_numInstructions++;
    }
    catch ( std::out_of_range e )
    {
        std::cout   << "The word "
                    << m_inputString
                    << " is not an instruction!" << std::endl;
    }
}

//Adds "exit" label into the instructions.
//This is done at the end of the program and at labels
void
Assembler :: addEnd ()
{
    m_program.instructions.push_back( Virtual_Machine::getEnd() );
    m_numInstructions++;
}

//Checks if a specific word or char is present in the input string
bool
Assembler :: wordFound( std::string wordOrChar ) const
{
    return m_inputString.find( wordOrChar ) != std::string::npos;
}
