# 📜 get\_next\_line

Custom implementation of a function that reads one line at a time from a file descriptor. Handles variable buffer sizes, maintains state across calls, and supports multiple file descriptors in the bonus version.

## Build and run

```bash
# Clone
 git clone https://github.com/cmunoz-g/get_next_line.git
 cd get_next_line
```

Include in your project by adding:

* `get_next_line.c`
* `get_next_line_utils.c`
* `get_next_line.h`

Compile with a specified buffer size:

```bash
gcc -Wall -Werror -Wextra -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o my_program
```

Replace `42` with the buffer size you want.

Run your program:

```bash
./my_program
```

## Features

* **Line-by-line reading** — returns each line including `\n` if present.
* **Static state** — keeps track of leftovers across multiple calls.
* **Configurable buffer size** — controlled at compile time with `BUFFER_SIZE`.
* **Memory safety** — manages dynamic memory to prevent leaks.

## Project structure

* **get\_next\_line.c** — main line-reading logic.
* **get\_next\_line\_utils.c** — helper functions.
* **get\_next\_line.h** — prototypes and includes.

## Bonus

* **Multiple file descriptors** — supports parallel reads from multiple descriptors, storing state separately.


