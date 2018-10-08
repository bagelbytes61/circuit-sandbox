#ifndef LOGIC_GATES_H_
#define LOGIC_GATES_H_

#pragma once

#include "miscellaneous.h"

struct nand_gate_two_in {
    pin_in_t a;
    pin_in_t b; 

    pin_out_t q;
};

inline void nand_gate_two_in_update(struct nand_gate_two_in* gate)
{
    gate->q = ~(*gate->a & *gate->b);
}

struct nand_gate_four_in {
    pin_in_t a;
    pin_in_t b;
    pin_in_t c;
    pin_in_t d;

    pin_out_t q;
};

inline void nand_gate_four_in_update(struct nand_gate_four_in* gate)
{
    gate->q = ~(*gate->a & *gate->b & *gate->c & *gate->d);
}

struct nor_gate_two_in {
    pin_in_t a;
    pin_in_t b;

    pin_out_t q;
};

inline void nor_gate_two_in_update(struct nor_gate_two_in* gate)
{
    gate->q = ~(*gate->a | *gate->b);
}

struct and_gate_two_in {
    pin_in_t a;
    pin_in_t b;

    pin_out_t q;
};

inline void and_gate_two_in_update(struct and_gate_two_in* gate)
{
    gate->q = (*gate->a & *gate->b);
}

struct and_gate_four_in {
    pin_in_t a;
    pin_in_t b;
    pin_in_t c;
    pin_in_t d;

    pin_out_t q;
};

inline void and_gate_four_in_update(struct and_gate_four_in* gate)
{
    gate->q = (*gate->a & *gate->b & *gate->c & *gate->d);
}

struct or_gate_two_in {
    pin_in_t a;
    pin_in_t b;

    pin_out_t q;
};

inline void or_gate_two_in_update(struct or_gate_two_in* gate)
{
    gate->q = (*gate->a | *gate->b);
}

struct xor_gate_two_in {
    pin_in_t a;
    pin_in_t b;

    pin_out_t q;
};

inline void xor_gate_two_in_update(struct xor_gate_two_in* gate)
{
    gate->q = (*gate->a ^ *gate->b);
}

struct not_gate {
    pin_in_t a;

    pin_out_t q;
};

inline void not_gate_update(struct not_gate* gate)
{
    gate->q = ~*gate->a;
}

#endif