#include "CPU.h"
#include "assembler.h"

int main()
{
    Assembler assumbler;

    CPU::Virtual_CPU cpu( assumbler.assemble( "dot hops/test.hop" ) );

    while( cpu.isRunning() )
    {
        cpu.tick();
    }

    return 0;
}
