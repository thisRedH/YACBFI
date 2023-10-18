
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include <errno.h>
#include <assert.h>

#include "vmem.h"
#define BI_TO_BY(b)     (size_t)((size_t)(b) / 8)
#define BY_TO_BI(b)     (size_t)((size_t)(b) * 8)

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

uint8_t _setbits(size_t* dest, size_t src, uint8_t pos, size_t num_bits) {
    if (num_bits >= BY_TO_BI(sizeof(*dest))) {
        *dest = src;
        return 0;
    }

    size_t mask = ((1ULL << num_bits) -1);
    uint8_t sdest = BY_TO_BI(sizeof(*dest));
    pos %= sdest;

    if (num_bits > sdest || pos + num_bits > sdest) {
        return 1;
    }
    if (!num_bits) return 0;

    // Clear bits in destination at the specified position
    *dest &= ~(mask << pos);
    // Set bits in destination to bits from source
    *dest |= (src & mask) << pos;

    return 0;
}

size_t _getbits(size_t src, uint8_t pos, size_t num_bits) {
    if (num_bits >= BY_TO_BI(sizeof(src)))
        return src;

    size_t mask = ((1ULL << num_bits) -1);
    uint8_t sdest = BY_TO_BI(sizeof(src));
    pos %= sdest;

    return (src >> pos) & mask;
}

uint8_t vblock_setbits(vblock* dest, size_t src, uint8_t pos, size_t num_bits) {
    pos %= BY_TO_BI(sizeof(*dest)) / num_bits;
    pos *= 8;
    return _setbits(dest, src, pos, num_bits);
}

size_t vblock_getbits(vblock src, uint8_t pos, size_t num_bits) {
    pos %= BY_TO_BI(sizeof(src)) / num_bits;
    pos *= 8;
    return _getbits(src, pos, num_bits);
}

vmem* vmem_init(vmem_type type, size_t length) {
    vmem* mem = (vmem*)malloc(sizeof(vmem));
    mem->length = length;
    mem->type = type;
    mem->block_cap = (size_t)(BY_TO_BI(sizeof(*mem->blocks)) / mem->type);
    mem->blocks = NULL;

    if (length > 0) {
        // Set length to pack all values into vblock + buffer because int "floor"
        length = (size_t)(length / mem->block_cap) +1;
        mem->blocks = calloc(length, sizeof(*mem->blocks));
        if (mem->blocks == NULL) errno = VMEM_EALLOC;
    }

    return mem;
}

void vmem_cleanup(vmem* mem) {
    free(mem->blocks);
    free(mem);
}

void vmem_set(vmem* mem, size_t pos, size_t value) {
    if (pos >= mem->length) {
        errno = VMEM_ERNG;
        return;
    }

    size_t bpos = pos / mem->block_cap;
    uint8_t spos = pos % mem->block_cap;

    vblock_setbits(&mem->blocks[bpos], value, spos, mem->type);
}

size_t vmem_get(const vmem* const mem, size_t pos) {
    if (pos >= mem->length) {
        errno = VMEM_ERNG;
        return 0;
    }

    size_t bpos = pos / mem->block_cap;
    uint8_t spos = pos % mem->block_cap;

    return vblock_getbits(mem->blocks[bpos], spos, mem->type);
}

void vmem_increment(vmem* const mem, size_t pos) {
    vmem_set(mem, pos, vmem_get(mem, pos) +1);
}

void vmem_decrement(vmem* const mem, size_t pos) {
    vmem_set(mem, pos, vmem_get(mem, pos) -1);
}
