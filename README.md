# MasterMind-Console
Number guessing game in C++

[![demo](https://asciinema.org/a/588659.svg)](https://asciinema.org/a/588659)

It's a simple game. Goal is to guess a number. Length of number is received from the user, and number of guesses depends on the length.
If the length is less than 10, then number of user chances is equal to length. 
Otherwise, user have 9 chances to guess the number.

Main functionality of code is based on working with strings, so we included string library.
Prototype of main game functions added at the top of the code for better code readability.

Please note that game uses C++ 11, compilers using older standards fail to compile this code.
