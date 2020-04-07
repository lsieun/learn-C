# scanf

<!-- TOC -->

- [1. Intro](#1-intro)
- [2. Syntax](#2-syntax)
  - [2.1. ANSI C Conversion Specifiers for scanf()](#21-ansi-c-conversion-specifiers-for-scanf)
  - [2.2. Conversion Modifiers for scanf()](#22-conversion-modifiers-for-scanf)
- [3. The scanf() View of Input](#3-the-scanf-view-of-input)
- [4. Examples](#4-examples)
  - [4.1. float](#41-float)
  - [4.2. string](#42-string)

<!-- /TOC -->

## 1. Intro

The `scanf()` function provides keyboard input to the program.

The `scanf()` function uses **whitespace** (**newlines**, **tabs**, and **spaces**) to decide how to divide the input into separate fields.

The only exception to this is the `%c` specification, which reads the very next character, even if that character is **whitespace**.

The `scanf()` function uses pretty much the same set of **conversion-specification characters** as `printf()` does. The main difference is that `printf()` uses `%f`, `%e`, `%E`, `%g`, and `%G` for both type `float` and type `double`, whereas `scanf()` uses them just for type `float`, requiring the `l` modifier for `double`. 

## 2. Syntax

### 2.1. ANSI C Conversion Specifiers for scanf()

The main conversion specifiers in the C99 standard：

- `%c`： Interpret input as a character.
- `%d`： Interpret input as a signed decimal integer.
- `%e`, `%f`, `%g`, `%a`： Interpret input as a floating-point number(`%a` is C99).
- `%E`, `%F`, `%G`, `%A`： Interpret input as a floating-point number (`%A` is C99).
- `%i`： Interpret input as a signed decimal integer.
- `%o`： Interpret input as a signed octal integer.
- `%p`： Interpret input as a pointer (an address).
- `%s`： Interpret input as a string. Input begins with **the first non-whitespace character** and includes everything up to **the next whitespace character**.
- `%u`： Interpret input as an unsigned decimal integer.
- `%x`, `%X`： Interpret input as a signed hexadecimal integer.

### 2.2. Conversion Modifiers for scanf()

- `*`： Suppress assignment (see text). Example: `"%*d"`.
- `digit(s)`： **Maximum field width**. Input stops when the maximum field width is reached or when the first whitespace character is encountered, whichever comes first. Example: `"%10s"`.
- `hh`： Read an integer as a `signed char` or `unsigned char`. Examples: `"%hhd"`, `"%hhu"`.
- `ll`: Read an integer as a `long long` or `unsigned long long` (C99). Examples: `"%lld"`, `"%llu"`.
- `h`, `l`, or `L`: `"%hd"` and `"%hi"` indicate that the value will be stored in a `short int`. `"%ho"`, `"%hx"`, and `"%hu"` indicate that the value will be stored in an `unsigned short int`. `"%ld"` and `"%li"` indicate that the value will be stored in a `long`. `"%lo"`, `"%lx"`, and `"%lu"` indicate that the value will be stored in `unsigned long`. `"%le"`, `"%lf"`, and `"%lg"` indicate that the value will be stored in type `double`. Using `L` instead of `l` with `e`, `f`, and `g` indicates that the value will be stored in
type `long double`. In the absence of these modifiers, `d`, `i`, `o`, and `x` indicate type `int`, and `e`, `f`, and `g` indicate type `float`.
- `j`: When followed by an integer specifier, indicates using the `intmax_t` or `uintmax_t` type (C99). Examples: `"%jd"`, `"%ju"`.
- `z`: When followed by an integer specifier, indicates using the type returned by `sizeof` (C99). Examples: `"%zd"`, `"%zo"`.
- `t`: When followed by an integer specifier, indicates using the type used to represent the difference between two pointers (C99). Examples: `"%td"`, `"%tx"`.

## 3. The scanf() View of Input

Let’s look in more detail at how `scanf()` reads input.

> 笔记：这里是对`scanf()`的工作原理进行讲解

Suppose you use a `%d` specifier to read an integer. The `scanf()` function begins reading input a character at a time. It skips over **whitespace characters** (spaces, tabs, and newlines) until it finds a non-whitespace character. Because it is attempting to read an integer, `scanf()` expects to find **a digit character** or, perhaps, a sign (`+` or `-`). If it finds **a digit** or **a sign**, it saves that character and then reads the next character. If that is **a digit**, it saves the digit and reads the next character. `scanf()` continues reading and saving characters until it encounters **a nondigit**. It then concludes that it has reached the end of the integer. `scanf()` places the **nondigit** back into the **input**. This means that the next time the program goes to read **input**, it starts at the previously rejected, **nondigit character**. Finally, `scanf()` computes the **numerical value** corresponding to the **digits** (and possible **sign**) it read and places that value in the specified variable.

> 笔记：这里是以int做为示例进行讲解

If you use a **field width**, `scanf()` halts at the field end or at the first whitespace, whichever comes first.

> 笔记：这里讲解field width的作用，要么满足width要求，要么遇到whitespace。

What if the first non-whitespace character is, say, an `A` instead of a digit? Then `scanf()` stops right there and places the `A` (or whatever) back in the input. No value is assigned to the specified variable, and the next time the program reads input, it starts at the `A` again. If your program has only `%d` specifiers, `scanf()` will never get past that `A`. Also, if you use a `scanf()` statement with several specifiers, C requires the function to stop reading input at the first
failure.

> 笔记：这里讲解一种特殊情况，即“遇不到数字的情况”

Reading input using the **other numeric specifiers** works much the same as the `%d` case. The main difference is that `scanf()` may recognize more characters as being part of the number. For instance, the `%x` specifier requires that `scanf()` recognize the hexadecimal digits `a-f` and `A-F`. Floating-point specifiers require `scanf()` to recognize decimal points, e-notation, and the new p-notation.

> 笔记：这里讲解其他的numberic specifiers

If you use an `%s` specifier, any character other than **whitespace** is acceptable, so `scanf()` skips **whitespace** to the **first non-whitespace character** and then saves up **non-whitespace characters** until hitting **whitespace** again. This means that `%s` results in `scanf()` reading a single word — that is, a string with no whitespace in it. If you use a **field width**, `scanf()` stops at the end of the field or at the first whitespace, whichever comes first. You can’t use the field width to make `scanf()` read more than one word for one `%s` specifier. A final point: When `scanf()` places the string in the designated array, it adds the terminating `'\0'` to make the array contents a C string.

> 笔记：这里讲解string

If you use a `%c` specifier, all input characters are fair game. If the next input character is a **space** or a **newline**, a space or a newline is assigned to the indicated variable; whitespace is not skipped.

> 笔记：这里讲解char

Actually, `scanf()` is not the most commonly used input function in C. It is featured here because of its versatility (it can read all the different data types), but C has several other input functions, such as `getchar()` and `fgets()`, that are better suited for specific tasks, such as **reading single characters** or **reading strings containing spaces**.

> 笔记：除了`scanf()`之外，还存在其他的input functions。

## 4. Examples

### 4.1. float

```c
float weight;
/* get input from the user */
scanf("%f", &weight);
```

The `%f` instructs `scanf()` to read a floating-point number from the keyboard, and the `&weight` tells `scanf()` to assign the input value to the variable named `weight`. The `scanf()` function uses the `&` notation to indicate where it can find the `weight` variable.

### 4.2. string

```c
char name[40];
printf("Hi! What's your first name?\n");
scanf("%s", name);
```

- It uses **an array** to hold a character string . Here, someone’s name is read into the array, which is a series of 40 consecutive bytes in memory, each able to hold a single character value.
- It uses the `%s` conversion specification to handle the input and output of the string. Note that `name` does not use the `&` prefix when used with `scanf()`.

C uses **null character** to mark the end of a string. However, you do not have to put the **null character** into the `name` array yourself. That task is done for you by `scanf()` when it reads the input.

通过下面的代码，来学习一下在`scanf()`方法的过程中，需要注意一些事情：

```c
char name[40];
printf("What's your name? ");
scanf("%s", name);
printf("Hello, %s.\n", name);
```

```text
What's your name? Angela Plains
Hello, Angela.
```

Note (and this is important) that `scanf()` just reads **Angela Plains**’s first name. After `scanf()` starts to read input, **it stops reading at the first whitespace** (**blank**, **tab**, or **newline**) it encounters. Therefore, it stops scanning for name when it reaches **the blank** between **Angela** and **Plains**. In general, `scanf()` is used with `%s` to read only a single word, not a whole phrase, as a string. C has other input-reading functions, such as `fgets()`, for handling general strings.

> 笔记：`scanf()`在读取字符串的时候，如果遇到空白字符，就会停止读取。
