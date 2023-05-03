// Made by RedH
// 2023 April

#include "utils.h"

#ifndef YACBFI_VERSION
#define YACBFI_VERSION  "1.0.5"
#endif

void printhelp(Command _cmds[]) {
    // Print the Usage (Usage: Name [help])
    printf("\nUsage: %s %s\n", _cmds[0].name, _cmds[0].help);

    // Print all helps (   -a, --name {spaces} help)
    for (int i = 1; _cmds[i].name != NULL; i++) {
        if (_cmds[i].alias == 0) {
            printf("       --%s", _cmds[i].name);
        } else {
            printf("   -%c, --%s", _cmds[i].alias, _cmds[i].name);
        }

        int spaces_needed = 20 - strlen(_cmds[i].name);
        for (int i = 0; i < spaces_needed; i++) {
            printf(" ");
        }

        printf("%s\n", _cmds[i].help);
    }
}


int getargs(int _argc, char const *_argv[], Command _cmds[], int* _index) {
    // Check if it reached the end of the argument list
    if (*_index >= _argc) { return -1; }

    // Check if argument is "long"
    if (_argv[*_index][0] == '-' && _argv[*_index][1] == '-') {
        const char* _optname = _argv[*_index] + 2;

        for (int i = 0; _cmds[i].name != NULL; i++) {
            // if optname has been found
            if (strcmp(_optname, _cmds[i].name) == 0) {
                (*_index)++;
                return _cmds[i].intern_alias;
            }
        }
        fprintf(stderr, "Unknown option: '%s'\n", _optname);
        return '?';
    }

    if (_argv[*_index][0] == '-') {
        char _optname = _argv[*_index][1];

        for (int i = 0; _cmds[i].name != NULL; i++) {
            // if optname has been found
            if (_cmds[i].alias == _optname) {
                (*_index)++;
                return _cmds[i].intern_alias;
            }
        }
        fprintf(stderr, "Unknown option: '%c'\n", _optname);
        return '?';
    }
    return '?';
}

int handleArgs(int _argc, char const *_argv[], Command _cmds[], const char** _filename, size_t* _cell_size) {
    *_filename = NULL;
    
    if (_argc <= 1) { return 0; }

    int _opt;
    int _index = 1;
    while ((_opt = getargs(_argc, _argv, _cmds, &_index)) != -1) {
        switch (_opt) {
        case 'h':
            printhelp(_cmds);
            return 2;
            break;
        case 'f':
            *_filename = _argv[_index];
            _index++;
            break;
        case 'v':
            printf("\nYACBFI - Made by RedH - %s\n\n", YACBFI_VERSION);
            printf("This software is published under the MIT license.\nSee the LICENSE file for more information.\n");
            return 2;
            break;
        case 's':
            int inp_size = atoi(_argv[_index]);
            *_cell_size = (size_t)(inp_size / 8);
            if (inp_size != 8 && inp_size != 16 && inp_size != 32 && inp_size != 64) {
                ERRPP("%d is not a valid bit size to use!\nPlease use 8, 16, 32 or 64", (int)inp_size);
                return 1;
            }
            _index++;
            break;
        case '?':
            return 1;
            break;
        default:
            break;
        }
    }
    return 0;
}

int recallocMem(void** _mem, size_t _oldNitems, size_t _size, size_t _newNitems) {
    if (_newNitems <= _oldNitems) {
        return 0;
    }

    void* _new_memory = calloc(_newNitems, _size);
    if (_new_memory == NULL) {
        return 1;
    }

    memcpy(_new_memory, *_mem, _oldNitems);
    free(*_mem);
    *_mem = _new_memory;

    return 0;
}