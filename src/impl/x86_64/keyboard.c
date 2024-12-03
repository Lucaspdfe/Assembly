/////////////////////////////////////////////////////////////////////////////////
// \author (c) Lucas Pedro (lucaspdfe@gmail.com)
// 
// \license The MIT License (MIT)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// \brief Keyboard handler (needs to update to include IRQ handler).
//
/////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>

// Define scancode constants
#define SCANCODE_SHIFT_PRESS 0x2A
#define SCANCODE_SHIFT_RELEASE 0xAA

static inline uint8_t inb(uint16_t port) {
    uint8_t value;
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static char scancode2ASCII(uint8_t scancode);

static char readScanKey() {
    while (!(inb(0x64) & 0x01)); // Wait for data to be available
    return inb(0x60);           // Read and return the scancode
}

char _readkey() {
    char ascii = 0;
    while (!ascii) {                            // Loop until a valid ASCII character is returned
        uint8_t scancode = readScanKey();         // Get the scancode
        ascii = scancode2ASCII(scancode); // Convert it to ASCII
    }
    return ascii;
}

// Scancode-to-ASCII map for ABNT2 (partial for simplicity)
char scancode_to_ascii[128] = {
    [0x01] = 0x00,   // Escape
    [0x02] = '1',    [0x03] = '2',    [0x04] = '3',    [0x05] = '4',
    [0x06] = '5',    [0x07] = '6',    [0x08] = '7',    [0x09] = '8',
    [0x0A] = '9',    [0x0B] = '0',    [0x0C] = '\'',   [0x0D] = '´',
    [0x0E] = '\b',   // Backspace
    [0x0F] = '\t',   // Tab
    [0x10] = 'q',    [0x11] = 'w',    [0x12] = 'e',    [0x13] = 'r',
    [0x14] = 't',    [0x15] = 'y',    [0x16] = 'u',    [0x17] = 'i',
    [0x18] = 'o',    [0x19] = 'p',    [0x1A] = '´',    [0x1B] = '[', 
    [0x1C] = '\n',   // Enter
    [0x1E] = 'a',    [0x1F] = 's',    [0x20] = 'd',    [0x21] = 'f',
    [0x22] = 'g',    [0x23] = 'h',    [0x24] = 'j',    [0x25] = 'k',
    [0x26] = 'l',    [0x27] = 'ç',    [0x28] = '~',    [0x29] = '`',
    [0x2C] = 'z',    [0x2D] = 'x',    [0x2E] = 'c',    [0x2F] = 'v',
    [0x30] = 'b',    [0x31] = 'n',    [0x32] = 'm',    [0x33] = ',', 
    [0x34] = '.',    [0x35] = '-', 
    [0x39] = ' '     // Space
};

// Uppercase map for Shifted keys
char scancode_to_ascii_shift[128] = {
    [0x02] = '!',    [0x03] = '@',    [0x04] = '#',    [0x05] = '$',
    [0x06] = '%',    [0x07] = '¨',    [0x08] = '&',    [0x09] = '*',
    [0x0A] = '(',    [0x0B] = ')',    [0x0C] = '"',    [0x0D] = '`',
    [0x10] = 'Q',    [0x11] = 'W',    [0x12] = 'E',    [0x13] = 'R',
    [0x14] = 'T',    [0x15] = 'Y',    [0x16] = 'U',    [0x17] = 'I',
    [0x18] = 'O',    [0x19] = 'P',    [0x1A] = '`',    [0x1B] = '{',
    [0x1E] = 'A',    [0x1F] = 'S',    [0x20] = 'D',    [0x21] = 'F',
    [0x22] = 'G',    [0x23] = 'H',    [0x24] = 'J',    [0x25] = 'K',
    [0x26] = 'L',    [0x27] = 'Ç',    [0x28] = '^',    [0x29] = '~',
    [0x2C] = 'Z',    [0x2D] = 'X',    [0x2E] = 'C',    [0x2F] = 'V',
    [0x30] = 'B',    [0x31] = 'N',    [0x32] = 'M',    [0x33] = '<', 
    [0x34] = '>',    [0x35] = '_'
};

// Flag to track Shift key state
static bool shift_pressed = false;

// Convert scancode to ASCII
static char scancode2ASCII(uint8_t scancode) {
    // Check for Shift press/release
    if (scancode == SCANCODE_SHIFT_PRESS) {
        shift_pressed = true;
        return 0;
    } else if (scancode == SCANCODE_SHIFT_RELEASE) {
        shift_pressed = false;
        return 0;
    }

    // Convert scancode to ASCII
    if (scancode < 128) {
        if (shift_pressed) {
            return scancode_to_ascii_shift[scancode];
        } else {
            return scancode_to_ascii[scancode];
        }
    }

    // Unsupported scancode
    return 0;
}