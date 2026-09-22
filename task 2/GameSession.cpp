#include <iostream>
#include "GameSession.h"
#include <unistd.h>

bool GameSession::IsGameOver()
{
    return false;
}

void GameSession::StartGame()
{
    while (!IsGameOver())
    {
        production.Produce();
        sleep(3);
        production.Process();

        sleep(2);
        economy.SellResources();
        sleep(1);
        economy.AddMoney();

        sleep(1);
        upgrades.Upgrade();

        std::cout << "------------------\n";
    }
}
