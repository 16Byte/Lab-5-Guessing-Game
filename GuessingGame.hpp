class GuessingGame
{
    public:
        void StartGame();
        void Log(const char* message, bool newLine = true);

    private:
        int GetRandomNumber();
};