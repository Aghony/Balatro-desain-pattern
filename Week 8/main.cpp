#include <cstdlib>
#include <cstring>
#include <iostream>
#include "InputGenerator.h"
#include "ScoringRule.h"
#include "RewardRule.h"
#include "ShopSystem.h"
#include "RunSession.h"
#include "PokerAdapters.h"

int main(int argc, char** argv) {
    bool interactive = true;
    int decks = 1;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--auto") == 0) {
            interactive = false;
        } else if (std::strncmp(argv[i], "--decks=", 8) == 0) {
            decks = std::atoi(argv[i] + 8);
        }
    }

    PokerInputGenerator inputGen(interactive, decks);
    PokerScoringRule scoringRule;
    BlindRewardRule rewardRule;
    ShopSystem shop;

    RunSession session(&inputGen, &scoringRule, &rewardRule, &shop);
    session.StartRun();

    return 0;
}