#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <map>
#include "CPU.h"

class Assembler
{
    public:
        const CPU::Program& assemble ( const std::string& fileName );

    private:
        byte toByte     ( const CPU::Instruction i );

        void addInstr   ();
        void addEnd     ();

        bool wordFound  ( std::string wordOrChar ) const;

        /* DATA */
        std::map <std::string, int>     m_jumps;
        std::string     m_inputString;

        int             m_inputNumber;
        unsigned        m_numInstructions = 0;

        CPU::Program         m_program;

        const static std::map<std::string, CPU::Instruction> strToIns;
};

#endif // ASSEMBLER_H
