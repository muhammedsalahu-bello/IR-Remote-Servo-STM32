/*
 * ir_decoder.c
 *
 *  Created on: Oct 6, 2026
 *      Author: user
 */
   #include "ir_decoder.h"
   #include <stdbool.h>

// Explicitly declare your file-scoped processing variables as static
static uint32_t previous_pulse_time = 0;
static uint32_t bit_32_storage_buffer = 0;
static uint32_t bit_successfully_stored = 0;
static bool new_command_available = false;  // Handled by adding <stdbool.h> in your header
static uint32_t final_bit_storage = 0;
static Remote_States internal_state = RESTING_STATE;

void start_ir_sensor(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE(); // Enable clock power to Port A

    // FIX 1: Use standard C assignment instead of C++ brace initialization {0}
    GPIO_InitTypeDef pin_checklist;
    pin_checklist.Pin = GPIO_PIN_0;
    pin_checklist.Mode = GPIO_MODE_IT_FALLING;
    pin_checklist.Pull = GPIO_PULLUP;
    pin_checklist.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOA, &pin_checklist);
}

void process_ir_sensor(uint32_t current_stopwatch_time) {
    uint32_t time_difference = current_stopwatch_time - previous_pulse_time;
    previous_pulse_time = current_stopwatch_time;

    if (time_difference >= 13000 && time_difference <= 14000) {
        internal_state = COUNTING_SIGNALS_STATE;
        bit_successfully_stored = 0;
        bit_32_storage_buffer = 0;
    } else if (internal_state == COUNTING_SIGNALS_STATE) {
        if (time_difference >= 1120 && time_difference <= 1130) {
            bit_32_storage_buffer = bit_32_storage_buffer >> 1;
            bit_successfully_stored++;
        } else if (time_difference >= 2200 && time_difference <= 2300) {
            bit_32_storage_buffer = bit_32_storage_buffer >> 1;
            bit_32_storage_buffer = bit_32_storage_buffer | 0x80000000;
            bit_successfully_stored++;
        } else {
            internal_state = RESTING_STATE;
        }

        if (bit_successfully_stored >= 32) {
            final_bit_storage = bit_32_storage_buffer;
            new_command_available = true;
            internal_state = RESTING_STATE;
        }
    }
}

bool check_for_new_remote_signal(uint32_t *output_storage_box) {
    if (new_command_available) {
        *output_storage_box = final_bit_storage;
        new_command_available = false; // Clear mailbox flag
        return true;
    }
    return false;
}



