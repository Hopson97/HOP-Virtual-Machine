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
| 5     | JUMP        | Requires a label to jump to       | Jumps to a "label" in the program                                |
| 6     | JIE         | Requires a label to jump to       | Jumps to a "label" in the program, if the top of stack is equal to next num                               |
| 7     | JIN         | Requires a label to jump to       | Jumps to a "label" in the program , if the top of stack is not equal to next num                               |
| 8     | JIL         | Requires a label to jump to       | Jumps to a "label" in the program, if the top of stack is less than  next num                               |
| 9     | JIG         | Requires a label to jump to       | Jumps to a "label" in the program, if the top of stack is greater than next num                               |
| 10    | EXIT        |                                   | Exits the program                                                |


As seen in the instruction list, you can also add labels. Every .hop needs a "main:" label as this marks the entry point of the program.

You can add labels wherever. However, you can only "JUMP" to the ones defined earlier in the program so far.

eg:

_____________
```
SomeSection:
  PUSH 8
  PRINT
  EXIT
  
SomeLabel:
  PUSH 7
  PUSH 3
  ADD
  PRINT
  JIE 10 someSection
  
main:
  PUSH 5
  PUSH 3
  SUB
  JIL 3 SomeLabel
  PRINT
  JUMP SomeLabel
  ```
  _________________
  
Prints out:

  2

  
  
  
