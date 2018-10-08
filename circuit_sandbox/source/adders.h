#ifndef ADDERS_H_
#define ADDERS_H_

#pragma once

#include "logic_gates.h"
#include "miscellaneous.h"

struct half_adder {
    struct xor_gate_two_in xor_0;
    struct and_gate_two_in and_0;
};

void half_adder_initialize(struct half_adder* adder, pin_in_t a, pin_in_t b)
{
    adder->xor_0.a = a;
    adder->xor_0.b = b;

    adder->and_0.a = a;
    adder->and_0.b = b;
}

void half_adder_update(struct half_adder* adder)
{
    xor_gate_two_in_update(&adder->xor_0);
    and_gate_two_in_update(&adder->and_0);
}

struct full_adder {
    struct xor_gate_two_in xor_0;
    struct xor_gate_two_in xor_1;
    struct and_gate_two_in and_0;
    struct and_gate_two_in and_1;
    struct or_gate_two_in  or_0;
};

void full_adder_initialize(struct full_adder* adder, pin_in_t a, pin_in_t b, pin_in_t c)
{
    adder->xor_0.a = a;
    adder->xor_0.b = b;

    adder->xor_1.a = &adder->xor_0.q;
    adder->xor_1.b = c;

    adder->and_0.a = &adder->xor_0.q;
    adder->and_0.b = c;

    adder->and_1.a = a;
    adder->and_1.b = b;

    adder->or_0.a = &adder->and_0.q;
    adder->or_0.b = &adder->and_1.q;
}

void full_adder_update(struct full_adder* adder)
{
    xor_gate_two_in_update(&adder->xor_0);
    xor_gate_two_in_update(&adder->xor_1);

    and_gate_two_in_update(&adder->and_0);
    and_gate_two_in_update(&adder->and_1);

    or_gate_two_in_update(&adder->or_0);
}

struct eight_bit_adder {
    struct half_adder ha0;
    struct full_adder fas[7];
};

void eight_bit_adder_initialize(struct eight_bit_adder* adder, pin_in_t a_pins, pin_in_t b_pins)
{
    half_adder_initialize(&adder->ha0, &a_pins[7], &b_pins[7]);

    full_adder_initialize(&adder->fas[0], &a_pins[6], &b_pins[6], &adder->ha0.and_0.q);
    full_adder_initialize(&adder->fas[1], &a_pins[5], &b_pins[5], &adder->fas[0].or_0.q);
    full_adder_initialize(&adder->fas[2], &a_pins[4], &b_pins[4], &adder->fas[1].or_0.q);
    full_adder_initialize(&adder->fas[3], &a_pins[3], &b_pins[3], &adder->fas[2].or_0.q);
    full_adder_initialize(&adder->fas[4], &a_pins[2], &b_pins[2], &adder->fas[3].or_0.q);
    full_adder_initialize(&adder->fas[5], &a_pins[1], &b_pins[1], &adder->fas[4].or_0.q);
    full_adder_initialize(&adder->fas[6], &a_pins[0], &b_pins[0], &adder->fas[5].or_0.q);
}

void eight_bit_adder_update(struct eight_bit_adder* adder)
{
    half_adder_update(&adder->ha0);

    full_adder_update(&adder->fas[0]);
    full_adder_update(&adder->fas[1]);
    full_adder_update(&adder->fas[2]);
    full_adder_update(&adder->fas[3]);
    full_adder_update(&adder->fas[4]);
    full_adder_update(&adder->fas[5]);
    full_adder_update(&adder->fas[6]);
}

#endif