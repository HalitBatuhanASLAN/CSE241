# Problem Solution - Convert Decimal to Binary in C++

This solution implements a function, `ConvertToBinary`, that converts an unsigned integer into its binary representation and stores it in a string. The function uses basic division and modulus operations to generate the binary equivalent.

## Problem Description
The task is to write a function that:
1. Converts an unsigned integer to its binary form.
2. Stores the resulting binary number as a string.

## Solution Explanation
The solution involves dividing the number by 2 repeatedly and recording the remainder (either `0` or `1`) until the number is reduced to zero. These remainders are concatenated to form the binary string.
