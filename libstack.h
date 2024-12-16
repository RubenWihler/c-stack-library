#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>
#include <stddef.h>

#define WARN_STACK_POP_INTO_NULL true
#define WARN_STACK_PUSH_NULL true

// Les différents types de stack
// STACK_TYPE_FIXED: stack avec une taille fixe - approche tableau
// STACK_TYPE_DYNAMIC: stack avec une taille dynamique - approche liste chaînée
typedef enum {
    STACK_TYPE_FIXED,
    STACK_TYPE_DYNAMIC,
} stack_type_t;

///@brief La configuration d'une pile avec une taille fixe
///@param length: La taille de la pile
///@param size: La taille d'un element de la pile
typedef struct _fstack_config_t{
    size_t length;
    size_t size;
} fstack_config_t;

///@brief La configuration d'une pile avec une taille dynamique
///@param size: La taille d'un element de la pile
typedef struct _dstack_config_t{
    size_t size;
} dstack_config_t;

///@brief La structure d'une pile generique
///@param type: Le type de la pile (STACK_TYPE_FIXED ou STACK_TYPE_DYNAMIC)
///@param size: La taille d'un element de la pile
typedef struct _stack_t{
    stack_type_t type;
    size_t size;
    
    void (*destroy)(struct _stack_t** self_ptr);
    int (*push)(struct _stack_t* self, void* val);
    void* (*peek)(struct _stack_t* self);
    void* (*pop)(struct _stack_t* self, void* popped);
    bool (*is_empty)(struct _stack_t* self);
} stack_t;

///@brief Cree une pile generique
///@param type: Le type de la pile (STACK_TYPE_FIXED ou STACK_TYPE_DYNAMIC)
///@param config: La configuration de la pile (fstack_config_t ou dstack_config_t)
///@return Un pointeur vers la pile cree
///
///@error retourne NULL si la creation a echoue (print un message d'erreur)
stack_t* stack_create(stack_type_t type, void* config);

///@brief Detruit une pile generique
///@param stack_ptr: Un pointeur vers un pointeur de la pile a detruire
///@note le pointeur de la pile est mis a NULL
void stack_destroy(stack_t** stack_ptr);

///@brief Ajoute une copie de la valeur passe en parametre au sommet de la pile
///@param stack: La pile
///@param val: L'element a ajouter
///@return 0 si l'ajout a reussi, -1 sinon
///
///@error retourne -1 si l'ajout a echoue (print un message d'erreur)
int stack_push(stack_t* stack, void* val);

///@brief Retourne l'adresse de l'element au sommet de la pile
///@param stack: La pile
///@return Un pointeur vers l'element au sommet de la pile
void* stack_peek(stack_t* stack);

///@brief Retire l'element au sommet de la pile et le copie dans popped
///@param stack: La pile
///@param popped: L'enplacement ou stocker l'element retire (peut etre NULL)
///@return Un pointeur vers popped (donc NULL si popped est NULL)
///
///@note NULL est retourne si la pile est vide
///@note Si popped est NULL, l'element retire n'est pas copie et est libere
///@note Nous ne pouvons pas retourner l'adresse de l'element retire car il est libere
///@note Si popped est NULL, cela genere par defaut un warning (mettre WARN_STACK_POP_INTO_NULL a false pour le desactiver)
void* stack_pop(stack_t* stack, void* popped);

///@brief Verifie si la pile est vide
///@param stack: La pile
///@return true si la pile est vide, false sinon
bool stack_is_empty(stack_t* stack);

#endif // __STACK_H__
