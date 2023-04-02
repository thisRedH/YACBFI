// Made by RedH
// 2023 April

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ERR(msg)                fprintf(stderr, msg); return 1;
#define ERR_ALLOC(ptr)          if (ptr == NULL) { fprintf(stderr, "Error allocating memory\n"); return 1; }
#define ERR_FOPEN(fptr, fn)     if (fptr == NULL) { fprintf(stderr, "Could not open the file \"%s\"\n", fn); return 1; }

#define COMMAND_HAS_ARG         1
#define COMMAND_NO_ARG          0

typedef struct {
    const char* name;
    char alias;
    int has_arg;
    const char* help;
    char intern_alias;
} Command;


/**
 * @param _cmds A list of all possible args. The last has to be NULL (ptr) and 0 (char) termiantet
 * @param _filename Return value
 * @return 0 = Success, 1 = Err, 2 = End programm no Err
 */
int handleArgs(int _argc, char const *_argv[], Command _cmds[], const char** _filename);

/**
 * \brief Gets the cli args in a while loop like getopts()
 * 
 * \param _cmds A list of all possible args. The last has to be NULL (ptr) and 0 (char) termiantet
 * \param _index To keep track where we are. Needs to be incemented when u decide to 
 * \return Returns the current intern_alias for use in switch
 */
int getargs(int _argc, char const *_argv[], Command _cmds[], int* _index);

/**
 * \brief Prints the help message
 */
void printhelp(Command _cmds[]);

#endif