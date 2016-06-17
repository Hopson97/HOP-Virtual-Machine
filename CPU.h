#ifndef CPU_H
#define CPU_H

#include <stack>
#include <vector>

typedef unsigned char byte;

namespace CPU
{

enum class Instruction
{
    PUSH,       //Pushes a value to top of stack eg "PUSH 5"
    POP,        //Removes value from top of stack
    ADD,        //Adds top two values to stack
    SUB,        //Subtracts top two values to stack
    PRINT,      //Prints top value of stack
    EXIT        //Exit the program
};

class Virtual_CPU //Lets call it "hop"
{
    public:
        Virtual_CPU     ( std::vector<byte>& listInstructions );

        void tick       ();

        bool isRunning  ();

    private:
        void getInstruction ();


        std::vector <byte>  m_instructions;

        int          m_stack[1024];

        bool         m_isRunning = true;

        Instruction m_currInstruction;

        /* REGISTERS */
        int a,          //General, currently not sure what this is
            b,
            c,
            ip = 0,     //Instruction pointer
            sp = -1;    //Stack pointer
};

}

#endif // CPU_H
