
#include <stdint.h>

/**
 * \brief vmem error's
 * Could be a return type or set in errno
 */
typedef enum _vmem_err {
    VMEM_ESUCCESS,                              // Success
    VMEM_EALLOC,                                // Generic allocation error. Use errno for more infos
    VMEM_ENOTTYPE,                              // Enum type not defined
    VMEM_ERNG,                                  // Out of Range
} vmem_err;

typedef enum _vmem_type {
    VMEM_TYPE_1 =   1,
    VMEM_TYPE_2 =   2,
    VMEM_TYPE_3 =   3,
    VMEM_TYPE_4 =   4,
    VMEM_TYPE_5 =   5,
    VMEM_TYPE_6 =   6,
    VMEM_TYPE_7 =   7,
    VMEM_TYPE_8 =   8,
    VMEM_TYPE_16 =  16,
    VMEM_TYPE_32 =  32,
    VMEM_TYPE_64 =  64,
} vmem_type;

typedef size_t vblock;

typedef struct _vmem {
    size_t length;
    vmem_type type;
    size_t block_cap;
    vblock* blocks;
} vmem;

uint8_t vblock_setbits(vblock* dest, size_t src, uint8_t pos, size_t num_bits);
size_t vblock_getbits(vblock src, uint8_t pos, size_t num_bits);

vmem* vmem_init(vmem_type type, size_t length);
void vmem_cleanup(vmem* mem);

void vmem_set(vmem* const mem, size_t pos, size_t value);
size_t vmem_get(const vmem* const mem, size_t pos);
void vmem_increment(vmem* const mem, size_t pos);
void vmem_decrement(vmem* const mem, size_t pos);

//void vmem_resize(vmem* mem, size_t new_length) {assert(1);} //TODO: Implement
