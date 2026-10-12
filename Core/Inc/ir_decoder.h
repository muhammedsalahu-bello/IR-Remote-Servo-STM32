#ifndef IR_DECODER_H_
#define IR_DECODER_H_

#include "main.h"
#include <stdbool.h>

// Explicitly define the enumerator states tracking your NEC state machine logic
typedef enum {
    RESTING_STATE,
	CHECKING_START_STATE,
    COUNTING_SIGNALS_STATE,
} Remote_States;

// Mapped public actions executed by your main runtime loop
void start_ir_sensor(void);
void process_ir_sensor(uint32_t current_stopwatch_time);
bool check_for_new_remote_signal(uint32_t *output_storage_box);

#endif /* IR_DECODER_H_ */
