#ifndef MISCELLANEOUS_H_
#define MISCELLANEOUS

#pragma once

#include <stdint.h>

typedef uint8_t *pin_in_t, pin_out_t;

typedef struct {
    uint8_t *in, out;
} pin_in_out_t;

#define PIN_LOW  0x00
#define PIN_HIGH 0xFF

#endif
