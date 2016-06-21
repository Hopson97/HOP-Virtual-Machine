#include "assembler.h"

#include <iostream>
#include <fstream>
#include <cassert>

const std::map<std::string, CPU::Instruction> Assembler::strToIns =
{
    { "PUSH", CPU::Instruction::PUSH        },
    { "POP",  CPU::Instruction::POP         },
    { "ADD",  CPU::Instruction::ADD         },
    { "SUB",  CPU::Instruction::SUB         },
    { "PRINT",  CPU::Instruction::PRINT     },
    { "JUMP",   CPU::Instruction::JUMP      },
    { "EXIT", CPU::Instruction::EXIT        }
};

void
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
            m_instructions.push_back( m_inputNumber );
            m_numInstructions++;
        }
        else if ( m_inputString == "JUMP" )
        {
            addInstr();
            inFile >> m_inputString;
            m_instructions.push_back( m_jumps.at( m_inputString ) );
            m_numInstructions++;
        }
        else if ( wordFound( ":" ) )
        {
            if ( m_numInstructions != 0 )
                addEnd();
            m_jumps.emplace( m_inputString.substr(0, m_inputString.size() - 1 ),
                             m_numInstructions );

            if ( wordFound( "main" ) )
                m_mainLine = m_numInstructions;
        }
        else
        {
            addInstr();
        }
    }
    addEnd();

    assert ( m_instructions.size() > 0 );
    assert ( m_mainLine != -1 );
}

const std::vector <byte>&
Assembler :: getInstructions() const
{
    return m_instructions;
}

int
Assembler :: getMainLine () const
{
    return m_mainLine;
}

byte
Assembler :: toByte ( const CPU::Instruction i )
{
    return static_cast<byte>(i);
}

void
Assembler :: addInstr()
{
    try {
        m_instructions.push_back( toByte ( strToIns.at ( m_inputString ) ) );
        m_numInstructions++;
    }
    catch ( std::out_of_range e )
    {
        std::cout   << "The word "
                    << m_inputString
                    << " is not an instruction!" << std::endl;
    }
}

void
Assembler :: addEnd ()
{
    m_instructions.push_back( CPU::getEnd() );
    m_numInstructions++;
}

bool
Assembler :: wordFound( std::string wordOrChar ) const
{
    return m_inputString.find( wordOrChar ) != std::string::npos;
}
