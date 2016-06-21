#include "CPU.h"
#include "assembler.h"

int main()
{
    Assembler assumbler;
    assumbler.assemble( "dot hops/test.hop" );

    CPU::Virtual_CPU cpu( assumbler.getInstructions(), assumbler.getMainLine() );

    while( cpu.isRunning() )
    {
        cpu.tick();
    }

    return 0;
}
