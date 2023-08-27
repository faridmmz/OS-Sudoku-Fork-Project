# Sudoku Compatibility Checker

This is a simple C program that checks the compatibility of Sudoku answers of letters.

## Project Description

In this project, we create a parent process that spawns four sub-processes using the `fork` command. One process is responsible for encrypting the input file and converting it to the corresponding Sudoku board. The other three processes check the compatibility of rows, columns, and sub-rectangles of the Sudoku board. The parent process communicates with each of the sub-processes using named pipes.

The input file format consists of:
1. Dimensions of the main Sudoku board.
2. Length and width of each sub-rectangle.
3. Encrypted Sudoku answers.

The encryption method involves replacing each letter with the letter that comes two places after it in the alphabet, wrapping around from 'Z' to 'A'.

After obtaining the Sudoku answer, the parent process distributes it to each of the three sub-processes to check compatibility. If all checks pass, "Satisfied constraints Puzzle Sudoku" is printed; otherwise, "Sudoku Puzzle is Wrong" is printed.

## Getting Started

1. Compile the program using a C compiler (e.g., `gcc -o sudoku_checker main.c`).
2. Create input files with appropriate test cases (e.g., `testcase.txt`, `testcase2.txt`).

## Usage

Run the compiled program and provide the input file as an argument:

```sh
./sudoku_checker testcase.txt
```
## Input File Format

The input file should have the following format:
```
<Main Board Dimension> * <Sub-rectangle Length> * <Sub-rectangle Width>
<Encrypted Sudoku Answers>
```

## Example Test Cases
### Test Case 1

Input (testcase.txt):
```
9 * 3 * 3
I JDK Cef GH#
c FGJ I h   K d e#hkefgdicj#
DIKGECJHF#GhfDk
jcEI#
ecjihfgkD#fgcHDIEJK#kdiejgHFc#JehcFKdlg
```

Output:
```
cul problem = 0 row problem = 0 rec problem = 0
Sudoku Puzzle constraints satisfied
```

### Test Case 2

Input (testcase2.txt):
```
4* 2 * 2
CdE F#F ed c #
Df ce# ECfF#
```

Output:
```
cul problem = 1 row problem = 1 rec problem = 0
Sudoku Puzzle is Wrong
```