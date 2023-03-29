#ifndef GPIO_H
#define GPIO_H

#include <stdlib.h>

void set_pin(char* pin, int state);
void init_pin(char* pin, char* direction);

#endif

