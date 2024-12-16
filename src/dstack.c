
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "stack.h"
#include "dstack.h"

static void dstack_destroy(stack_t** stack_ptr);
static int dstack_push(stack_t* stack, void* val);
static void* dstack_peek(stack_t* stack);
static void* dstack_pop(stack_t* stack, void* popped);
static bool dstack_is_empty(stack_t* stack);

int dstack_init(dstack_t* stack, dstack_config_t config){
    if (!stack) return (fprintf(stderr, "[!] dstack_init : invalid stack pointer\n"), -1);
    if (config.size == 0) return (fprintf(stderr, "[!] dstack_init : invalid config size : size must be > 0\n"), -1);

    memset(stack, 0, sizeof(*stack));

    stack->base = (stack_t){
        .type = STACK_TYPE_DYNAMIC,
        .size = config.size,
        .destroy = dstack_destroy,
        .push = dstack_push,
        .peek = dstack_peek,
        .pop = dstack_pop,
        .is_empty = dstack_is_empty
    };

    stack->top = NULL;

    return 0;
}

static void dstack_destroy(stack_t** stack_ptr){
    assert(stack_ptr && *stack_ptr);
    dstack_t *stack = (dstack_t*)*stack_ptr;

    while(stack->top){
        node_t *tmp = stack->top;
        stack->top = stack->top->next;
        free(tmp);
    }

    free(stack);
    *stack_ptr = NULL;
}

//Fait une COPIE de la valeur et l'ajoute au sommet de la pile
static int dstack_push(stack_t* stack, void* val){
    assert(stack && val);

    dstack_t *dstack = (dstack_t*)stack;
    
    node_t *n = malloc(sizeof(*n));
    if(!n) return (perror("malloc failed"), -1);

    n->data = malloc(stack->size);
    if(!n->data) return (perror("malloc failed"), -1);
    
    memcpy(n->data, val, stack->size);
    
    n->next = dstack->top;
    dstack->top = n;
    
    return 0;
}

static void* dstack_peek(stack_t* stack){
    assert(stack);
    dstack_t *dstack = (dstack_t*)stack;

    if(dstack_is_empty(stack)) return NULL;
    return dstack->top->data;
}

static void* dstack_pop(stack_t* stack, void* popped){
    assert(stack);
    dstack_t *dstack = (dstack_t*)stack;

    if(dstack_is_empty(stack)) return NULL;

    node_t *n = dstack->top;
    dstack->top = n->next;

    if(popped)
        memcpy(popped, n->data, stack->size);

    free(n->data);
    free(n);

    return popped;
}

static bool dstack_is_empty(stack_t* stack){
    assert(stack);
    return ((dstack_t*)stack)->top == NULL;
}


