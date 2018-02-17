# Sort Algorithm with Graphic Output

## Description

This programm is a personnal projetc that displays different sort algorithms (Bubble, Insertion, Cocktail Shaker, Merge) in the Unix terminal. 

## Requirements 

I run this program with Ubuntu, in the terminal. It contains system calls like `system("clear")`. You need to modifiy these calls if you want to run it on a different operating system.
The program displays a graph that is 200 column large and 55 lines high. If your screen is to small to display a graph that big, change thoses values in the source code, they are declared as constant.
The program also displays colors in the terminal with lines like this one `printf("\033[7m \033[0m");`. If your terminal does not support this type of encoding, you can replace the colors with charaters by changing the value of the constant `DISPLAY_COLOR` to 0 in the source code.

## License and Maintainers

This software is a free software that is under the MIT license and is 
maintained by CHARLOT Servan. Any questions or suggestions send him an 
email: <charlot.servan@gmail.com>