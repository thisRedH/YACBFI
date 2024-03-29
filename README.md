# YACBFI - Yet another C Brainf*ck Interpreter

YACBFI is yet another [Brainf*ck](https://www.wikipedia.org/wiki/Brainfuck) interpreter written in [C99](https://www.wikipedia.org/wiki/C99).\
I made this not because there are so few out there... rather because I wanted to learn C coming from a C++ background.\
It was harder than I could imagine. I relie so heavily upon C++11 Features and OOP that it was a real challenge.

## Requirements
 - A compiler that is capable of C99 (GCC Testet)
### Additionally
 - GNU Make

## Compilation
### With Make:
Just type `make`. Otherwise, use `make CC={compiler name}` to change the compiler.
### With GCC:
```bash
$ gcc -std=c99 -O3 -o yacbfi.exe src/main.c src/utils.c
```

## Usage
There is a `Hello World!` sample (sample/hello.bf)\
To test it, I highly recommend checking out Daniel B. Cristofani's [Brainf*ck Programs](http://brainfuck.org)\
<sup>Espessialy [test.b](http://brainfuck.org/tests.b) for "Feature" testing</sup>
```bash
$ yacbfi -f {file.bf}
```

## Features
- Full Brainf*ck Support
- Dynamic Memory Allocation

## Todo's
 - [ ] Option to have different size of cells ([Test](https://esolangs.org/wiki/Brainfuck#Cell_Size))
 - [ ] Settable Size to enable wrapping (Dynamic Memory turns Off)
 - [ ] `+++++[>+++++++>++<<-]>.>.[` Should give error message "unmatched \]"
 - [ ] `+++++[>+++++++>++<<-]>.>.][` Should give error message "unmatched \["

## License
This software is licensed under the [MIT License](https://choosealicense.com/licenses/mit/).
