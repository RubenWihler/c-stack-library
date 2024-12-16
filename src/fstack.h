#ifndef __FSTACK_H__
#define __FSTACK_H__

#include "stack.h"

typedef struct _fstack_t{
    stack_t base;
    void *data;
    size_t top;
    size_t length;
} fstack_t;

int fstack_init(fstack_t* stack, fstack_config_t config);


#endif // __FSTACK_H__
