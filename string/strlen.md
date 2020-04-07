# strlen

```c
#include <string.h>
```

The `sizeof` operator gives **the size of things in bytes**. The `strlen()` function gives **the length of a string in characters**. Because it takes one byte to hold one character, you might suppose that both would give the same result when applied to a string, but they don’t.

```c
// try the %u or %lu specifiers if your implementation
// does not recognize the %zd specifier

char name[40];
printf("What's your name? ");
scanf("%s", name);
printf("Hello, %s.\n", name);
printf("Your name of %zd letters occupies %zd memory cells.\n", strlen(name), sizeof name);
```

```text
What's your name? Serendipity Chance
Hello, Serendipity.
Your name of 11 letters occupies 40 memory cells.
```

The C99 and C11 standards use a `%zd` specifier for the type used by the `sizeof` operator. This also applies for type returned by `strlen()`. For earlier versions of C you need to know the actual type returned by `sizeof` and `strlen()`; typically that would be `unsigned` or `unsigned long`.

One other point: The preceding chapter used `sizeof` with parentheses, but this example doesn’t. Whether you use parentheses depends on whether you want **the size of a type** or **the size of a particular quantity**. Parentheses are required for **types** but are optional for **particular quantities**. That is, you would use `sizeof(char)` or `sizeof(float)` but can use `sizeof name` or `sizeof 6.28`. However, it is all right to use parentheses in these cases, too, as in `sizeof(6.28)`.

