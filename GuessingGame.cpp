#include <iostream>
#include <random>
#include "GuessingGame.hpp"

using namespace std;

void GuessingGame::StartGame()
{
    //Log(to_string(GetRandomNumber(1, 100, 542)));

    Log("Welcome to the Guessing Game!");
    Log("I'm thinking of a number between 1 and 100.");
    Log("Can you guess what it is?");
    int numberToGuess = GetRandomNumber(1, 100);
    int userGuess = 0;
    int numberOfTries = 0;

    while(userGuess != numberToGuess)
    {
        Log("Enter your guess: ", false);
        cin >> userGuess;
        numberOfTries++;

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
        else if(userGuess != numberToGuess)
        {
            // Wrong guess
            GiveTheUserAHint(userGuess, numberToGuess);
        }
        else if(userGuess == numberToGuess)
        {
            // Win condition
            Log("Congratulations! You've guessed the number " + to_string(numberToGuess) + " in " + to_string(numberOfTries) + " tries!");
        }
    }
}

void GuessingGame::Log(string message, bool newLine)
{
    cout << message;
    if(newLine) cout << endl;
}

void GuessingGame::GiveTheUserAHint(int userGuess, int numberToGuess)
{
    if(userGuess < numberToGuess)
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

    if(seed == 0)
    {
        // Use a random seed
        mt19937 gen(rand());
        uniform_int_distribution<> random(min, max);
        return random(gen);
    }
    else
    {
        // Use the provided seed
        mt19937 gen(seed);
        uniform_int_distribution<> random(min, max);
        return random(gen);
    }
    return -404; // Error -- seed not found
}