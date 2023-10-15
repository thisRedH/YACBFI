
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
    VMEM_BIT8 =   1,
    VMEM_BIT16 =  2,
    VMEM_BIT32 =  4,
    VMEM_BIT64 =  8,
} vmem_type;

typedef struct _vmem {
    size_t length;
    vmem_type type : 4;
    union {
        size_t* _bits;
        uint8_t* bit8;
        uint16_t* bit16;
        uint32_t* bit32;
        uint64_t* bit64;
    };
} vmem;

vmem* vmem_init(vmem_type type, size_t length);
void vmem_cleanup(vmem* mem);

size_t vmem_get(const vmem* const mem, size_t pos);
void vmem_set(vmem* const mem, size_t pos, size_t value);

void vmem_resize(vmem* mem, size_t new_length);