#include <iostream>
#include <random>
#include "GuessingGame.hpp"

using namespace std;

void GuessingGame::StartGame()
{
    Log(to_string(GetRandomNumber(1, 100)));
}

void GuessingGame::Log(string message, bool newLine)
{
    cout << message;
    if(newLine) cout << endl;
}

int GuessingGame::GetRandomNumber(int min, int max)
{
    random_device rand;
    mt19937 gen(rand());
    uniform_int_distribution<> random(min, max);
    return random(gen);
}