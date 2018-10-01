#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

typedef enum {
    BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4,
	BUTTON_5,
	BUTTON_6,
} BUTTON;

bool Button_Get(BUTTON button);

#endif
