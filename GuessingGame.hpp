#include <iostream>

using namespace std;

class GuessingGame
{
    //the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
    #define RESET   "\033[0m"
    #define BLACK   "\033[30m"      /* Black */
    #define RED     "\033[31m"      /* Red */
    #define GREEN   "\033[32m"      /* Green */
    #define YELLOW  "\033[33m"      /* Yellow */
    #define BLUE    "\033[34m"      /* Blue */
    #define MAGENTA "\033[35m"      /* Magenta */
    #define CYAN    "\033[36m"      /* Cyan */
    #define WHITE   "\033[37m"      /* White */
    #define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
    #define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
    #define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
    #define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
    #define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
    #define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
    #define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
    #define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

    // Background color codes (Ubuntu/Linux, macOS only)
    #define BGBLACK   "\033[40m"      /* Black background */
    #define BGRED     "\033[41m"      /* Red background */
    #define BGGREEN   "\033[42m"      /* Green background */
    #define BGYELLOW  "\033[43m"      /* Yellow background */
    #define BGBLUE    "\033[44m"      /* Blue background */
    #define BGMAGENTA "\033[45m"      /* Magenta background */
    #define BGCYAN    "\033[46m"      /* Cyan background */
    #define BGWHITE   "\033[47m"      /* White background */

    public:
        void StartGame();
        void HandleGameLoop();
        void Log(string message, bool newLine = true, const char* color = RESET);
        void LogSeparator();

        const static int MAX_TRIES = 10;

    private:
        int GetUserInput();
        int GetRandomNumber(int min, int max, unsigned int seed = 0);
        void GiveTheUserAHint(int userGuess, int numberToGuess);
        bool CheckWinLossCondition(int userGuess, int numberToGuess, int numberOfTries);
        void AskTheUserIfTheyWantToPlayAgain();

        int numberToGuess;
        int userGuess;
        int userGuessCached;
        int numberOfTries;
        int numberOfHintsGiven;
        int numberOfHintsUsed;
        
        const static int MAX_HINTS = 3;
};