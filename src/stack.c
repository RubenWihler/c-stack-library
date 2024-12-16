
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "fstack.h"
#include "dstack.h"

stack_t* stack_create(stack_type_t type, void* config){
    if (type == STACK_TYPE_FIXED){
        fstack_t *stack = malloc(sizeof(*stack));
        if (!stack) return (perror("malloc failed"), NULL);
        
        fstack_config_t *fconfig = (fstack_config_t*)config;
        if (!fconfig){
            fprintf(stderr, "[!] stack_create : invalid config\n");
            free(stack);
            return NULL;
        }

        if(fstack_init(stack, *fconfig)){
            free(stack);
            return NULL;
        }
        
        return (stack_t*)stack;
    }
    
    if (type == STACK_TYPE_DYNAMIC){
        dstack_t *stack = malloc(sizeof(*stack));
        if (!stack) return (perror("malloc failed"), NULL);
        
        dstack_config_t *dconfig = (dstack_config_t*)config;
        if (!dconfig){
            fprintf(stderr, "[!] stack_create : invalid config\n");
            free(stack);
            return NULL;
        }

        if(dstack_init(stack, *dconfig)){
            free(stack);
            return NULL;
        }
        
        return (stack_t*)stack;
    }
    
    fprintf(stderr, "[!] stack_create : invalid stack type\n");
    return NULL;
}

void stack_destroy(stack_t** stack_ptr){
    if (!stack_ptr || !*stack_ptr){
        fprintf(stderr, "[!] stack_destroy : unable to destroy stack, stack is NULL or invalid\n");
        return;
    }
    
    stack_t *stack = *stack_ptr;
    stack->destroy(stack_ptr);
}

int stack_push(stack_t* stack, void* val){
    if (!stack){
        fprintf(stderr, "[!] stack_push : unable to push, stack is NULL\n");
        return 1;
    }

    if(!val && WARN_STACK_PUSH_NULL){
        fprintf(stderr, "[!] stack_push : pushing a NULL value into the stack (this may cause issues)\n");
    }
    
    return stack->push(stack, val);
}

void* stack_peek(stack_t* stack){
    if (!stack){
        fprintf(stderr, "[!] stack_peek : unable to peek, stack is NULL\n");
        return NULL;
    }
    
    return stack->peek(stack);
}

void* stack_pop(stack_t* stack, void* popped){
    if (!stack){
        fprintf(stderr, "[!] stack_pop : unable to pop, stack is NULL\n");
        return NULL;
    }

    if(!popped && WARN_STACK_POP_INTO_NULL){
        fprintf(stderr, "[!] stack_pop : popping into a NULL value (this may be an unintended behavior)\n");
    }
    
    return stack->pop(stack, popped);
}

bool stack_is_empty(stack_t* stack){
    if (!stack){
        fprintf(stderr, "[!] stack_is_empty : unable to check if stack is empty, stack is NULL\n");
        return true;
    }
    
    return stack->is_empty(stack);
}
