#pragma once

#include "ProductionSystem.h"
#include "EconomySystem.h"
#include "UpgradeSystem.h"

class GameSession
{
private:
    ProductionSystem production;
    EconomySystem economy;
    UpgradeSystem upgrades;

    bool IsGameOver();

public:
    void StartGame();
};