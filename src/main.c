// Made by RedH
// 2023 April

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include "utils.h"

/**
 * \brief Loads a Brainf*ck file and puts it into _prog
 * 
 * \param _file The file to open
 * \param _prog Return value for the Brainf*ck code string
 * \param _len Return value for length of the Brainf*ck code string
 * \return 0 = Success, 1 = Err
 */
int loadProgr(const char* _file, char** _prog, size_t* _len);

Command cmds[] = {
    {"yacbfi",      0,      COMMAND_NO_ARG,  "[options]",                       0},
    {"help",        'h',    COMMAND_NO_ARG,  "Shows this message",              'h'},
    {"version",     'v',    COMMAND_NO_ARG,  "Show the current version number", 'v'},
    {"file",        'f',    COMMAND_HAS_ARG, "Brainf*ck File to use",           'f'},
    {"cell_size",   's',    COMMAND_HAS_ARG, "The Bit amount to use per Cell (Standart: 8Bit)",   's'},
    {NULL, 0, 0, NULL, 0}
};

#define ALLOC_MEM               (size_t)512
#define REALLOC_MEM             (size_t)1024

int main(int argc, char const *argv[]) {
    const char* filename;
    char* program;
    size_t program_len = 0;

    size_t cell_size = 1;

    int err = handleArgs(argc, argv, cmds, &filename, &cell_size);
    if (err == 1) { ERR("Failed to Initialize!"); return 1; }
    if (err == 2) { return 0; }
    else if (filename == NULL) {
        printf("Input your programm (max. 1000 chars): ");
        program = (char*) malloc(sizeof(char) * 1024);
        if (program == NULL) { ERR_ALLOC(); }

        fgets(program, 1024, stdin);
        program_len = strlen(program);
    } else {
        loadProgr(filename, &program, &program_len);
    }

    size_t memory_length = ALLOC_MEM;
    uint8_t* memory = (uint8_t*) calloc(ALLOC_MEM, sizeof(uint8_t));
    if (memory == NULL) { ERR_ALLOC(); }

    size_t mem_ptr = 0;


    for (int i = 0; i < program_len; i++) {
        // Dynamicly alloc if the Memory gets too small
        if (mem_ptr >= memory_length) {
            int reerr = recallocMem((void**)&memory, memory_length,
                        sizeof(uint8_t), (memory_length + REALLOC_MEM));
            if (reerr != 0) { ERR_ALLOC(); }

            memory_length += REALLOC_MEM;
        }

        // Process the current instruction
        switch(program[i]) {
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
    if (_fp == NULL) { ERR_FOPEN(_file_name); return 1; }

    fseek(_fp, 0, SEEK_END);
    long _flen = ftell(_fp);
    rewind(_fp);
    *_len = _flen + 1;

    *_prog = (char*) malloc(sizeof(char) * (_flen + 1));
    if (*_prog == NULL) { ERR_ALLOC(); return 1; }

    fread(*_prog, sizeof(char), _flen, _fp);
    // Set null Terminator
    (*_prog)[_flen] = '\0';

    fclose(_fp);
    return 0;
}