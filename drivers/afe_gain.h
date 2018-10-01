#ifndef GAIN_SET_H
#define GAIN_SET_H

typedef enum {
    GAIN_OFF, // Disconnect the op-amp
    GAIN_1,   // 1X total Gain
    GAIN_0_5, // 0.5X total Gain
	GAIN_0_1  // 0.1X total gain
} afe_gain_t;

void afe_gain_set (afe_gain_t gain);

#endif