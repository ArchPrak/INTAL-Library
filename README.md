# INTAL
An INTAL can be defined as a non-negative integer of arbitrary length, where each decimal digit is represented as a character. The entire number is 
represented as an array of characters (string),  with null termination. The most significant digit is at the head of the string.
For eg. the number 1543 would be represented as a string S with '1' at S[0], '5' at S[1], '4' at S[2] and null char at S[3].

This is an implementation of a C library for the integers of arbitrary length (intal).

### Difference from the Integer datatype in C
In C programming, int stands for integer, i.e., a non-decimal numeric value.
It is stored as 2 or 4 bytes. The corresponding ranges for the values that could be stored are -32,768 to 32,767 for 2 bytes and -2,147,483,648 to 2,147,483,648 for 4 bytes.
The fundamental difference lies in the definition of intals, they are non-negative integers, unlike the general integers which include negative numbers as well.
Also, in this implementation, the range of intals has been resctricted by fixing the maximum number of digits in an INTAL as 1000. This allows us to represent numbers in the range (0,10^1000).This increased range allows us to work with much larger numbers that otherwise would be too large to store in a variable of the Integer datatype.

### Applications
INTAL opertions can be used for faster computations of large numbers, which is not currently available directly in C.
Operations on large numbers could be useful in fields like Biotechnology for Gene Sequence Representation with operations like 
intersection, union etc. and in the field of Number Theory.

# Functions
<ul>
<li>  Mathematical Operations
  <ol>
    <li>Intal Addition</li>
    <li>Intal Subtraction</li>
    <li>Intal Comparison</li>
    <li>Intal Multiplication</li>
    <li>Modulo Operation</li>
    <li>Power Function</li>
    <li>Greatest Common Divisor</li>
    <li>nth Fibonacci</li>
    <li>Binomial Coefficient</li>
    <li>Factorial</li>
  </ol>
</li>

<li> Array of INTALs
  <ol>
    <li>Maximum/Minimum INTAL </li>
    <li>Binary Search</li>
    <li>Sorting</li>
    <li>Dynamic Programming solution for the Coin-Row Problem:<br> There is a row of n coins whose values are some positive integers C[0..n-1].
The goal is to pick up the maximum amount of money subject to the constraint that
 no two coins adjacent in the initial row can be picked up </li>
    
  </ol>
</li>
  
