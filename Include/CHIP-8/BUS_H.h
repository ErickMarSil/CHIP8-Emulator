#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include <MEMORY_H.h>

public:
    /* Read and write from slots stack */
    uint8_t read_stack(uint16_t& addr);
    void write_stack(uint16_t& addr, uint8_t data, uint8_t& SP);

    /* Read and write from slots in framebuffer listener */
    uint8_t read_framebuffer(uint16_t addr);
    void write_framebuffer(uint16_t& addr, uint8_t data)

    

#endif