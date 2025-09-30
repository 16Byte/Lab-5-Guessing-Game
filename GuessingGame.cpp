#include <iostream>
#include "GuessingGame.hpp"

using namespace std;

void GuessingGame::StartGame()
{

}

void GuessingGame::Log(const char* message, bool newLine)
{
    cout << message;
    if(newLine) cout << endl;
}

int GuessingGame::GetRandomNumber()
{
    return 0;
}