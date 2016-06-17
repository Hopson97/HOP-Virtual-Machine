#include "CPU.h"

#include <stdexcept>
#include <cstdio>
#include <iostream>

namespace CPU
{

Virtual_CPU :: Virtual_CPU ( std::vector<byte>& listInstructions )
:   m_instructions ( std::move ( listInstructions ) )
{

}

void
Virtual_CPU :: tick()
{
    getInstruction();

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
            c = a - b;
            sp++;
            m_stack[sp] = c;
            break;

        case Instruction::PRINT:
            std::cout << m_stack[sp] << std::endl;
            break;

        case Instruction::EXIT:
            m_isRunning = false;
            break;

    }
}

void
Virtual_CPU :: getInstruction ()
{
    try
    {
        m_currInstruction = static_cast<Instruction>(m_instructions.at( ip++ ) );
    }
    catch ( std::out_of_range e )
    {
        m_isRunning = false;
    }
}

bool
Virtual_CPU :: isRunning ()
{
    return m_isRunning;
}

}
