#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <map>
#include "virtual_machine.h"

class Assembler
{
    public:
        const Virtual_Machine::Program& assemble ( const std::string& fileName );

    private:
        byte toByte     ( const Virtual_Machine::Instruction i );

        void addInstr   ();
        void addEnd     ();

        void addPush    ( std::ifstream& inFile );

        void addJump    ( std::ifstream& inFile, bool initialAddInstr = false );
        void addComparitiveJump( std::ifstream& inFile );


        void addLabel   ();


        bool wordFound  ( std::string wordOrChar ) const;

        /* DATA */
        std::map <std::string, int>     m_jumps;
        std::string     m_inputString;

        int             m_inputNumber;
        unsigned        m_numInstructions = 0;

        Virtual_Machine::Program         m_program;

        const static std::map< const std::string, Virtual_Machine::Instruction> strToIns;
};

#endif // ASSEMBLER_H
