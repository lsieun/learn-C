# define

<!-- TOC -->

- [1. Syntax](#1-syntax)
- [2. Examples](#2-examples)
  - [2.1. character and string constants](#21-character-and-string-constants)
- [3. Common Error](#3-common-error)

<!-- /TOC -->

## 1. Syntax

The preprocessor lets you define constants. Just add a line like the following at the top of the file containing your program:

```c
#define TAXRATE 0.015
```

When your program is compiled, the value `0.015` will be substituted everywhere you have used `TAXRATE`. This is called a **compile-time substitution**. By the time you run the program, all the substitutions have already been made. Such defined constants are often termed **manifest constants**.

Note the format. First comes `#define`. Next comes **the symbolic name** (`TAXRATE`) for the constant and then **the value** (`0.015`) for the constant. (Note that this construction does not use the `=` sign.) So the general form is as follows:

```c
#define NAME value
```

You would substitute the symbolic name of your choice for `NAME` and the appropriate value for `value`. No **semicolon** is used because this is a substitution mechanism handled by the preprocessor, not a C statement. Why is `TAXRATE` capitalized? **It is a sensible C tradition to type constants in uppercase**. Then, when you encounter one in the depths of a program, you know immediately that it is a constant, not a variable. Capitalizing constants is just another technique to make programs more readable. Your programs will still work if you don’t capitalize the constants, but capitalizing them is a reasonable habit to cultivate.

Other, less common, naming conventions include prefixing a name with a `c_` or `k_` to indicate **a constant**, producing names such as `c_level` or `k_line`.

## 2. Examples

### 2.1. character and string constants

The `#define` statement can be used for **character** and **string constants**, too. Just use single quotes for the former and double quotes for the latter. The following examples are valid:

```c
#define BEEP '\a'
#define TEE 'T'
#define ESC '\033'
#define OOPS "Now you have done it!"
```

## 3. Common Error

Remember that everything following the **symbolic name** is substituted for it. Don’t make this common error:

```c
/* the following is wrong */
#define TOES = 20
```

If you do this, `TOES` is replaced by `= 20`, not just `20`. In that case, a statement such as

```c
digits = fingers + TOES;
```

is converted to the following misrepresentation:

```c
digits = fingers + = 20;
```
