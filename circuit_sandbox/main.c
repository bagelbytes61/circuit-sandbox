#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <time.h>

#define VCC     0x0000001
#define CLK     0x0000002
#define WR      0x0000004
#define RD      0x0000008
#define CS      0x0000010

#define A0      0x0000020
#define A1      0x0000040
#define A2      0x0000080
#define A3      0x0000100
#define A4      0x0000200
#define A5      0x0000400
#define A6      0x0000800
#define A7      0x0001000
#define A8      0x0002000
#define A9      0x0004000
#define A10     0x0008000
#define A11     0x0010000
#define A12     0x0020000
#define A13     0x0040000
#define A14     0x0080000
#define A15     0x0100000

#define D0      0x00200000
#define D1      0x00400000
#define D2      0x00800000
#define D3      0x01000000
#define D4      0x02000000
#define D5      0x04000000
#define D6      0x08000000
#define D7      0x10000000

#define RESET   0x20000000
#define AUDIO   0x40000000
#define GND     0x80000000


#define D_TYPE_FLIP_FLOP_PIN_D 0x01
#define D_TYPE_FLIP_FLOP_PIN_E 0x02

#define PIN_LOW  0
#define PIN_HIGH 1

struct d_type_flip_flop {
    uint8_t d : 1;
    uint8_t e : 1;

    uint8_t q : 1;
    uint8_t q_ : 1;

    uint8_t state : 1;
};

void d_type_flip_flop_set_pin_state(struct d_type_flip_flop* gate, uint8_t pin, uint8_t state)
{
    switch (pin) {
        case D_TYPE_FLIP_FLOP_PIN_D:
            gate->d = state;
            break;
        case D_TYPE_FLIP_FLOP_PIN_E:
            gate->e = state;
            break;
    }
}

void d_type_flip_flop_update(struct d_type_flip_flop* gate)
{
    gate->q = (((gate->d ^ ~gate->e) & ~(gate->e ^ gate->d)) & (gate->state & ~gate->e)) | (gate->d & gate->e);
    gate->q_ = ~gate->q;
    gate->state = gate->q;
}

#define TIME_STEP 3

int main(void)
{
    struct d_type_flip_flop gate_a;
    memset(&gate_a, 0, sizeof gate_a);

    time_t updated_time, current_time;
    time(&updated_time);

    while (1) {
        time(&current_time);
        while (current_time - updated_time > TIME_STEP) {
            if (gate_a.q == PIN_LOW) {
                d_type_flip_flop_set_pin_state(&gate_a, D_TYPE_FLIP_FLOP_PIN_D, PIN_HIGH);
                d_type_flip_flop_set_pin_state(&gate_a, D_TYPE_FLIP_FLOP_PIN_E, PIN_HIGH);
            }
            else {
                d_type_flip_flop_set_pin_state(&gate_a, D_TYPE_FLIP_FLOP_PIN_D, PIN_LOW);
                d_type_flip_flop_set_pin_state(&gate_a, D_TYPE_FLIP_FLOP_PIN_E, PIN_HIGH);
            }

            d_type_flip_flop_update(&gate_a);

            printf("state\nd: %u\ne: %u\n\nq: %u\nq_:%u\n\n", gate_a.d, gate_a.e, gate_a.q, gate_a.q_);

            updated_time += TIME_STEP;
        }

        time(&current_time);
    }

    return 0;
}