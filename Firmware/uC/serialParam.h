
#ifndef __SERIALPARAM_H
#define __SERIALPARAM_H

#include <stdbool.h>
#include <stdint.h>

void outputParam(uint16_t dutyM1, uint16_t dutyM3, uint16_t deadTime, uint16_t freq, bool forceDuty, bool select_bootStrap);

#endif //__SERIALPARAM_H