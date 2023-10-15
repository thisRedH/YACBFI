
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include <errno.h>
#include <assert.h>

#include "vmem.h"

void* __recalloc(void* ptr, size_t old_count, size_t count, size_t size) {
    void* new;

    if (!ptr) {
        new = calloc(count, size);
        if (!new) return NULL;
    } else {
        if (old_count < count) {
            new = calloc(count, size);
            if (!new) return NULL;

            memcpy(new, ptr, old_count * size);

            free(ptr);
        } else {
            new = ptr;
        }
    }
    return new;
}

vmem* vmem_init(vmem_type type, size_t length) {
    vmem* mem = malloc(sizeof(*mem));
    mem->length = length;
    mem->type = type;
    mem->_bits = NULL;

    if (length > 0) {
        mem->_bits = calloc(length, type);
        if (mem->_bits == NULL) errno = VMEM_EALLOC;
    }

    return mem;
}

void vmem_cleanup(vmem* mem) {
    free(mem->_bits);
    free(mem);
}

size_t vmem_get(const vmem* const mem, size_t pos) {
    if (pos >= mem->length) {
        errno = VMEM_ERNG;
        return 0;
    }

    switch (mem->type) {
    case VMEM_BIT8:
        return mem->bit8[pos];
        break;
    case VMEM_BIT16:
        return mem->bit16[pos];
        break;
    case VMEM_BIT32:
        return mem->bit32[pos];
        break;
    case VMEM_BIT64:
        return mem->bit64[pos];
        break;
    default:
        errno = VMEM_ENOTTYPE;
        return 0;
        break;
    }
}

void vmem_set(vmem* const mem, size_t pos, size_t value) {
    if (pos >= mem->length) {
        errno = VMEM_ERNG;
        return;
    }

    switch (mem->type) {
    case VMEM_BIT8:
        mem->bit8[pos] = value;
        break;
    case VMEM_BIT16:
        mem->bit16[pos] = value;
        break;
    case VMEM_BIT32:
        mem->bit32[pos] = value;
        break;
    case VMEM_BIT64:
        mem->bit64[pos] = value;
        break;
    default:
        errno = VMEM_ENOTTYPE;
        break;
    }
    return;
}

void vmem_resize(vmem* mem, size_t new_length) {
    mem->_bits = __recalloc(mem->_bits, mem->length, new_length, mem->type);
    mem->length = new_length;
}
