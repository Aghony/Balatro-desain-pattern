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
    // Tanpa argumen: pemain memilih kartu sendiri, 1 dek.
    //   --auto      : otomatis (5 kartu pertama), tanpa input
    //   --decks=N   : jumlah dek (2 = Five of a Kind mungkin, 3 = Flush House juga mungkin)
    bool interactive = true;
    int decks = 1;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--auto") == 0) {
            interactive = false;
        } else if (std::strncmp(argv[i], "--decks=", 8) == 0) {
            decks = std::atoi(argv[i] + 8);
        }
    }

    // Implementasi baru dari diagram Balatro, disuntikkan lewat interface Task 1.
    PokerInputGenerator inputGen(interactive, decks);     // menggantikan RandomInputGenerator
    PokerScoringRule scoringRule;     // menggantikan StandardScoringRule
    BlindRewardRule rewardRule;       // menggantikan BonusRewardRule
    ShopSystem shop;

    // Dependency Injection: RunSession tidak berubah sama sekali
    RunSession session(&inputGen, &scoringRule, &rewardRule, &shop);
    session.StartRun();

    return 0;
}
