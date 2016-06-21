#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <map>
#include "CPU.h"

class Assembler
{
    public:
        void assemble (const std::string& fileName );

        const std::vector <byte>& getInstructions() const;

        int getMainLine () const;

    private:
        byte toByte     ( const CPU::Instruction i );

        void addInstr   ();
        void addEnd     ();

        bool wordFound  ( std::string wordOrChar ) const;

        /* DATA */
        std::vector <byte>              m_instructions;
        std::map <std::string, int>     m_jumps;

        std::string     m_inputString;

        int             m_mainLine;
        int             m_inputNumber;
        unsigned        m_numInstructions = 0;

        const static std::map<std::string, CPU::Instruction> strToIns;
};

#endif // ASSEMBLER_H
