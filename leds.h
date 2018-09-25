#ifndef LEDS_H
#define LEDS_H

#include <stdbool.h>
typedef enum
{
    LED_NONE,
    LED_1,
    LED_2,
	LED_3
} LED;

#define LED_COUNT 3

void LED_On(LED led);

void LED_Off(LED led);

void LED_Toggle(LED led);

bool LED_Get(LED led);

#endif //LEDS_H
