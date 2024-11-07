#ifndef MEMORY_H
#define MEMORY_H

constexpr uint64 MAX_MEMORY = 4096;

struct Memory {
    uint8 Memory_Slots[MAX_MEMORY];
    void clear_memory();
    void init_memory();
    void add_stack(uint16& SP, uint32& data, cycle& Cycles);
};

#endif