#include "keyboard.h"
#include <stddef.h>
#include <stdbool.h>
#include "../isr.h"
#include "../ports.h"

#define BUFFER_SIZE 256
static char buffer[BUFFER_SIZE];
static uint8_t head = 0;
static uint8_t tail = 0;

static const char scancode_to_ascii[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0,
    // Extended keys ignored...
};

void keyboard_callback() {
    uint8_t scancode = inb(0x60);
    if (scancode & 0x80) return; // ignore key release

    char ch = scancode_to_ascii[scancode];
    if (ch && ((head + 1) % BUFFER_SIZE != tail)) {
        buffer[head] = ch;
        head = (head + 1) % BUFFER_SIZE;
    }
}

void keyboard_init() {
    register_interrupt_handler(33, keyboard_callback); // IRQ1
    outb(0x21, inb(0x21) & ~0x02); // Enable IRQ1 (keyboard)
}

int keyboard_available() {
    return head != tail;
}

char keyboard_get_char() {
    while (head == tail) __asm__ volatile("hlt");
    char ch = buffer[tail];
    tail = (tail + 1) % BUFFER_SIZE;
    return ch;
}