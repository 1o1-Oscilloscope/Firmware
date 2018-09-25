#include <stdbool.h>

extern uint32_t ticks;

typedef struct sw_timer_s {
    uint32_t start_tick;
    uint32_t length;
    bool running;
} sw_timer;

void init_sw_timer(void);

bool tmr_expired(sw_timer timer);

void reset_timer(sw_timer* timer);

#define TIMER(LEN) {0, LEN, true};
