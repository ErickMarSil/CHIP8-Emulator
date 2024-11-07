#ifdef CPU_H
#define CPU_H

public:
    typedef int cycle;

public:
    struct Memory{
        void clear_memory();
        void init_memory();
        void add_stack(uint8& addr, uint32& data, cycle& Cycles);
    }

#endif