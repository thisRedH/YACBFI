#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include "defines.h"
#include "vmem.h"


int main(int argc, char const *argv[]) {
    size_t pcur, mcur;                    // Program/Instruction and Memory Cursor/Pointer
    vmem* vmem;

    // Initialization
    pcur, mcur = 0;
    vmem = vmem_init(VMEM_BIT8, MEM_INIT_SIZE);
    if (errno == VMEM_EALLOC) goto error;

    // Process the current instruction

    // Cleanup
    vmem_cleanup(vmem);
    goto error;

    return 0;
error:
    puts("Error");
    return -1;
}
