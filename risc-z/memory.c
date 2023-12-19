#include <stddef.h>
#include "memory.h"

typedef struct {
    rz_address_t base;
    size_t size;
    uint8_t *data;
} memory_region_t;

static uint8_t text_memory[TEXT_SIZE];
static uint8_t data_memory[DATA_SIZE];
static uint8_t stack_memory[STACK_SIZE];

memory_region_t regions[] = {
    { TEXT_OFFSET,  TEXT_SIZE, text_memory },
    { DATA_OFFSET,  DATA_SIZE, data_memory },
    { STACK_OFFSET, STACK_SIZE, stack_memory },
};

void *mem_access(rz_address_t addr) {
    static uint8_t nowhere;
    for(int i = 0; i < 3; ++i) {
        if(regions[i].base <= addr && addr < regions[i].base + regions[i].size)
            return regions[i].data + addr - regions[i].base;
    }
    nowhere = 0;
    return &nowhere;
}
