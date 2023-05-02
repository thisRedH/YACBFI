// Made by RedH
// 2023 April

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ERR(msg)                fprintf(stderr, "\n\n%s\n\n", msg)
#define ERR_ALLOC()             fprintf(stderr, "\n\nError reallocating new Memory: %s\n\n", strerror(errno))
#define ERR_FOPEN(fn)           fprintf(stderr, "\n\nCould not open the file \"%s\": %s\n\n", fn, strerror(errno))

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
 * \brief Prints the help message
 */
void printhelp(Command _cmds[]);

/**
 * \brief Gets the cli args in a while loop like getopts()
 * 
 * \param _cmds A list of all possible args. The last has to be NULL (ptr) and 0 (char) termiantet
 * \param _index To keep track where we are. Needs to be incemented when u decide to 
 * \return Returns the current intern_alias for use in switch
 */
int getargs(int _argc, char const *_argv[], Command _cmds[], int* _index);

/**
 * \param _cmds A list of all possible args. First has to be Program Name. The last has to be NULL (ptr) and 0 (char) termiantet
 * \param _filename Return value
 * \return 0 = Success, 1 = Err, 2 = End programm no Err
 */
int handleArgs(int _argc, char const *_argv[], Command _cmds[], const char** _filename);

/**
 * \brief Reallocate a block of memory to make it bigger (smaller not supportet). New space Iitialiced to 0 (using calloc)
 * 
 * \param _mem Memory that needs to be reallocatet
 * \param _oldNitems The length of the old "array"
 * \param _size Size of the type that u allocate (sizeof())
 * \param _newNitems The length of the new "array"
 * \return 0 = Success, 1 = Err
 */
int recallocMem(void** _mem, size_t _oldNitems, size_t _size, size_t _newNitems);

#endif