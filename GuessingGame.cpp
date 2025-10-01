#include <iostream>
#include <random>
#include "GuessingGame.hpp"

using namespace std;

void GuessingGame::StartGame()
{
    int numberToGuess = GetRandomNumber(1, 100);
    int userGuess = 0;
    int numberOfTries = 0;

    cout << endl;
    Log("Welcome to the Guessing Game!");
    Log("I'm thinking of a number between 1 and 100.");
    Log("Can you guess what it is?");
    cout << endl;

    while(userGuess != numberToGuess && numberOfTries <= 10)
    {
        Log("Enter your guess: ", false);
        cin >> userGuess;
        numberOfTries++;
        
        cout << endl;
        Log("-------------------------------");
        cout << endl;

        if(userGuess == -1)
        {
            // User wants to set a seed
            Log("Please enter the seed you'd like to use: ", false);

            unsigned int seed;
            cin >> seed;

            numberToGuess = GetRandomNumber(1, 100, seed);
            numberOfTries = 0;

            Log("Seed set! Let's start over. ");
        }
        else if(userGuess == numberToGuess)
        {
            // Win condition
            Log("Congratulations! You've guessed the number " + to_string(numberToGuess) + " in " + to_string(numberOfTries) + " tries!");
        }
        else if(numberOfTries == 10)
        {
            // Lose condition
            Log("Sorry, you've used all your tries. The number was " + to_string(numberToGuess) + ".");
        }

        // Give a hint every 2 tries
        if(numberOfTries % 2 == 0 && userGuess != numberToGuess)
        {
            cout << BGCYAN << CYAN << "[HINT] " << RESET;
            GiveTheUserAHint(userGuess, numberToGuess);
        }

        Log(numberOfTries < 10 ? "You have " + to_string(10 - numberOfTries) + " tries left." : "No tries left. Game over.");

        //debugging
        Log(" (Debug: Number to guess is " + to_string(numberToGuess) + ")", false);
        Log(to_string(numberOfTries));
        cout << endl;
    }
}

void GuessingGame::Log(string message, bool newLine)
{
    cout << message;
    if(newLine) cout << endl;
}

void GuessingGame::GiveTheUserAHint(int userGuess, int numberToGuess)
{
    // TODO:
    // here we're going to choose a random number
    // in a switch statement we'll use that number to generate a hint for the player
    
    if(numberToGuess == (sqrt(userGuess)))
    {
        Log("The number you're looking for is the square root of your last guess.");
    }

    //temp
    else if(userGuess < numberToGuess)
    {
        Log("Too low! Try again.");
    }
    else if(userGuess > numberToGuess)
    {
        Log("Too high! Try again.");
    }
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