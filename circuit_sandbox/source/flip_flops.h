#ifndef FLIP_FLOPS_H_
#define FLIP_FLOPS_H_

#pragma once

#include "miscellaneous.h"

struct d_flip_flop {
    pin_in_t d;
    pin_in_t e;

    pin_out_t q;
    pin_out_t q_;
};

inline void d_flip_flop_update(struct d_flip_flop* flip_flop)
{
    if (*flip_flop->e) {
        flip_flop->q_ = ~(flip_flop->q = *flip_flop->d);
    }
}

#endif