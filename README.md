Lab 5 Planning

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

We'll be:
- using the class #include <random>
- implementing game logic with loops, conditions, and state tracking
- using oop to ultimately have multiple source files and compile using a make file

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Game Rules:
- The program must generate a number between 1 and 100 randomly - done
- We'll be using seeds so we can debug and test without having to actually guess - done
- The player will have 10 tries to guess the random number - done
- The win condition is when the player guesses the correct number - done
- The win condition includes displaying a message to the player that they've won - done
- The loss condition is when the player uses all 10 tries without guessing the correct number. - done
- The loss condition includes what the win condition does, just with appropriate changes made - done
- Regardless of win or loss, ask the player if they'd like to play again - done
- If the guess is wrong, give a hint such as higher or lower to the player - done

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Gatchas:
- The player must press 0 if they want a hint. TODO
- The player will need to guess 2 times before receiving their first hint. - done
- The maximum amount of hints per game loop is 3 TODO
- I guess they can stack their hints if they'd like so let's print their available hints if they have any TODO
- We must have a few hint types and the type of hint must be random when a hint is used. Ex. (Is it even or odd, what's it a multiple of (prime numbers lol), etc.)

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Input Validation:
- Guesses outside the range of 1-100 or 0 are invalid and do not consume tries

Requirements:
- Must use OOP principles - done
- 2 methods other than main - done
- At least 1 class (has to be GuessingGame) - done
- For every function you write, include comments describing: BASICALLY DOCUMENT YOUR CODE

    Purpose: What does the function do?

    Preconditions: What must be true before calling it?

    Postconditions: What will be true after execution?

    Return Value (if applicable).

    - Example of a specification:

        // Purpose: Processes the player's guess and updates game state.
        // Precondition: guess is an integer >= 0.
        // Postcondition: If guess is correct, gameOver is set to true.
        //                If guess is incorrect, tries counter is updated.
        // Return: true if the game should continue, false if it ends.
        bool processGuess(int guess);

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

File Structure:
- GuessingGame.hpp
- GuessingGame.cpp
- main.cpp
- Makefile

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Example Makefile: You must add comments to your make file and own it
all: game
game: main.cpp GuessingGame.cpp
g++ main.cpp GuessingGame.cpp -o game
clean:
rm -f game

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Sample run:

    Welcome to the Number Guessing Game!
    I have chosen a number between 1 and 100.
    You have 10 tries to guess it.

    Enter your guess (1-100), or 0 for a hint:
    50
    Too high! Tries left: 9

    Enter your guess (1-100), or 0 for a hint:
    25
    Too low! Tries left: 8

    Enter your guess (1-100), or 0 for a hint:
    0
    Hint: The number is even.
    (Hint used: 1/3, Tries left: 6)

    Enter your guess (1-100), or 0 for a hint:
    42
    Correct! You win!

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

What to Submit:

You must submit a zipped project folder on Canvas containing:

    Source Code Files

        GuessingGame.hpp – class declaration with full specifications for each method.

        GuessingGame.cpp – class implementation with method bodies.

        main.cpp – driver program that runs the game.

    Makefile

        Must correctly compile the project with make.

        Must include a clean target.

    Documentation

        Specifications (purpose, preconditions, postconditions, return value) for every function.

        Meaningful inline comments, clear variable names, and proper indentation.

    Sample Output File 

        Copy and paste one run of your game into a text file called output.txt.

        This helps show that your program works correctly.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
