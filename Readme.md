# LC3 Simulator

Welcome to the **LC3 Simulator** *Qt based* project! This simulator emulates the LC3 (Little Computer 3) architecture, providing a platform for running LC3 assembly programs. It is a great tool for students and professionals looking to understand computer architecture and low-level programming.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [How to use](#usage)
- [Examples](#example)
- [Notes](#notes)

## Introduction

The LC3 Simulator is a software tool that mimics the functionality of the LC3 computer. The LC3 is a simple educational computer used for teaching and learning the basics of computer architecture and assembly language programming. This simulator allows you to write, debug, and run LC3 assembly programs on your computer.

## Features

- **Complete LC3 Instruction Set**: Supports all LC3 instructions, including arithmetic, logical, control, and memory operations.
- **User-Friendly Interface**: Easy-to-use graphical interface for writing and running LC3 programs.
- **Debugging Tools**: Step through programs, set breakpoints, and inspect registers and memory.
- **Program Loader**: Load and run LC3 programs from text files.(coming soon)

## Installation

You can install the app either by using the installer included in the project or by getting the source code and running it via **Qt**.

**Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/lc3-simulator.git
   cd lc3-simulator
   ```

## Usage
To use this simulator, first compile the code you have written, and then:
1. You can run the whole program using the "Run" button.
2. You can use the "Next" button to run each instruction step by step, showing what the LC3 does during each clock pulse (in the box above the editor)

## Example
```assembley
; This symbol is used for comments ;
; A program to calculate addition of numbers from 1 to N
ORG 3000
; Initialize variables
LD R0, INIT ; Load R0 with the initial value (1)
LD R2, N ; Load R2 with loop size
AND R1, R1, #0 ; Clear R1 (accumulator for sum)
; Loop to add numbers from 1 to 100
LOOP, ADD R1, R1, R0 ; Add current number (R0) to sum (R1)
ADD R0, R0, #1 ; Increment current number
ADD R2, R2, #1 ; Increment loop counter
BRn LOOP ; If counter negative (not reached 0), repeat loop
; Store the result (sum of numbers 1 to 100) in memory
ST R1, RESULT ; Store the sum in memory location 'RESULT'
; Halt the program
  HALT
; Initialize variables
INIT, DEC 1 ; Initial value for the loop (starting from 1)
RESULT, DEC 0 ; Memory location to store the result
N, DEC -100 ; Loop size initializer 
   END
```

## Notes
1. Please use the ORG pseudo-command with an exact HEX value, like: ORG [Hex value] (e.g., ORG 3000).
2. The PC initially equals 0x3000.
3. I/O mapping:
        KBDR: 0xFE00
        KBSR: 0xFE01
        DDR: 0xFE02
        DSR: 0xFE03
4. Using the memory search, you can go to your desired address by entering it.
5. Please put a space between the arguments for commands like ADD or AND, etc.
	
