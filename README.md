# get_next_line

A line-by-line file reading function, based on the 42 School get_next_line project.

## Context

I'm not a 42 School student, but I follow parts of their curriculum on my own time as a personal learning path to deepen my understanding of the C programming language.

## What is get_next_line?

`get_next_line` is a project from the 42 cursus. The goal is to implement a function that reads a file descriptor line by line — returning one line per call, including the newline character, until the end of the file. No buffered I/O helpers like `getline`, no shortcuts. You have to manage the reading, buffering, and state yourself.

## What I learned

- How `read()` works at a low level and why buffering matters
- Managing persistent state across multiple function calls using `static` variables
- Handling edge cases: missing newline at EOF, empty files, multiple file descriptors
- Careful memory management to avoid leaks across successive calls

## Project structure

```
get_next_line/
├── get_next_line.c
├── get_next_line_utils.c
└── get_next_line.h
```

## How it works

Each call to `get_next_line(fd)` returns the next line from the given file descriptor. A `static` buffer retains whatever was read past the last newline, so it's available on the next call. The function keeps reading in chunks of `BUFFER_SIZE` bytes until a newline or EOF is found.

```c
char *get_next_line(int fd);
```

| Return value | Condition |
|---|---|
| A line (with `\n`) | A line was successfully read |
| A line (without `\n`) | Last line before EOF |
| `NULL` | EOF reached or an error occurred |

## Bonus — multiple file descriptors

The bonus version handles several file descriptors simultaneously without losing track of each one's reading state — using an array of static buffers indexed by `fd`.

```
get_next_line/
├── get_next_line_bonus.c
├── get_next_line_utils_bonus.c
└── get_next_line_bonus.h
```

## Build & usage

Compile it alongside your project, and set `BUFFER_SIZE` at compile time:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

You can tune `BUFFER_SIZE` to any value — the function must behave correctly regardless.

## Tests
The project has been tested using this repo:

https://github.com/Tripouille/gnlTester

## Notes

This project is done purely for learning purposes, following the 42 cursus as a self-study resource. I am not affiliated with 42 School.

