# C++ Number Guessing Game

A polished implementation of a number guessing game featuring a smart hint system, color-coded output, and debug features.

## Features

- 🎲 Random number generation between 1-100
- 🎯 Limited tries with configurable maximum
- 💡 Progressive hint system with multiple hint types:
  - Even/Odd properties
  - Divisibility hints
  - Prime number detection
- 🎨 Color-coded terminal output for better UX
- 🔄 Play again functionality
- 🐛 Debug mode for testing

## Game Rules

- Guess a number between 1 and 100
- Default: 10 tries to guess correctly
- Earn hints after every 2 guesses
- Use hints by entering '0'
- Maximum of 3 hints per game (configurable)

## Customization

### Debug Mode
To see the answer for testing:
```cpp
// In GuessingGame::StartGame()
// Set the debugging bool to true

bool debugging = false;

//debugging
if(debugging)
{
    Log(" (Debug: Number to guess is " + to_string(numberToGuess) + ")", true, BGGREEN);
    LogSeparator();
}
```

### Game Parameters
In `GuessingGame.hpp`:
```cpp
// Modify these constants to adjust game difficulty
const int MAX_TRIES = 10;  // Number of allowed guesses
const int MAX_HINTS = 3;   // Maximum hints per game
```

## Technical Features

- Object-Oriented Design
- Input validation
- ANSI color formatting
- Random seed support for testing
- Clean code architecture
- Error handling

## Project Structure

```
├── GuessingGame.hpp  # Class declaration and constants
├── GuessingGame.cpp  # Game logic implementation
├── main.cpp         # Driver program
└── Makefile        # Build configuration
```

## Color Coding

- 🟦 Cyan: Hints and general gameplay
- 🟩 Green: Success messages and debug info
- 🟥 Red: Errors and invalid inputs
- 🟪 Magenta: Progress tracking
