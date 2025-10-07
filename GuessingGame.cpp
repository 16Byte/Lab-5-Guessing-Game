#include <iostream>
#include <random>
#include <sstream>
#include <ctime>
#include "GuessingGame.hpp"

using namespace std;

void GuessingGame::StartGame()
{
    numberToGuess = GetRandomNumber(1, 100);
    userGuess = 0;
    numberOfTries = 0;
    numberOfHintsGiven = 0;
    numberOfHintsUsed = 0;
    bool debugging = false;

    //debugging
    if(debugging)
    {
        Log(" (Debug: Number to guess is " + to_string(numberToGuess) + ")", true, BGGREEN);
        LogSeparator();
    }
}

void GuessingGame::HandleGameLoop()
{
    while(userGuess != numberToGuess && numberOfTries <= MAX_TRIES)
    {
        Log("Enter your guess: ", false);
        userGuess = GetUserInput();

        if(userGuess == 0) // User wants to use a hint
        {
            if(numberOfHintsGiven - numberOfHintsUsed > 0)
                GiveTheUserAHint(userGuess, numberToGuess);
            else
                Log("No hints available!", true, BGRED);
        }
        else if(userGuess == -1) // Dev backend
        {
            // User wants to set a seed
            Log("Please enter the seed you'd like to use: ", false);

            unsigned int seed;
            cin >> seed;

            numberToGuess = GetRandomNumber(1, 100, seed);
            numberOfTries = 0;

            Log("Seed set! Let's start over.", true, BGGREEN);
        }
        else
        {
            numberOfTries++;

            // Give the player a new hint every 2 guesses, so long as they haven't surpassed MAX_HINTS
            if((numberOfTries % 2 == 0 && userGuess != numberToGuess) && numberOfHintsGiven < MAX_HINTS)
                numberOfHintsGiven++;

            if(CheckWinLossCondition(userGuess, numberToGuess, numberOfTries))
                return;
        }
        userGuessCached = userGuess;

        LogSeparator();
        Log("You have " + to_string(MAX_TRIES - numberOfTries) + "\\" + to_string(MAX_TRIES) + " tries left.", true, BGMAGENTA);
        
        int availableHints = numberOfHintsGiven - numberOfHintsUsed;
        if (availableHints < 0) availableHints = 0;
        if (availableHints > MAX_HINTS) availableHints = MAX_HINTS;
        Log("You have " + to_string(availableHints) + "\\" + to_string(MAX_HINTS) + " hints available.", true, BGCYAN);
    }
}

bool GuessingGame::CheckWinLossCondition(int userGuess, int numberToGuess, int numberOfTries)
{
    if(numberOfTries <= 0) return false; //don't print anything if no tries have been made yet

    if(userGuess == numberToGuess)
    {
        // Win condition
        Log("Congratulations! You've guessed the number " + to_string(numberToGuess) + " in " + to_string(numberOfTries) + " tries!", true, BGGREEN);
        AskTheUserIfTheyWantToPlayAgain();
        return true;
    }
    else if(numberOfTries > MAX_TRIES && userGuess != numberToGuess)
    {
        // Loss condition
        Log("Sorry, you've used all your tries. The number was " + to_string(numberToGuess) + ".", true, BGRED);

        AskTheUserIfTheyWantToPlayAgain();
        return true;   
    }

    // Provide feedback so they're not guessing blindly
    if(userGuess < numberToGuess)
        Log("Too low! Try again.", true, BGCYAN);
    else if(userGuess > numberToGuess)
        Log("Too high! Try again.", true, BGCYAN);

    return false;
}

void GuessingGame::GiveTheUserAHint(int userGuess, int numberToGuess)
{
    if(numberOfHintsGiven == 0) {
        Log("No hints available!", true, BGRED);
        return;
    }

    Log("[HINT] ", false, BGCYAN);

    // Get a random hint type
    mt19937 gen(static_cast<unsigned int>(time(0) + numberOfHintsUsed));
    uniform_int_distribution<> dist(0, 2);
    int hintType = dist(gen);

    if(hintType == 0) {
        if(numberToGuess % 2 == 0)
            Log("The number you're looking for is even.", true, BGCYAN);
        else
            Log("The number you're looking for is odd.", true, BGCYAN);
    }
    else if(hintType == 1) {
        if(numberToGuess % 3 == 0)
            Log("The number you're looking for is divisible by 3.", true, BGCYAN);
        else if(numberToGuess % 5 == 0)
            Log("The number you're looking for is divisible by 5.", true, BGCYAN);
        else if(numberToGuess % 7 == 0)
            Log("The number you're looking for is divisible by 7.", true, BGCYAN);
        else
            Log("The number you're looking for is not divisible by 3, 5, or 7.", true, BGCYAN);
    }
    else {
        bool isPrime = true;
        for(int i = 2; i <= numberToGuess / 2; i++) {
            if(numberToGuess % i == 0) {
                isPrime = false;
                break;
            }
        }
        Log(isPrime ? 
            "The number you're looking for is a prime number." : 
            "The number you're looking for is not a prime number.", true, BGCYAN);
    }
    numberOfHintsUsed++;
}

void GuessingGame::AskTheUserIfTheyWantToPlayAgain()
{
    Log("Would you like to play again? y/N");

    string playAgainChoice = "";

    if(!getline(cin, playAgainChoice) || playAgainChoice.empty() || (playAgainChoice == "n" || playAgainChoice == "N"))
    {
        Log("Thanks for playing!");
        return;
    }
    else if(playAgainChoice == "y" || playAgainChoice == "Y")
    {
        StartGame();
        HandleGameLoop();
        return;
    }
    else
    {
        Log("Invalid input. Please enter Y or N.");
        AskTheUserIfTheyWantToPlayAgain();
    }
}

int GuessingGame::GetUserInput()
{
    int input;
    string line;
    
    while (true) {
        // Check if input has a value
        if (!getline(cin, line) || line.empty()) {
            cerr << "Error: No input provided. Please enter a number: ";
            continue;
        }
        
        // Try to convert the string to a number
        istringstream iss(line);
        if (iss >> input && iss.eof()) {
            // Check if input is valid (0 for hint or 1-100 for guess)
            if (input == 0 || (input >= 1 && input <= 100)) {
                return input;
            }
            cerr << "Error: Please enter a number between 1 and 100 (or 0 for a hint): ";
            continue;
        }
        
        cerr << "Error: That was not a number. Please enter a number: ";
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
    std::cout << color << message << RESET;
    if(newLine) std::cout << endl;
}

void GuessingGame::LogSeparator()
{
    std::cout << endl;
    Log("-------------------------------");
    std::cout << endl;
}