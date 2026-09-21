#include <iostream>
#include <cstdlib>
#include <ctime>

#include "InputGenerator.h"
#include "ScoringRule.h"
#include "RewardRule.h"
#include "ShopSystem.h"
#include "RunSession.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Modifikasi 1: Menggunakan RandomInputGenerator tanpa mengubah RunSession
    RandomInputGenerator inputGen;
    StandardScoringRule scoringRule;
    
    // Modifikasi 2: Menggunakan BonusRewardRule tanpa mengubah RunSession
    BonusRewardRule rewardRule;
    
    ShopSystem shop;

    // Dependency Injection
    RunSession session(&inputGen, &scoringRule, &rewardRule, &shop);
    session.StartRun();

    return 0;
}