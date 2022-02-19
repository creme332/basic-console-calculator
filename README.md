# BasicCalculator
Simple console mode calculator that follows BODMAS/PEMDAS, deals with nested parentheses, negative numbers, unary operators, decimal numbers, and powers. Precision of calculation can be varied as well.

It uses the Shunting Yard Algorithm to convert the input infix expression to postfix notation and then evaluates it.

# Examples of valid input #

- `"112+22*(2*(22-53^2*(2))-7/(7/2-1/4))" = -246159.38462`
- `"2+-1" = 1`
- `"2^0.5" = 1.413`
- `"7^7^(2/(4-532)^3)" = 7.0`
- `"2(2)"`  (=`"2*(2)"`)


# Examples of invalid input #

- `"1---1"`
- `"2*"`
- `"7 ^ 7 ^ (2/(4-532)^3)"` (No spaces are allowed when inputting directly from console)


# Current limitations #
- Range of numbers is limited by `double` data type.
- No support for trigonometric and logarithmic expressions.
- No support for expressions containing irrational numbers (eg pi, e)
- Input is not validated so all invalid inputs will cause program to crash.
