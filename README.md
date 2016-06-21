# HOP-Virtual-Machine

It is a simple "CPU"/ fake assembly langauge.

So far the instructions for it :

| Value | Instruction | Notes                             | DOES                                                             |
|-------|-------------|-----------------------------------|------------------------------------------------------------------|
| 0     | PUSH X      | Replace "X" with an integer value | Pushes "X" onto the top of the stack                             |
| 1     | POP         |                                   | Removes the value from the top of the stack                      |
| 2     | ADD         |                                   | Adds top two values of the stack together, adds new value on top |
| 3     | SUB         |                                   | Adds top two values of the stack together,                       |
| 4     | PRINT       |                                   | Adds new value on top                                            |
| 5     | JUMP        |                                   | Jumps to a "label" in the program                                 |
| 6     | EXIT        |                                   | Exits the program                                                |


As seen in the instruction list, you can also add labels. Every .hop needs a "main:" label as this marks the entry point of the program.

You can add labels wherever. However, you can only "JUMP" to the ones defined earlier in the program so far.

eg:

_____________

SomeLabel:
  PUSH 7
  PUSH 3
  ADD
  PRINT
  
main:
  PUSH 5
  PUSH 3
  SUB
  PRINT
  JUMP SomeLabel
  
  _________________
  
Prints out:
  2
  10
  
  
  
