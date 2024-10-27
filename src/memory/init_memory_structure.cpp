#include <iostream>
#include <string>

using namespace std;

using Byte = unsigned int;

struct Memory{
    static constexpr int max_mem = 4096;
    static constexpr int buffer_mem = 512;
    static constexpr int display_mem = 256;
    static constexpr int callstack_mem = 96;

    Byte memory_slots[max_mem];
    Byte buffer_cpu_slots[buffer_mem];
    Byte buffer_display_slots[display_mem];
    Byte buffer_callstack_slots[callstack_mem];
};