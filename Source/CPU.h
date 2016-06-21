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
    JUMP,
    EXIT,        //Exit the program
    END
};

int getEnd ();


class Virtual_CPU //Lets call it "hop"
{
    public:
        Virtual_CPU     ( const std::vector<byte>& listInstructions, const int main );

        void tick       ();

        bool isRunning  () const;

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
            ip,         //Instruction pointer
            sp = -1;    //Stack pointer
};

}

#endif // CPU_H
