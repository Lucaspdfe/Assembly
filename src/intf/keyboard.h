#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define readKey _readkey
char _readkey();

#ifdef __cplusplus
}
#endif

#endif  // _KEYBOARD_H_

