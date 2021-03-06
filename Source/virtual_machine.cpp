#include "virtual_machine.h"

#include <stdexcept>
#include <cstdio>
#include <iostream>

namespace Virtual_Machine
{

HOP :: HOP ( const Program& program )
:   m_instructions ( program.instructions )
,   ip             ( program.entryPoint )
{
}

//Reads the next instruction and executes it
void
HOP :: tick()
{
    fetchInstruction();
    executeInstruction();
}

//Checks for the next instruction. Can cause program to exit if the instruction
//pointer is out of range
void
HOP :: fetchInstruction ()
{
    try
    {
        m_currInstruction = static_cast<Instruction>(m_instructions.at( ip++ ) );
    }
    catch ( std::out_of_range e )
    {
        std::cout   << "Out of range: "     << ip
                    << ". Max range of: "   << m_instructions.size() - 1
                    << std::endl;
        m_isRunning = false;
    }
}

void
HOP :: executeInstruction ()
{
    switch ( m_currInstruction )
    {
        case Instruction::PUSH:
            m_stack[ ++sp ] = m_instructions[ip++];
            break;

        case Instruction::POP:
            sp--;
            break;

        case Instruction::ADD:
            a = m_stack[sp--];
            b = m_stack[sp--];
            c = a + b;
            sp++;
            m_stack[sp] = c;
            break;

        case Instruction::SUB:
            a = m_stack[sp--];
            b = m_stack[sp--];
            c = b - a;
            sp++;
            m_stack[sp] = c;
            break;

        case Instruction::PRINT:
            std::cout << m_stack[sp] << std::endl;
            break;

        case Instruction::JUMP:
            ip = m_instructions.at(ip);
            break;

        case Instruction::JIE:
            if ( m_stack[sp] == m_instructions.at( ip++ ) )
                ip = m_instructions.at( ip );
            else
                ip++;
            break;

        case Instruction::JIN:
            if ( m_stack[sp] != m_instructions.at( ip++ ) )
                ip = m_instructions.at( ip );
            else
                ip++;
            break;

        case Instruction::JIL:
            if ( m_stack[sp] < m_instructions.at( ip++ ) )
                ip = m_instructions.at( ip );
            else
                ip++;
            break;

        case Instruction::JIG:
            if ( m_stack[sp] > m_instructions.at( ip++ ) )
                ip = m_instructions.at( ip );
            else
                ip++;
            break;

        case Instruction::EXIT:
            m_isRunning = false;
            break;
    }
}

//Checks if the virtual_machine/ VM is still running
bool
HOP :: isRunning () const
{
    return m_isRunning;
}

//Helper function for the assembler to get the exit instruction.
//The purpose is for the program end and at the end of label sections
int
getEnd ()
{
    return static_cast<int>(Instruction::EXIT);
}

}
