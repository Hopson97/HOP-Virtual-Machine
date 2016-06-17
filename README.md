# HOP-Virtual-Machine
I'm learning about how the CPU works, and so I decided to try make one :P

It is a simple "CPU", however I'm not 100% certain I am "doing it right".

So far the instructions for it :

| Value | Instruction | Notes                             | DOES                                                             |
|-------|-------------|-----------------------------------|------------------------------------------------------------------|
| 0     | PUSH X      | Replace "X" with an integer value | Pushes "X" onto the top of the stack                             |
| 1     | POP         |                                   | Removes the value from the top of the stack                      |
| 2     | ADD         |                                   | Adds top two values of the stack together, adds new value on top |
| 3     | SUB         |                                   | Adds top two values of the stack together,                       |
| 4     | PRINT       |                                   | Adds new value on top                                            |
| 5     | EXIT        |                                   | Exits the program                                                |


So far it runs test.hop, and it prints 7 and 14 as expected.
