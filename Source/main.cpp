#include "virtual_machine.h"
#include "assembler.h"

int main()
{
    Assembler assumbler;

    Virtual_Machine::HOP hop_machine( assumbler.assemble( "dot hops/test.hop" ) );

    while( hop_machine.isRunning() )
    {
        hop_machine.tick();
    }

    return 0;
}
