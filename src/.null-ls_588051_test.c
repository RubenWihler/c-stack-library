
/* 
Cas de tests: 

1. Tests de base sur les opérations de la pile

    Initialisation :
        Vérifier que la pile est correctement initialisée avec une taille donnée.
        Vérifier qu'une tentative d'initialisation avec une taille nulle ou invalide échoue.

    Push :
        Pousser un seul élément sur une pile vide.
        Pousser plusieurs éléments et vérifier l'ordre d'insertion (dernier entré, premier sorti - LIFO).
        Pousser un élément nul (valeur NULL ou invalide) et s'assurer que l'opération est rejetée.

    Pop :
        Extraire un élément d'une pile contenant un seul élément.
        Extraire plusieurs éléments d'une pile avec plusieurs éléments.
        Extraire un élément d'une pile vide (doit échouer ou retourner un indicateur d'échec).

    Peek (si implémenté) :
        Regarder le sommet de la pile sans la modifier.
        Vérifier que peek sur une pile vide renvoie un état cohérent (par exemple, un pointeur NULL).

2. Tests avancés

    Gestion de la mémoire :
        Vérifier que les données sont correctement copiées lors d’un push (valider que la modification de la source après push n’affecte pas la pile).
        Tester la libération de la mémoire lors d’un pop ou de la destruction de la pile (dstack_free).

    Cas limites :
        Pousser un élément très grand (par exemple, une structure volumineuse ou un tableau).
        Pousser un grand nombre d’éléments jusqu’à ce que la mémoire soit saturée (tester le comportement en cas d’échec d’allocation).

    Réinitialisation et réutilisation :
        Pousser des éléments, vider complètement la pile, puis réutiliser la pile.

3. Tests d’erreur et de robustesse

    Erreurs de mémoire :
        Vérifier le comportement en cas d’échec de l’allocation mémoire (par exemple, simuler un échec de malloc).

    Pointeurs invalides :
        Appeler push, pop ou peek avec une pile non initialisée (NULL).
        Tester avec des valeurs de données invalides (par exemple, un pointeur non valide pour val).

    Concurrentiel (si applicable) :
        Tester l’accès simultané à une même pile par plusieurs threads (uniquement si la bibliothèque est supposée être thread-safe).

4. Scénarios d’utilisation réels

    Manipulation de données de différentes tailles :
        Pousser des entiers, des flottants, des structures et des chaînes de caractères, et s’assurer que tout fonctionne comme attendu.

    Vérification de l’isolation des données :
        Pousser une structure, modifier la structure d'origine après le push, et s'assurer que les données dans la pile ne sont pas modifiées.

    Test de destruction de la pile :
        Créer une pile, y pousser plusieurs éléments, puis la détruire avec dstack_free et vérifier qu’il n’y a pas de fuite mémoire.

    Stress test :
        Effectuer un grand nombre d’opérations (milliers ou millions) de push et pop pour s’assurer que la pile reste fonctionnelle et que les performances sont acceptables.

    Empilement et désempilement partiel :
        Pousser plusieurs éléments, en extraire certains (mais pas tous), et vérifier que les éléments restants sont corrects.
*/



#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#include "stack.h"

typedef struct _test_result {
    bool passed;
    const char *name;
} test_result;

typedef test_result (*unit_test_t)(void);

void print_in_color(char *color, char *text) {
    printf("\033%s", color);
    printf("%s", text);
    printf("\033[0m");
}

void print_in_red(char *text) {
    print_in_color("[0;31m", text);
}

void print_in_green(char *text) {
    print_in_color("[0;32m", text);
}

bool dbl_eq(double a, double b) {
    return fabs(a - b) < 1e-6;
}

/*
 *
 * Write your tests here
 *
 */

test_result t_stack_fixed_create_default() {
    bool passed = true;

    fstack_config_t config = {
        .length = 10,
        .size = sizeof(int)
    };
    stack_t *stack = stack_create(STACK_TYPE_FIXED, &config);
    if (!stack) passed = false;

    stack_destroy(&stack);
    return (test_result){.passed = passed, .name = "Test stack_fixed_create_default"};
}

test_result t_stack_dynamic_create_default() {
    bool passed = true;

    dstack_config_t config = {
        .size = sizeof(int)
    };
    stack_t *stack = stack_create(STACK_TYPE_DYNAMIC, &config);
    if (!stack) passed = false;

    stack_destroy(&stack);
    return (test_result){.passed = passed, .name = "Test stack_dynamic_create_default"};
}

test_result t_stack_fixed_push_pop() {
    bool passed = true;

    fstack_config_t config = {
        .length = 10,
        .size = sizeof(int)
    };
    stack_t *stack = stack_create(STACK_TYPE_FIXED, &config);

    int value_to_push = 42;
    if (stack_push(stack, &value_to_push) != 0) passed = false;
    
    int value_popped;
    if (!stack_pop(stack, &value_popped)) passed = false;
    if (value_popped != 42) passed = false;

    stack_destroy(&stack);
    return (test_result){.passed = passed, .name = "Test stack_fixed_push_pop"};
}

test_result t_stack_dynamic_push_pop(){
    bool passed = true;

    dstack_config_t config = {
        .size = sizeof(int)
    };
    stack_t *stack = stack_create(STACK_TYPE_DYNAMIC, &config);

    int value_to_push = 42;
    if (stack_push(stack, &value_to_push) != 0) passed = false;

    int value_popped;
    if(!stack_pop(stack, &value_popped)) passed = false;
    if (value_popped != 42) passed = false;

    stack_destroy(&stack);
    return (test_result){.passed = passed, .name = "Test stack_dynamic_push_pop"};
}


test_result t_stack_fixed_is_empty() {
    bool passed = true;

    fstack_config_t config = {
        .length = 10,
        .size = sizeof(int)
    };
    stack_t *stack = stack_create(STACK_TYPE_FIXED, &config);

    if (!stack_is_empty(stack)) passed = false;

    int value_to_push = 42;
    stack_push(stack, &value_to_push);

    if (stack_is_empty(stack)) passed = false;

    stack_pop(stack, NULL);

    if (!stack_is_empty(stack)) passed = false;

    stack_destroy(&stack);
    return (test_result){.passed = passed, .name = "Test stack_fixed_is_empty"};
}

test_result t_stack_dynamic_is_empty() {
    bool passed = true;

    dstack_config_t config = {
        .size = sizeof(int)
    };
    stack_t *stack = stack_create(STACK_TYPE_DYNAMIC, &config);

    if (!stack_is_empty(stack)) passed = false;

    int value_to_push = 42;
    stack_push(stack, &value_to_push);

    if (stack_is_empty(stack)) passed = false;

    stack_pop(stack, NULL);

    if (!stack_is_empty(stack)) passed = false;

    stack_destroy(&stack);
    return (test_result){.passed = passed, .name = "Test stack_dynamic_is_empty"};
}

test_result t_stack_peek() {
    bool passed = true;

    fstack_config_t config = {
        .length = 10,
        .size = sizeof(int)
    };
    stack_t *stack = stack_create(STACK_TYPE_FIXED, &config);

    int value_to_push = 42;
    stack_push(stack, &value_to_push);

    int *value_peeked = (int *)stack_peek(stack);
    if (!value_peeked || *value_peeked != 42) passed = false;

    if (stack_is_empty(stack)) passed = false;  // La pile ne doit pas être vide après `peek`.

    stack_destroy(&stack);
    return (test_result){.passed = passed, .name = "Test stack_peek"};
}

test_result t_stack_fixed_overflow() {
    bool passed = true;

    fstack_config_t config = {
        .length = 2,
        .size = sizeof(int)
    };
    stack_t *stack = stack_create(STACK_TYPE_FIXED, &config);

    int value1 = 1, value2 = 2, value3 = 3;
    stack_push(stack, &value1);
    stack_push(stack, &value2);

    if (stack_push(stack, &value3) == 0) passed = false;  // Cela ne doit pas réussir.

    stack_destroy(&stack);
    return (test_result){.passed = passed, .name = "Test stack_fixed_overflow"};
}

test_result t_stack_dynamic_resize() {
    bool passed = true;

    dstack_config_t config = {
        .size = sizeof(int)
    };
    stack_t *stack = stack_create(STACK_TYPE_DYNAMIC, &config);

    int values[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        if (stack_push(stack, &values[i]) != 0) passed = false;
    }

    for (int i = 4; i >= 0; i--) {
        int value_popped;
        if (!stack_pop(stack, &value_popped)) passed = false;
        if (value_popped != values[i]) passed = false;
    }

    stack_destroy(&stack);
    return (test_result){.passed = passed, .name = "Test stack_dynamic_resize"};
}

test_result t_stack_destroy_empty() {
    bool passed = true;

    fstack_config_t config = {
        .length = 10,
        .size = sizeof(int)
    };
    stack_t *stack = stack_create(STACK_TYPE_FIXED, &config);

    stack_destroy(&stack);  // La destruction d'une pile vide ne doit pas causer de problème.

    if (stack) passed = false;

    return (test_result){.passed = passed, .name = "Test stack_destroy_empty"};
}

test_result t_stack_destroy_non_empty() {
    bool passed = true;

    fstack_config_t config = {
        .length = 10,
        .size = sizeof(int)
    };
    stack_t *stack = stack_create(STACK_TYPE_FIXED, &config);

    int value = 42;
    stack_push(stack, &value);

    stack_destroy(&stack);  // La destruction d'une pile non vide doit libérer la mémoire.

    if (stack) passed = false;

    return (test_result){.passed = passed, .name = "Test stack_destroy_non_empty"};
}

test_result t_stack_various_data_types() {
    bool passed = true;

    {// Test with double
        {//fixed
            fstack_config_t config = {
                .length = 10,
                .size = sizeof(double)
            };
            stack_t *stack = stack_create(STACK_TYPE_FIXED, &config);
            
            double value1 = 1.0, value2 = 2.0, value3 = 3.0;
            stack_push(stack, &value1);
            stack_push(stack, &value2);
            stack_push(stack, &value3);

            double value_popped;
            if (!stack_pop(stack, &value_popped)) passed = false;
            if (!dbl_eq(value_popped, 3.0)) passed = false;
        
            stack_destroy(&stack);
        }

        {//dynamic
            dstack_config_t config = {
                .size = sizeof(double)
            };
            stack_t *stack = stack_create(STACK_TYPE_DYNAMIC, &config);
            
            double value1 = 1.0, value2 = 2.0, value3 = 3.0;
            stack_push(stack, &value1);
            stack_push(stack, &value2);
            stack_push(stack, &value3);

            double value_popped;
            if (!stack_pop(stack, &value_popped)) passed = false;
            if (!dbl_eq(value_popped, 3.0)) passed = false;

            stack_destroy(&stack);
        }
    }

    {// Test with struct
        typedef struct {
            int x;
            int y;
        } point_t;


        {//fixed
            fstack_config_t config = {
                .length = 10,
                .size = sizeof(point_t)
            };
            stack_t *stack = stack_create(STACK_TYPE_FIXED, &config);
            
            point_t value1 = {1, 2}, value2 = {3, 4}, value3 = {5, 6};
            stack_push(stack, &value1);
            stack_push(stack, &value2);
            stack_push(stack, &value3);

            point_t value_popped;
            if (!stack_pop(stack, &value_popped)) passed = false;
            if (value_popped.x != 5 || value_popped.y != 6) passed = false;

            stack_destroy(&stack);
        }

        {//dynamic
            dstack_config_t config = {
                .size = sizeof(point_t)
            };
            stack_t *stack = stack_create(STACK_TYPE_DYNAMIC, &config);
            
            point_t value1 = {1, 2}, value2 = {3, 4}, value3 = {5, 6};
            stack_push(stack, &value1);
            stack_push(stack, &value2);
            stack_push(stack, &value3);

            point_t value_popped;
            if (!stack_pop(stack, &value_popped)) passed = false;
            if (value_popped.x != 5 || value_popped.y != 6) passed = false;

            stack_destroy(&stack);
        }
    }

    return (test_result){.passed = passed, .name = "Test stack_various_data_types"};
}

test_result t_stack_fixed_stress_test() {
    bool passed = true;
    
    struct timespec start, end;
    double elapsed_time;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    fstack_config_t config = {
        .length = 1000000,
        .size = sizeof(size_t)
    };
    stack_t *stack = stack_create(STACK_TYPE_FIXED, &config);

    for (size_t i = 0; i < 1000000; i++) {
        stack_push(stack, &i);
    }

    for (size_t i = 999999; i !=  0; i--) {
        size_t value_popped;
        if (!stack_pop(stack, &value_popped)) passed = false;
        if (value_popped != i) passed = false;
    }

    stack_destroy(&stack);
    
    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("fixed stack stress test elapsed time: %f seconds\n", elapsed_time);

    return (test_result){.passed = passed, .name = "Test stress test"};
}

test_result t_stack_dynamic_stress_test() {
    bool passed = true;
    
    struct timespec start, end;
    double elapsed_time;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    dstack_config_t config = {
        .size = sizeof(size_t)
    };
    stack_t *stack = stack_create(STACK_TYPE_DYNAMIC, &config);

    for (size_t i = 0; i < 1000000; i++) {
        size_t value = i;
        stack_push(stack, &value);
    }

    for (size_t i = 999999; i != 0; i--) {
        size_t value_popped;
        if (!stack_pop(stack, &value_popped)) passed = false;
        if (value_popped != i) passed = false;
    }

    stack_destroy(&stack);
    
    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("dynamic stack stress test elapsed time: %f seconds\n", elapsed_time);

    return (test_result){.passed = passed, .name = "Test stress test"};
}


// Add or remove your test function name here
const unit_test_t tests[] = {
    t_stack_fixed_create_default,
    t_stack_dynamic_create_default,
    t_stack_fixed_push_pop,
    t_stack_dynamic_push_pop,
    t_stack_fixed_is_empty,
    t_stack_dynamic_is_empty,
    t_stack_peek,
    t_stack_fixed_overflow,
    t_stack_dynamic_resize,
    t_stack_destroy_empty,
    t_stack_destroy_non_empty,
    t_stack_various_data_types,
    t_stack_fixed_stress_test,
    t_stack_dynamic_stress_test
};

int main(void) {
    uint32_t nb_tests = sizeof(tests) / sizeof(unit_test_t);
    char message[256];
    bool all_passed = true;

    for (uint32_t i = 0; i < nb_tests; i++) {
        printf("Running test n°%d: ...\n", i);
        test_result r = tests[i]();
        if (r.passed) {
            sprintf(message, "\t- %s : OK", r.name);
            print_in_green(message);
        } else {
            all_passed = false;
            sprintf(message, "\t- %s : FAILED", r.name);
            print_in_red(message);
        }
        printf("\n");
    }
    if (all_passed)
        print_in_green("\nTests suite result : OK\n");
    else
        print_in_red("\nTests suite result : FAILED\n");
}