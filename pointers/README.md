# Pointers

<!-- TOC -->

- [1. The Indirection Operator: `*`](#1-the-indirection-operator)
- [Declaring Pointers](#declaring-pointers)
- [Using Pointers to Communicate Between Functions](#using-pointers-to-communicate-between-functions)
- [2. Summary: Pointer-Related Operators](#2-summary-pointer-related-operators)

<!-- /TOC -->

Pointers? What are they? Basically, **a pointer** is **a variable** (or, more generally, a data object) whose value is a **memory address**. Just as a `char` variable has a character as a value and an `int` variable has an integer as a value, the **pointer variable** has an address as a value. Pointers have many uses in C.

If you give a particular pointer variable the name `ptr`, you can have statements such as the following:

```c
ptr = &pooh; // assigns pooh's address to ptr
```

We say that `ptr` “points to” `pooh`. The difference between `ptr` and `&pooh` is that `ptr` is a **variable**, and `&pooh` is a **constant**. If you want, you can make `ptr` point elsewhere:

```c
ptr = &bah; // make ptr point to bah instead of to pooh
```

Now the value of `ptr` is the address of `bah`.

To create **a pointer variable**, you need to be able to **declare its type**. Suppose you want to declare `ptr` so that it can hold the address of an `int`. To make this declaration, you need to use a new operator. Let’s examine that operator now.

## 1. The Indirection Operator: `*`

Suppose you know that `ptr` points to `bah`, as shown here:

```c
ptr = &bah;
```

Then you can use the **indirection** operator `*` (also called the **dereferencing operator**) to find the value stored in `bah` (don’t confuse this unary indirection operator with the binary `*` operator of multiplication—same symbol, different syntax):

```c
val = *ptr; // finding the value ptr points to
```

The statements `ptr = &bah;` and `val = *ptr;` taken together amount to the following statement:

```c
val = bah;
```

Using the **address** and **indirection operators** is a rather indirect way of accomplishing this result, hence the name “**indirection operator**.”

## Declaring Pointers

You already know how to declare int variables and other fundamental types. How do you **declare a pointer variable**? You might guess that the form is like this:

```c
pointer ptr; // not the way to declare a pointer
```

Why not? Because it is not enough to say that a variable is a pointer. You also have to specify the kind of variable to which the pointer points. The reason is that different variable types take up different amounts of storage, and some pointer operations require knowledge of that storage size. Also, the program has to know what kind of data is stored at the address. A long and a float might use the same amount of storage, but they store numbers quite differently. Here’s how pointers are declared:

```c
int * pi; // pi is a pointer to an integer variable
char * pc; // pc is a pointer to a character variable
float * pf, * pg; // pf, pg are pointers to float variables
```

**The space** between the `*` and **the pointer name** is optional. Often, programmers **use the space** in a **declaration** and **omit it** when **dereferencing a variable**.

The value (`*pc`) of what `pc` points to is of type `char`. What of `pc` itself? We describe it as being of type “**pointer to char**.” The value of `pc` is an **address**, and it is represented internally as an unsigned integer on most systems. However, you shouldn’t think of a pointer as an integer type. There are things you can do with integers that you can’t do with pointers, and vice versa. For example, you can multiply one integer by another, but you can’t multiply one pointer by another. So a pointer really is a new type, not an integer type. Therefore, as mentioned before, ANSI C provides the `%p` form specifically for pointers.

## Using Pointers to Communicate Between Functions

We have touched only the surface of the rich and fascinating world of pointers, but our concern here is **using pointers to solve our communication problem**.

The following listing shows a program that uses pointers to make the `interchange()` function work. Let’s look at it, run it, and then try to understand how it works.

```c
/* using pointers to make swapping work */
#include <stdio.h>
void interchange(int * u, int * v);

int main(void)
{
    int x = 5, y = 10;
    printf("Originally x = %d and y = %d.\n", x, y);
    interchange(&x, &y); // send addresses to function
    printf("Now x = %d and y = %d.\n", x, y);
    return 0;
}

void interchange(int * u, int * v)
{
    int temp;
    temp = *u;
    *u = *v;
    *v = temp; // temp gets value that u points to
}
```

First, the function call looks like this:

```c
interchange(&x, &y);
```

Instead of transmitting the **values** of `x` and `y`, the function transmits their **addresses**. That means the formal arguments `u` and `v`, appearing in the prototype and in the definition of `interchange()`, will have **addresses** as their values. Therefore, they should be declared as **pointers**. Because `x` and `y` are integers, `u` and `v` are pointers to integers, so declare them as follows:

```c
void interchange (int * u, int * v)
```

Next, the body of the function declares

```c
int temp;
```

to provide the needed temporary storage. To store the value of `x` in `temp`, use

```c
temp = *u;
```

Remember, `u` has the value `&x`, so `u` points to `x`. This means that `*u` gives you the value of `x`, which is what we want. Don’t write

```c
temp = u; /* NO */
```

because that would assign `temp` the **address** of `x` rather than its **value**, and we are trying to interchange values, not addresses.

Similarly, to assign the value of `y` to `x` , use

```c
*u = *v;
```

which ultimately has this effect:

```c
x = y;
```

You can omit the variable names in the ANSI C prototype. Then the prototype declaration looks like this:

```c
void interchange(int *, int *);
```

In general, you can communicate two kinds of information about a variable to a function. If you use a call of the form

```c
function1(x);
```

you transmit the **value** of `x`. If you use a call of the form

```c
function2(&x);
```

you transmit the **address** of `x`. The first form requires that the function definition includes a formal argument of the same type as `x` :

```c
int function1(int num)
```

The second form requires the function definition to include a formal parameter that is a pointer to the right type:

```c
int function2(int * ptr)
```

Use the first form if the function needs a value for some calculation or action. Use the second form if the function needs to alter variables in the calling function. You have been doing this all along with the `scanf()` function. When you want to read in a value for a variable (`num`, for example), you use `scanf("%d", &num)`. That function reads a value and then uses the address you give it to store the value.

**Pointers** enable you to get around the fact that the variables of `interchange()` are local. They let that function reach out into `main()` and alter what is stored there.


## 2. Summary: Pointer-Related Operators

- The Address Operator: `&`
  - General Comments: When followed by a variable name, `&` gives the address of that variable.
  - Example: `&nurse` is the address of the variable `nurse`.
- The Indirection Operator: `*`
  - General Comments: When followed by a pointer name or an address, `*` gives the value stored at the pointed-to address.
  - Example:

```c
nurse = 22;
ptr = &nurse; // pointer to nurse
val = *ptr; // assigns value at location ptr to val
```

The net effect is to assign the value `22` to `val`.

