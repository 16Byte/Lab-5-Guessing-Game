#include <iostream>
#include "GuessingGame.hpp"

using namespace std;

void IntroduceTheGame(GuessingGame& game);

int main()
{
    // This program will only run on Ubuntu/Linux and MacOS terminals due to the use of terminal color codes.
    // Windows users can use WSL (Windows Subsystem for Linux) to run this program

    GuessingGame game;

    IntroduceTheGame(game);

    game.StartGame();
    game.HandleGameLoop();
        
    // End of program
    return 0;
}

void IntroduceTheGame(GuessingGame& game)
{
    std::cout << endl;
        game.Log("Welcome to the Guessing Game!");
        game.Log("I'm thinking of a number between 1 and 100.");
        game.Log("Can you guess what it is?");
    std::cout << endl;
        game.Log("You have " + to_string(game.MAX_TRIES) + " tries to guess the number.");
        game.Log("You can enter 0 to use a hint if you have any available.");
        game.Log("Good luck!");
    std::cout << endl;
}