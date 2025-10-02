#include <iostream>
#include <random>
#include "GuessingGame.hpp"

using namespace std;

void GuessingGame::StartGame()
{
    int numberToGuess = GetRandomNumber(1, 100);
    int userGuess = 0;
    int numberOfTries = 0;
    const int MAX_TRIES = 10;

    cout << endl;
    Log("Welcome to the Guessing Game!");
    Log("I'm thinking of a number between 1 and 100.");
    Log("Can you guess what it is?");
    cout << endl;

    while(userGuess != numberToGuess && numberOfTries <= MAX_TRIES)
    {
        CheckWinCondition(userGuess, numberToGuess, numberOfTries);

        Log("You have " + to_string(MAX_TRIES - numberOfTries) + "\\" + to_string(MAX_TRIES) + " tries left.");
        Log("Enter your guess: ", false);
        cin >> userGuess;
        numberOfTries++;

        LogSeparator();

        //debugging
        Log(" (Debug: Number to guess is " + to_string(numberToGuess) + ")");

        if(userGuess == -1) // Dev backend
        {
            // User wants to set a seed
            Log("Please enter the seed you'd like to use: ", false);

            unsigned int seed;
            cin >> seed;

            numberToGuess = GetRandomNumber(1, 100, seed);
            numberOfTries = 0;

            Log("Seed set! Let's start over. ");
        }
        
        if(numberOfTries % 2 == 0 && userGuess != numberToGuess) // Give a hint every 2 tries
            GiveTheUserAHint(userGuess, numberToGuess);

        
    }
    //end of program
}

void GuessingGame::Log(string message, bool newLine)
{
    cout << message;
    if(newLine) cout << endl;
}

void GuessingGame::LogSeparator()
{
    cout << endl;
    Log("-------------------------------");
    cout << endl;
}

void GuessingGame::CheckWinCondition(int userGuess, int numberToGuess, int numberOfTries)
{
    if(numberOfTries <= 0) return;

    if(userGuess == numberToGuess)
    {
        // Win condition
        Log("Congratulations! You've guessed the number " + to_string(numberToGuess) + " in " + to_string(numberOfTries) + " tries!");
        return;
    }
    else if(numberOfTries > 10 && userGuess != numberToGuess)
    {
        // Lose condition
        Log("Sorry, you've used all your tries. The number was " + to_string(numberToGuess) + ".");

        Log("Would you like to play again? y/N");

        string playAgainChoice = "";
        cin >> playAgainChoice;

        if(playAgainChoice.empty() || (playAgainChoice == "n" || playAgainChoice == "N"))
        {
            Log("Thanks for playing!");
            return;
        }
        else if(playAgainChoice == "y" || playAgainChoice == "Y")
        {
            StartGame();
        }
    }

    if(userGuess < numberToGuess)
    {
        Log("Too low! Try again.");
    }
    else if(userGuess > numberToGuess)
    {
        Log("Too high! Try again.");
    }
}

void GuessingGame::GiveTheUserAHint(int userGuess, int numberToGuess)
{
    // TODO:
    // KISS.

    cout << BGCYAN << "[HINT] ";
    
    if(numberToGuess == (sqrt(userGuess)))
        Log("The number you're looking for is the square root of your last guess.");

    cout << RESET;
}

int GuessingGame::GetRandomNumber(int min, int max, unsigned int seed)
{
    random_device rand;
    uniform_int_distribution<> random(min, max);

    if(seed == 0)
    {
        // Use a random seed
        mt19937 gen(rand());
        return random(gen);
    }
    else
    {
        // Use the provided seed
        mt19937 gen(seed);
        return random(gen);
    }
    return -404; // Error -- seed not found
}