#include <stdint.h>

void sendInterrupt(int interruptNumber) {
    asm volatile (
        "int %0"
        :
        : "i"(interruptNumber)
    );
}

void allocateMemory(uint32_t size) {
    asm volatile (
        "mov %0, %%eax\n"
        "int $0x80"
        :
        : "r"(size)
        : "%eax"
    );
}

void deloacteMemory(uint32_t address) {
    asm volatile (
        "mov %0, %%eax\n"
        "int $0x80"
        :
        : "r"(address)
        : "%eax"
    );
}

void setCursorPosition(uint16_t x, uint16_t y) {
    asm volatile (
        "mov %0, %%dx\n"
        "mov %1, %%cx\n"
        "int $0x10"
        :
        : "r"(x), "r"(y)
        : "%dx", "%cx"
    );
}

void getCursorPosition(uint16_t* x, uint16_t* y) {
    asm volatile (
        "int $0x10"
        : "=a"(*x), "=b"(*y)
        :
        : "%dx", "%cx"
    );
}

void setVideoMode(uint8_t mode) {
    asm volatile (
        "mov %0, %%al\n"
        "int $0x10"
        :
        : "r"(mode)
        : "%eax"
    );
}

void getVideoMode(uint8_t* mode) {
    asm volatile (
        "int $0x10"
        : "=a"(*mode)
        :
        : "%eax"
    );
}

