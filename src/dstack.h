#ifndef __DSTACK_H__
#define __DSTACK_H__

#include "stack.h"

typedef struct _node_t{
    void *data;
    struct _node_t *next;
} node_t;

typedef struct _dstack_t {
    stack_t base;
    node_t *top;
} dstack_t;

int dstack_init(dstack_t* stack, dstack_config_t config);

#endif // __DSTACK_H__
