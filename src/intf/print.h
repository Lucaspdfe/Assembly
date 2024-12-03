#ifndef _PRINT_H_
#define _PRINT_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define clrscr print_clear
void print_clear();
#define putc _putchar
void _putchar(char character);
#define puts print_str
void print_str(char* string);
void print_set_color(uint8_t foreground, uint8_t background);

#ifdef __cplusplus
}
#endif


#endif  // _PRINT_H_
