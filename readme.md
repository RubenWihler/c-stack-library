# C-Stack-Library

Une petite bibliothèque de pile genérique en C.
Il existe deux implémentations de pile, une basée sur un tableau et l'autre basée sur une liste chaînée.
    - La pile basée sur un tableau est plus rapide, mais elle a une taille fixe.
    - La pile basée sur une liste chaînée est plus lente, mais elle n'a pas de limite de taille.

## Fonctionnalité

- [x] Pile de taille fixe
- [x] Pile de taille dynamique
- [x] Push
- [x] Pop
- [x] Peek
- [x] Is Empty

## Utilisation

Voici un exemple d'utilisation d'une pile de taille fixe :

```c
struct user_t {
    size_t id;
    char name[20];
    uint age;
};

//création d'une pile de taille fixe
//la configuration de la pile est passée en argument
//ici c'est une configuration pour une pile de taille fixe : fstack_config_t
//la taille de la pile est de 10 éléments
//la taille de chaque élément est la taille de la structure user_t
stack_t *stack = stack_create(STACK_TYPE_FIXED, &(fstack_config_t){
    .length = 10, 
    .size = sizeof(struct user_t)
});

//l'utilisateur à ajouter à la pile
struct user_t user = {
    .id = 0,
    .name = "Alice",
    .age = 20
};

//exemple de push
stack_push(stack, &user);

//exemple de peek
printf("stack peek: %s\n", ((struct user_t *)stack_peek(stack))->name);

//exemple de pop
struct user_t user_popped;
stack_pop(stack, &user_popped);

//libération de la mémoire de la pile
stack_destroy(&stack);

```

Voici la même chose avec une pile de taille dynamique :

```c
struct user_t {
    size_t id;
    char name[20];
    uint age;
};

//création d'une pile de taille dynamique
//la configuration de la pile est passée en argument
//ici c'est une configuration pour une pile de taille dynamique : dstack_config_t
//la taille de chaque élément est la taille de la structure user_t
stack_t *stack = stack_create(STACK_TYPE_DYNAMIC, &(dstack_config_t){
    .size = sizeof(struct user_t)
});

//l'utilisateur à ajouter à la pile
struct user_t user = {
    .id = 0,
    .name = "Alice",
    .age = 20
};

//exemple de push
stack_push(stack, &user);

//exemple de peek
printf("stack peek: %s\n", ((struct user_t *)stack_peek(stack))->name);

//exemple de pop
struct user_t user_popped;
stack_pop(stack, &user_popped);

//libération de la mémoire de la pile
stack_destroy(&stack);
```

Comme vous pouvez le voir, l'utilisation est la même pour les deux types de piles.
La seule différence est la configuration passée à la fonction `stack_create`.

## Compilation

Pour compiler la bibliothèque, vous pouvez utiliser le fichier `Makefile` fourni.

```bash
make lib
```

## Tests

Pour exécuter les tests, vous pouvez utiliser le fichier `Makefile` fourni.

```bash
make test
```

## Auteur

- [Ruben Wihler](https://github.com/RubenWihler)
