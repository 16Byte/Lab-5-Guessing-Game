#include <iostream>

using namespace std;

class GuessingGame
{
    public:
        void StartGame();
        void Log(string message, bool newLine = true);

    private:
        int GetRandomNumber(int min, int max);
};