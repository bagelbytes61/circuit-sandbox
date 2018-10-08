#ifndef ADDR_DECODERS_H_
#define ADDER_DECOERS_H_

#pragma once

#include "logic_gates.h"
#include "miscellaneous.h"

struct addr_decoder_four_bit {
    struct not_gate inverters[4];

    struct and_gate_four_in decoders[16];
};

void addr_decoder_four_bit_initialize(struct addr_decoder_four_bit* decoder, pin_in_t addr_pins)
{
    for (uint8_t i = 0; i < 0x04; ++i) {
        decoder->inverters[i].a = &addr_pins[i];
    }

    for (uint8_t i = 0; i < 0x10; ++i) {
        if (i & 0x01) { decoder->decoders[i].a = decoder->inverters[0].a; }
        else { decoder->decoders[i].a = &decoder->inverters[0].q; }

        if (i & 0x02) { decoder->decoders[i].b = decoder->inverters[1].a; }
        else { decoder->decoders[i].b = &decoder->inverters[1].q; }

        if (i & 0x04) { decoder->decoders[i].c = decoder->inverters[2].a; }
        else { decoder->decoders[i].c = &decoder->inverters[2].q; }

        if (i & 0x08) { decoder->decoders[i].d = decoder->inverters[3].a; }
        else { decoder->decoders[i].d = &decoder->inverters[3].q; }
    }
}

void addr_decoder_four_bit_update(struct addr_decoder_four_bit* decoder)
{
    for (uint8_t i = 0; i < 4; ++i) {
        not_gate_update(&decoder->inverters[i]);
    }

    for (uint8_t i = 0; i < 16; ++i) {
        and_gate_four_in_update(&decoder->decoders[i]);
    }
}

#endif