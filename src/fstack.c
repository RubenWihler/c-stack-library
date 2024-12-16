

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "stack.h"
#include "fstack.h"

static void fstack_destroy(stack_t** stack_ptr);
static int fstack_push(stack_t* stack, void* val);
static void* fstack_peek(stack_t* stack);
static void* fstack_pop(stack_t* stack, void* popped);
static bool fstack_is_empty(stack_t* stack);

int fstack_init(fstack_t* stack, fstack_config_t config){
    if (!stack) return (fprintf(stderr, "[!] fstack_init : invalid stack pointer\n"), -1);
    if (config.size == 0) return (fprintf(stderr, "[!] fstack_init : invalid config size : size must be > 0\n"), -1);
    if (config.length == 0) return (fprintf(stderr, "[!] fstack_init : invalid config length : length must be > 0\n"), -1);

    memset(stack, 0, sizeof(*stack));

    stack->base = (stack_t){
        .type = STACK_TYPE_FIXED,
        .size = config.size,
        .destroy = fstack_destroy,
        .push = fstack_push,
        .peek = fstack_peek,
        .pop = fstack_pop,
        .is_empty = fstack_is_empty
    };

    stack->data = calloc(config.length, config.size);
    if (!stack->data) return (perror("calloc failed"), -1);

    stack->top = 0;
    stack->length = config.length;

    return 0;
}

static void fstack_destroy(stack_t** stack){
    assert(stack && *stack);
    
    free(((fstack_t*)*stack)->data);
    free(*stack);
    *stack = NULL;
}

static int fstack_push(stack_t* stack, void* val){
    assert(stack && val);

    fstack_t *fstack = (fstack_t*)stack;
    
    if(fstack->top == fstack->length){
        fprintf(stderr, "[!] fstack_push : unable to push, stack is full\n");
        return 1;
    }
    
    void* dest = ((char*)fstack->data)+(fstack->top * stack->size);
    memcpy(dest, val, stack->size);

    fstack->top++;

    return 0;
}

static void* fstack_peek(stack_t* stack){
    assert(stack);

    fstack_t *fstack = (fstack_t*)stack;

    if(fstack_is_empty(stack))
        return NULL;

    //on fait -1 car l'array commence a 0 et notre top a 1 (0 est quand la pile est vide)
    return ((char*)fstack->data)+(fstack->top - 1) * stack->size;
}

static void* fstack_pop(stack_t* stack, void* popped){
    if(!stack){
        fprintf(stderr, "[!] fstack_pop : unable to pop, given stack pointer is NULL\n");
        return NULL;
    }
    
    void *res = fstack_peek(stack);
    
    if (!res){
        fprintf(stderr, "[!] fstack_pop : unable to pop, stack is empty\n");
        return NULL;
    }

    fstack_t *fstack = (fstack_t*)stack;
    fstack->top--;

    if(popped) 
        memcpy(popped, res, stack->size);

    return popped;
}

static bool fstack_is_empty(stack_t* stack){
    if(!stack){
        fprintf(stderr, "[!] fstack_is_empty : unable to check if stack is empty, given stack pointer is NULL\n");
        return true;
    }

    return ((fstack_t*)stack)->top == 0;
}
