#include <iostream>
#include <random>
#include <sstream>
#include <ctime>
#include "GuessingGame.hpp"

using namespace std;

// Purpose: Starts the game by initializing the number to guess and resetting other game variables.
// Precondition: The game is not currently running.
// Postcondition: The game state is initialized, and the number to guess is set.
// Returns: void
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

// Purpose: Handles The main game loop where the user guesses the number.
// Precondition : The game has been started and the number to guess is set.
// Postcondition: The user has either guessed the number, used all tries, or opted to
//                play again. The game state is reset if the user chooses to play again.
// Returns: void
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

// Purpose: Checks if the user has won or lost the game based on their guess and the number of tries.
// Precondition: The user has made a guess and the number of tries is known.
// Postcondition: If the user has won or lost, a message is displayed and the user is prompted to play again.
// Returns: true if the game is over (win/loss), false otherwise.
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

// Purpose: Gives the user a hint based on their guess and the number to guess.
// Precondition: The user has requested a hint and there are hints available.
// Postcondition: A hint is provided to the user based on the number to guess.
// Returns: void
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

// Purpose: Asks the user if they want to play again after a game ends.
// Precondition: The game has ended (win/loss).
// Postcondition: If the user chooses to play again, the game state is reset and a new game starts.
// Returns: void
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

// Purpose: Gets user input and validates it.
// Precondition: The user is prompted to enter a guess or a hint request.
// Postcondition: The user input is validated and returned as an integer.
// Returns: The validated user input as an integer (0 for hint, 1-100 for guess).
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

// Purpose: Generates a random number between min and max, optionally using a seed.
// Precondition: The min and max values are valid, and an optional seed can be provided.
// Postcondition: A random number is generated based on the provided parameters.
// Returns: A random number between min and max, or -404 if an error occurs.
// Note: If seed is 0, a random seed is used; otherwise, the provided seed is used.
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

// Purpose: Logs a message to the console with optional color and newline.
 // Precondition: The message to log is provided, and optional parameters for new line and color can be set.
 // Postcondition: The message is printed to the console with the specified formatting.
 // Returns: void
void GuessingGame::Log(string message, bool newLine, const char* color)
{
    std::cout << color << message << RESET;
    if(newLine) std::cout << endl;
}

// Purpose: Logs a separator line to the console for better readability.
 // Precondition: None
 // Postcondition: A separator line is printed to the console.
 // Returns: void
void GuessingGame::LogSeparator()
{
    std::cout << endl;
    Log("-------------------------------");
    std::cout << endl;
}