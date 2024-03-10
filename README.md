# RISC-V Assembler
A simple RISC-V assembler that reads assembly code, parses it, and generates machine code instructions.

## Table of Contents

- [About](#about)
- [Features](#features)
- [Usage](#usage)
- [Limitations](#limitations)

## About

This project implements a basic RISC-V assembler in C++. It consists of a two-pass process: the first pass processes the `.data` section, storing variables and data in memory, while the second pass processes the `.text` section, generating machine code instructions.

## Features
The assembler supports the following commands:
### R Format
- add
- and
- or
- sll
- slt
- sra
- srl
- sub
- xor
- mul
- div
- rem

### I Format
- addi
- andi
- ori
- lb
- ld
- lh
- lw
- jalr

### S Format
- sb
- sw
- sd
- sh

### SB Format
- beq
- bne
- bge
- blt

### U Format
- auipc
- lui

### UJ Format
- jal

 and the following assembler directives:
- .text
- .data
- .byte
- .half
- .word
- .dword
- .asciz

## Usage
1. Ensure all the files are in the same folder and compile main.cpp.

   ```bash
   g++ main.cpp

2. Execute the executable file and ensure there is a file "input.asm" to provide input.
   For Windows:
   ```bash
   ./a.exe
   ```
   For Linux:
   ```bash
   ./a.out
   ```
The output will be generated in a file "output.mc" which will contain the machine code of instructions along with the program counter and the data segment of the code
   
## Limitations
For proper working of the assembler, the given rules need to be followed
- Each line can contain only one instruction
- There should not be any space between the label name and the ':' during declaration
- Comments can be placed anywhere in the code except along with labels
- Label declaration should not be followed by an instruction
