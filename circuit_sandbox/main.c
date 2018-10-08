#include "source/memory.h"

#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <time.h>

#define CLK_FREQ 2

int main(void)
{
    pin_out_t rd = PIN_LOW;
    pin_out_t wr = PIN_HIGH;
    pin_out_t addr_pins[] = { PIN_HIGH, PIN_HIGH, PIN_LOW, PIN_LOW };
    pin_in_out_t data_pins[] = { {NULL, PIN_LOW}, {NULL, PIN_HIGH}, {NULL, PIN_HIGH}, {NULL, PIN_LOW}, {NULL, PIN_LOW}, 
    {NULL, PIN_LOW}, {NULL, PIN_LOW}, { NULL, PIN_HIGH} };

    struct sram_chip sram_chip;
    sram_chip_initialize(&sram_chip, &rd, &wr, addr_pins, data_pins);

    sram_chip_update(&sram_chip);

    printf("address pins: ");
    for (uint8_t i = 0; i < 4; ++i) {
        printf("%u ", (uint8_t)(~addr_pins[i] + 1));
    }

    printf("\n\ndata pins: ");
    for (uint8_t i = 0; i < 8; ++i) {
        printf("%u ", (uint8_t)(~data_pins[i].out + 1));
    }


    printf("\n\nmemory\n");
    for (uint8_t j = 0; j < 8; ++j) {
        printf("%04xh\t", j);
        for (uint8_t k = 0; k < 8; ++k) {
            printf("%u ", (uint8_t)(~sram_chip.s_mem_cells[j].flip_flops[k].q + 1));
        }
        printf("\n");
    }

    return 0;
}

//    sram_chip_update(&sram_chip);
//
//    sram_chip.wr.state = PIN_HIGH;
//    sram_chip.addr_lns[0].state = PIN_LOW;
//    sram_chip.addr_lns[1].state = PIN_HIGH;
//    sram_chip.addr_lns[2].state = PIN_LOW;
//    sram_chip.addr_lns[3].state = PIN_LOW;
//
//    sram_chip.data_lns[7].state = PIN_LOW;
//    sram_chip.data_lns[6].state = PIN_HIGH;
//    sram_chip.data_lns[5].state = PIN_HIGH;
//    sram_chip.data_lns[4].state = PIN_LOW;
//    sram_chip.data_lns[3].state = PIN_LOW;
//    sram_chip.data_lns[2].state = PIN_LOW;
//    sram_chip.data_lns[1].state = PIN_LOW;
//    sram_chip.data_lns[0].state = PIN_HIGH;
//
//
//    sram_chip_update(&sram_chip);
//
//    time_t updated_cycles, current_cycle;
//    time(&updated_cycles);
//
//    while (1) {
//        time(&current_cycle);
//        while (current_cycle - updated_cycles > CLK_FREQ) {
//
//
//
//
//            updated_cycles += CLK_FREQ;
//        }
//
//        time(&current_cycle);
//    }
//
//    return 0;
//}

//void d_flip_flop_set_pin_state(struct d_flip_flop* flip_flop, uint8_t pin, uint8_t state)
//{
//    switch (pin) {
//        case D_FLIP_FLOP_PIN_D:
//            flip_flop->d = state;
//            break;
//        case D_FLIP_FLOP_PIN_E:
//            flip_flop->e = state;
//            break;
//    }
//}

//if (flip_flop_a.q == PIN_LOW) {
//    d_flip_flop_set_pin_state(&flip_flop_a, D_FLIP_FLOP_PIN_D, PIN_HIGH);
//    if (flip_flop_a.e == PIN_HIGH) {
//        d_flip_flop_set_pin_state(&flip_flop_a, D_FLIP_FLOP_PIN_E, PIN_LOW);
//    }
//}
//else {
//    d_flip_flop_set_pin_state(&flip_flop_a, D_FLIP_FLOP_PIN_D, PIN_LOW);
//    if (flip_flop_a.e = PIN_LOW) {
//        d_flip_flop_set_pin_state(&flip_flop_a, D_FLIP_FLOP_PIN_E, PIN_HIGH);
//    }
//}