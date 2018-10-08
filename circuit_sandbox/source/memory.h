#ifndef MEMORY_H_
#define MEMORY_H_

#pragma once

#include "addr_decoders.h"
#include "flip_flops.h"
#include "miscellaneous.h"

#include <memory.h>

struct s_mem_cell {
    struct d_flip_flop flip_flops[8];
};

void s_mem_cell_initialize(struct s_mem_cell* cell, pin_in_t* data_pins, pin_in_t e)
{
    //cell->flip_flops[0].e = e;

    for (uint8_t i = 0; i < 8; ++i) {
        cell->flip_flops[i].d = data_pins[i];
        cell->flip_flops[i].e = e;
    }
}

void s_mem_cell_update(struct s_mem_cell* cell)
{
    for (uint8_t i = 0; i < 8; ++i) {
        d_flip_flop_update(&cell->flip_flops[i]);
    }
}

struct sram_chip {

    struct addr_decoder_four_bit decoder;
    struct s_mem_cell s_mem_cells[8];
};

void sram_chip_initialize(struct sram_chip* chip, pin_in_t rd, pin_in_t wr, pin_in_t addr_pins, pin_in_out_t* data_pins)
{
    memset(chip, 0, sizeof *chip);

    addr_decoder_four_bit_initialize(&chip->decoder, addr_pins);

    for (int8_t i = 0; i < 8; ++i) {
        pin_in_t data_pins_in[] = { &data_pins[0].out,  &data_pins[1].out, &data_pins[2].out, &data_pins[3].out, 
            &data_pins[4].out,  &data_pins[5].out, &data_pins[6].out, &data_pins[7].out };
        s_mem_cell_initialize(&chip->s_mem_cells[i], data_pins_in, &chip->decoder.decoders[i].q);
    }
}

void sram_chip_update(struct sram_chip* chip)
{
    addr_decoder_four_bit_update(&chip->decoder);

    for (uint8_t i = 0; i < 4; ++i) {
        s_mem_cell_update(&chip->s_mem_cells[i]);
    }
}

#endif