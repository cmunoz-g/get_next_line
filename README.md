# 📜 get_next_line

## Introduction
**get_next_line** is a project designed to implement a function that reads a single line from a file descriptor, handling various edge cases such as different buffer sizes and multiple file descriptors simultaneously. The function `get_next_line()` returns each line of a file until the end of the file or an error occurs.

## Project Description
The goal is to write a function that reads from a file descriptor and returns the next line, including the newline character `\n` if present. This project covers important concepts such as static variables, memory management, and file I/O.

### Project Files
- **get_next_line.c**: Contains the main function logic for reading lines from the file descriptor.
- **get_next_line_utils.c**: Contains helper functions to support the main logic.
- **get_next_line.h**: Header file with function prototypes and necessary includes.

## How to Use
1. **Clone the Repository**:
    ```bash
    git clone https://github.com/cmunoz-g/get_next_line.git
    ```
2. **Navigate to the Project Directory**:
    ```bash
    cd get_next_line
    ```
3. **Include in Your Project**:
    ```bash
    To use `get_next_line()`, include the `get_next_line.c`, `get_next_line_utils.c`, and `get_next_line.h` files in your project directory. Create a `main.c` file where you call the `get_next_line()` function.
    ```
5. **Compile the Program**:
    Compile all files together, specifying the `BUFFER_SIZE` as needed:
    ```bash
    gcc -Wall -Werror -Wextra -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o my_program
    ```
    Replace `42` with the desired buffer size.
6. **Run Your Program**:
    Run the compiled program:
    ```bash
    ./my_program
    ```
    Make sure to provide the appropriate input (e.g., file descriptor) within your `main.c` to test the `get_next_line()` function.

## Implementation Details
- **Static Variables**: The function uses a static variable to maintain the state between calls, allowing it to keep track of what has been read.
- **Buffer Size**: The size of the buffer can be specified using the `BUFFER_SIZE` macro at compile time, allowing flexibility in how much data is read at once.
- **Memory Management**: Proper handling of dynamically allocated memory to ensure there are no memory leaks.

## Bonus Features
- **Multiple File Descriptors**: The bonus part of the project supports reading from multiple file descriptors simultaneously, keeping track of each one separately using a single static variable.
