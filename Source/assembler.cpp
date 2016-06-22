#include "assembler.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>

const std::string push  = "PUSH";
const std::string pop   = "POP";

const std::string add   = "ADD";
const std::string sub   = "SUB";

const std::string print = "PRINT";

const std::string jump  = "JUMP";
const std::string jie   = "JIE";
const std::string jin   = "JIN";
const std::string jil   = "JIL";
const std::string jig   = "JIG";

const std::string end  = "EXIT";


const std::map< const std::string, Virtual_Machine::Instruction> Assembler::strToIns =
{
    { push,   Virtual_Machine::Instruction::PUSH  },
    { pop,    Virtual_Machine::Instruction::POP   },

    { add,    Virtual_Machine::Instruction::ADD   },
    { sub,    Virtual_Machine::Instruction::SUB   },

    { print,  Virtual_Machine::Instruction::PRINT },

    { jump,   Virtual_Machine::Instruction::JUMP  },
    { jie,    Virtual_Machine::Instruction::JIE  },
    { jin,    Virtual_Machine::Instruction::JIN  },
    { jil,    Virtual_Machine::Instruction::JIL  },
    { jig,    Virtual_Machine::Instruction::JIG  },

    { end,   Virtual_Machine::Instruction::EXIT  }
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
        if ( m_inputString == push )
        {
            addPush( inFile );
        }
        else if ( m_inputString == jump )
        {
            addJump( inFile, true );

        }
        else if ( m_inputString == jie ||
                  m_inputString == jin ||
                  m_inputString == jil ||
                  m_inputString == jig )
        {
            addComparitiveJump( inFile );
        }
        else if ( wordFound( ":" ) ) //A label
        {
            addLabel();
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


//Adds the push instruction into the push
void
Assembler :: addPush ( std::ifstream& inFile )
{
    addInstr();
    inFile >> m_inputNumber;
    m_program.instructions.push_back( m_inputNumber );
    m_numInstructions++;
}


void
Assembler :: addJump ( std::ifstream& inFile, bool initialAddInstr )
{
    if ( initialAddInstr )
        addInstr();

    inFile >> m_inputString;

    try
    {
        m_program.instructions.push_back( m_jumps.at( m_inputString ) );
    }
    catch ( std::out_of_range e )
    {
        std::cout << "Unrecognised label \" " << m_inputString << "\"." << std::endl;
        exit ( -1 );
    }
    m_numInstructions++;
}

void
Assembler :: addComparitiveJump( std::ifstream& inFile )
{
    addInstr();
    inFile >> m_inputNumber;
    m_program.instructions.push_back( m_inputNumber );
    addJump( inFile );
    m_numInstructions++;
}


void
Assembler :: addLabel ()
{
    if ( m_numInstructions != 0 )
        addEnd();
    m_jumps.emplace( m_inputString.substr(0, m_inputString.size() - 1 ),
                     m_numInstructions );

    if ( wordFound( "main" ) )  //Entry point of the program found
        m_program.entryPoint = m_numInstructions;
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
