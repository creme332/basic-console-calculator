# 💻 Basic Calculator
![image](https://user-images.githubusercontent.com/65414576/154796235-27b9efe5-34d6-43ac-a74f-bfc8459e16f8.png)

Calculator application that uses the [Shunting Yard Algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm) to convert an input infix expression to postfix expression before evaluating it.

## 👍 Examples of valid expressions ##
```cpp
112+22*(2*(22-53^2*(2))-7/(7/2-1/4)) //-246159.38462

2+-1 // 1

2^0.5 // 1.413

7^7^(2/(4-532)^3) // 7^(7^(2/(4-532)^3)) = 7.0

2(2)  // same as 2*2
```
## 👎 Examples of invalid expressions ##
```cpp
1---1 //not supported yet
2* //incomplete expression
7 ^ 7 ^ (2/(4-532)^3) //(No spaces between digits/operators are allowed when inputting directly from console)
```

# 🛑 Current limitations #
- Range of numbers is limited by `double` data type.
- No support for trigonometric and logarithmic expressions.
- No support for expressions containing irrational numbers (eg pi, e)
- Input is not validated so all invalid inputs will cause program to crash.
