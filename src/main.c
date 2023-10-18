#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include "defines.h"
#include "vmem.h"


int main(int argc, char const *argv[]) {
    size_t pcur, mcur;                    // Program/Instruction and Memory Cursor/Pointer
    char* pinst;                          // Program Instructions
    vmem* vmem;

    //TODO: Implement an argparser

    // Initialization
    pcur, mcur = 0;
    vmem = vmem_init(VMEM_TYPE_8, MEM_INIT_SIZE);
    if (errno == VMEM_EALLOC) goto error;

    //TODO: Load instruction from file from args or from stdin
    pinst = malloc(520*sizeof(*pinst));
    scanf("%519s", pinst);
    printf("%s", pinst);

    for (pcur = 0; pcur < 500; pcur++) {
        //TODO: Dynamicly alloc if the Memory gets too small

        // Process the current instruction
        switch(pinst[pcur]) {
            case '+':
                vmem_increment(vmem, mcur);
                break;
            case '-':
                vmem_decrement(vmem, mcur);
                break;
            case '>':
                mcur++;
                break;
            case '<':
                mcur--;
                break;
            case '.':
                putchar(vmem_get(vmem, mcur));
                break;
            case ',':
                vmem_set(vmem, mcur, getchar());
                break;
            case '[':
                if (vmem_get(vmem, mcur) == 0) {
                    // Find the matching ']'
                    int level = 1;
                    while (level > 0) {
                        pcur++;
                        if (pinst[pcur] == '[') {
                            level++;
                        } else if (pinst[pcur] == ']') {
                            level--;
                        }
                    }
                }
                break;
            case ']':
                if (vmem_get(vmem, mcur) != 0) {
                    // Find the matching '['
                    int level = 1;
                    while (level > 0) {
                        pcur--;
                        if (pinst[pcur] == '[') {
                            level--;
                        } else if (pinst[pcur] == ']') {
                            level++;
                        }
                    }
                }
                break;
            default:
                break;
        }
    }

    // Process the current instruction

    // Cleanup
    vmem_cleanup(vmem);

    return 0;
error:
    puts("Error");
    return -1;
}
