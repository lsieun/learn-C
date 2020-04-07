# Type char

The `char` type is used for storing characters such as letters and punctuation marks, but technically it is an integer type. Why? Because the `char` type actually stores integers, not characters. To handle characters, the computer uses a numerical code in which certain integers represent certain characters. The most commonly used code in the U.S. is the **ASCII code**. In it, for example, the integer value `65` represents an uppercase `A`. So to store the letter `A`, you actually need to store the integer `65`. (Many IBM mainframes use a different code, called EBCDIC, but the principle is the same. Computer systems outside the U.S. may use entirely different codes.)

The standard ASCII code runs numerically from `0` to `127`. This range is small enough that `7` bits can hold it. The `char` type is typically defined as an 8-bit unit of memory, so it is more than large enough to encompass the **standard ASCII code**. Many systems, such as the IBM PC and the Apple Macs, offer **extended ASCII codes** (different for the two systems) that still stay within an 8-bit limit. More generally, C guarantees that the `char` type is large enough to store the basic character set for the system on which C is implemented.

**Many character sets have many more than `127` or even `255` values**. For example, there is the Japanese kanji character set. The commercial Unicode initiative has created a system to represent a variety of characters sets worldwide and currently has over 110,000 characters. The International Organization for Standardization (ISO) and the International Electrotechnical Commission (IEC) have developed a standard called ISO/IEC 10646 for character sets. Fortunately, **the Unicode standard** has been kept compatible with the more extensive ISO/IEC 10646 standard.

The C language defines **a byte** to be the number of bits used by type `char`, so one can have a system with a 16-bit or 32-bit byte and char type.

## Signed or Unsigned?

Some C implementations make `char` a signed type. This means a `char` can hold values typically in the range `-128` through `127`. Other implementations make `char` an unsigned type, which provides a range of `0` through `255`. Your compiler manual should tell you which type your char is, or you can check the `limits.h header` file.

As of C90, C enabled you to use the keywords `signed` and `unsigned` with `char`. Then, regardless of what your default `char` is, `signed char` would be signed, and `unsigned char` would be unsigned. These versions of `char` are useful if you’re using the type to handle small integers. For **character use**, just use the standard `char` type without modifiers.
