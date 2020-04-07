# Bitwise Shift Operators

## Left Shift: `<<`

The left shift operator (`<<`) shifts the bits of the value of the left operand to the left by the number of places given by the right operand. The vacated positions are filled with 0s, and bits moved past the end of the left operand are lost. In the following example, then, each bit is moved two places to the left:

```c
(10001010) << 2 // expression
(00101000)      // resulting value
```

## Right Shift: `>>`

The right-shift operator (`>>`) shifts the bits of the value of the left operand to the right by the number of places given by the right operand. Bits moved past the right end of the left operand are lost. For unsigned types, the places vacated at the left end are replaced by `0`s. For signed types, the result is machine dependent. The vacated places may be filled with 0s, or they may be filled with copies of the sign (leftmost) bit:

```c
(10001010) >> 2 // expression, signed value
(00100010)      // resulting value, some systems
(10001010) >> 2 // expression, signed value
(11100010)      // resulting value, other systems
```

For an unsigned value, you have the following:

```c
(10001010) >> 2 // expression, unsigned value
(00100010)      // resulting value, all system
```

