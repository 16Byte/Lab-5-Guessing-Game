#include <iostream>
#include <random>
#include "GuessingGame.hpp"

using namespace std;

void GuessingGame::StartGame()
{
    numberToGuess = GetRandomNumber(1, 100);
    userGuess = 0;
    numberOfTries = 0;
    numberOfHintsGiven = 0;
    numberOfHintsUsed = 0;

    //debugging
    Log(" (Debug: Number to guess is " + to_string(numberToGuess) + ")", true, BGGREEN);

    cout << endl;
    Log("Welcome to the Guessing Game!");
    Log("I'm thinking of a number between 1 and 100.");
    Log("Can you guess what it is?");
    cout << endl;

    while(userGuess != numberToGuess && numberOfTries <= MAX_TRIES)
    {
        Log("Enter your guess: ", false);

        cin >> userGuess;

        if(numberOfHintsGiven - numberOfHintsUsed > 0 && userGuess == 0) // User asked for a hint
        {
            GiveTheUserAHint(userGuess, numberToGuess);
        }
        else
            numberOfTries++;

        LogSeparator();
        Log("You have " + to_string(MAX_TRIES - (numberOfTries - 1)) + "\\" + to_string(MAX_TRIES) + " tries left.", true, BGMAGENTA);
        

        if(numberOfTries % 2 == 0 && userGuessCached != 0 && userGuess != numberToGuess && numberOfHintsGiven < MAX_HINTS && numberOfTries <= MAX_TRIES)
            numberOfHintsGiven++; // Give a hint every 2 tries, if there are hints left to give

        CheckWinCondition(userGuess, numberToGuess, numberOfTries);

        if(userGuess == -1) // Dev backend
        {
            // User wants to set a seed
            Log("Please enter the seed you'd like to use: ", false);

            unsigned int seed;
            cin >> seed;

            numberToGuess = GetRandomNumber(1, 100, seed);
            numberOfTries = 0;

            Log("Seed set! Let's start over.", true, BGGREEN);
        }
        userGuessCached = userGuess;
        
        Log("You have " + to_string(numberOfHintsGiven - numberOfHintsUsed) + "\\" + to_string(MAX_HINTS) + " hints available.", true, BGCYAN);
    }
    //end of program
}

void GuessingGame::CheckWinCondition(int userGuess, int numberToGuess, int numberOfTries)
{
    if(numberOfTries <= 0) return;

    if(userGuess == numberToGuess)
    {
        // Win condition
        Log("Congratulations! You've guessed the number " + to_string(numberToGuess) + " in " + to_string(numberOfTries) + " tries!", true, BGGREEN);
        AskTheUserIfTheyWantToPlayAgain();
        return;
    }
    else if(numberOfTries > 10 && userGuess != numberToGuess)
    {
        // Lose condition
        Log("Sorry, you've used all your tries. The number was " + to_string(numberToGuess) + ".", true, BGRED);

        AskTheUserIfTheyWantToPlayAgain();
        return;   
    }

    if(userGuess < numberToGuess)
    {
        Log("Too low! Try again.", true, BGCYAN);
    }
    else if(userGuess > numberToGuess)
    {
        Log("Too high! Try again.", true, BGCYAN);
    }
}

void GuessingGame::GiveTheUserAHint(int userGuess, int numberToGuess)
{
    // TODO:
    // KISS.

    if(numberOfHintsUsed >= MAX_HINTS) return;

    Log("[HINT] ", false, BGCYAN);

    if(numberOfHintsUsed == 1) // First hint: is it odd or even?
    {
        if(numberToGuess % 2 == 0)
            Log("The number you're looking for is even.", true, BGCYAN);
        else
            Log("The number you're looking for is odd.", true, BGCYAN);
    }
    
    else if(numberOfHintsUsed == 2) // Second hint: is it divisible by 3, 5, or 7?
    {
        if(numberToGuess % 3 == 0)
            Log("The number you're looking for is divisible by 3.", true, BGCYAN);
        else if(numberToGuess % 5 == 0)
            Log("The number you're looking for is divisible by 5.", true, BGCYAN);
        else if(numberToGuess % 7 == 0)
            Log("The number you're looking for is divisible by 7.", true, BGCYAN);
        else
            Log("The number you're looking for is not divisible by 3, 5, or 7.", true, BGCYAN);
    }
    else if(numberOfHintsUsed == 3) // Third hint: is it a square of a number?
    {
        for(int i = 1; i <= 10; i++)
        {
            if(i * i == numberToGuess)
            {
                Log("The number you're looking for is a perfect square: " + to_string(i) + " * " + to_string(i) + " = " + to_string(numberToGuess), true, BGCYAN);
                numberOfHintsUsed++;
                return;
            }
        }
        Log("The number you're looking for is not a perfect square.", true, BGCYAN);
    }

    cout << RESET;

    numberOfHintsUsed++;
}

void GuessingGame::AskTheUserIfTheyWantToPlayAgain()
{
    Log("Would you like to play again? Y/N");

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
        else
        {
            Log("Invalid input. Please enter Y or N.");
            AskTheUserIfTheyWantToPlayAgain();
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

void GuessingGame::Log(string message, bool newLine, const char* color)
{
    cout << color << message << RESET;
    if(newLine) cout << endl;
}

void GuessingGame::LogSeparator()
{
    cout << endl;
    Log("-------------------------------");
    cout << endl;
}