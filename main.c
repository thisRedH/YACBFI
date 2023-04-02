// Made by RedH
// 2023 April

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/**
 * \brief Loads a Brainfuck file and puts it into _prog
 * 
 * \param _file The file to open
 * \param _prog Return value for the Brainfuck code string
 * \param _len Return value for length of the Brainfuck code string
 * \return Error 1, Success 0
 */
int loadProgr(const char* _file, char** _prog, size_t* _len);

Command cmds[] = {
    // Informatical args like help or version come before all other to quit the program before making anything else
    {"yacbfi",  0,      COMMAND_NO_ARG,  "[options]",                       0},
    {"help",    'h',    COMMAND_NO_ARG,  "Shows this message",              'h'},
    {"version", 'v',    COMMAND_NO_ARG,  "Show the current version number", 'v'},
    {"file",    'f',    COMMAND_HAS_ARG, "Brainf*ck File to use",           'f'},
    {NULL, 0, 0, NULL, 0}
};

#define ALLOC_MEM               (size_t)512
#define REALLOC_MEM             (size_t)1024

int main(int argc, char const *argv[]) {
    const char* filename;
    char* program;
    size_t program_len;

    size_t memory_size = ALLOC_MEM;
    unsigned char* memory = (char*)calloc(sizeof(unsigned char), memory_size); ERR_ALLOC(memory)
    size_t mem_ptr = 0;
    unsigned char current_instr;

    int err = handleArgs(argc, argv, cmds, &filename);

    if (err == 1) { ERR("Failed to Initialize!\n") }
    if (err == 2) { return 0; }
    else if (filename == NULL) {
        printf("Input your programm (max. 1000 chars): ");
        program = (char*) malloc(sizeof(char) * 1024); ERR_ALLOC(program)
        fgets(program, 1024, stdin);
        program_len = strlen(program);
    } else {
        loadProgr(filename, &program, &program_len);
    }


    for (int i = 0; i < program_len; i++) {
        // Dynamicly realloc if the Memory gets too small
        if (mem_ptr >= memory_size) {
            memory_size += REALLOC_MEM;
            unsigned char* new_memory = (unsigned char*)calloc(sizeof(unsigned char), memory_size); ERR_ALLOC(new_memory)
            memcpy(new_memory, memory, mem_ptr);
            free(memory);
            memory = new_memory;
        }

        current_instr = program[i];
        switch(current_instr) {
            case '+':
                memory[mem_ptr] += 1;
                break;
            case '-':
                memory[mem_ptr] -= 1;
                break;
            case '>':
                mem_ptr++;
                break;
            case '<':
                mem_ptr--;
                break;
            case '.':
                putchar(memory[mem_ptr]);
                break;
            case ',':
                memory[mem_ptr] = getchar();
                break;
            case '[':
                if (memory[mem_ptr] == 0) {
                    // Find the matching ']'
                    int level = 1;
                    while (level > 0) {
                        i++;
                        if (program[i] == '[') {
                            level++;
                        } else if (program[i] == ']') {
                            level--;
                        }
                    }
                }
                break;
            case ']':
                if (memory[mem_ptr] != 0) {
                    // Find the matching '['
                    int level = 1;
                    while (level > 0) {
                        i--;
                        if (program[i] == '[') {
                            level--;
                        } else if (program[i] == ']') {
                            level++;
                        }
                    }
                }
                break;
            default:
                break;
        }
    }
    free(program);
    free(memory);

    return 0;
}

int loadProgr(const char* _file_name, char** _prog, size_t* _len) {
    FILE* _fp = fopen(_file_name, "rb");
    ERR_FOPEN(_fp, _file_name)

    fseek(_fp, 0, SEEK_END);
    long _flen = ftell(_fp);
    rewind(_fp);
    *_len = _flen + 1;

    *_prog = (char*) malloc(sizeof(char) * (_flen + 1)); ERR_ALLOC(*_prog)

    fread(*_prog, sizeof(char), _flen, _fp);
    (*_prog)[_flen] = '\0';

    fclose(_fp);
    return 0;
}