#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include <stack>
#include <vector>

typedef unsigned char byte;

namespace Virtual_Machine
{

enum class Instruction
{
    PUSH,       //Pushes a value to top of stack eg "PUSH 5"
    POP,        //Removes value from top of stack
    ADD,        //Adds top two values to stack
    SUB,        //Subtracts top two values to stack
    PRINT,      //Prints top value of stack
    JUMP,
    EXIT        //Exit the program
};

int getEnd ();

struct Program
{
    std::vector <byte>  instructions;
    int entryPoint = -1;
};


class HOP //Lets call it "hop"
{
    public:
        HOP     ( const Program& program );

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

#endif // virtual_machine_H
