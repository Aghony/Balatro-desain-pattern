#include "RunSession.h"
#include <iostream>

RunSession::RunSession(IInputGenerator* inputGen, IScoringRule* scoring, IRewardRule* reward, ShopSystem* shop)
    : inputGenerator(inputGen), scoringRule(scoring), rewardRule(reward), shopSystem(shop), totalMoney(0), currentRound(1) {}

void RunSession::StartRun() {
    std::cout << "=== RUN START ===\n";

    while (currentRound <= MAX_ROUNDS) {
        std::cout << "\nRound " << currentRound << "\n";

        // Invariant execution sequence:
        // 1. Generate input
        TurnInput input = PhaseGenerateInput();

        // 2. Compute base score
        int baseScore = PhaseComputeBaseScore(input);

        // 3. Compute reward
        int reward = PhaseComputeReward(baseScore);

        // 4. Update money
        PhaseUpdateMoney(reward);

        // 5. Shop phase
        PhaseShop();

        // 6. Advance round
        PhaseAdvanceRound();
    }

    std::cout << "\n=== RUN END ===\n";
    std::cout << "Final money: " << totalMoney << "\n";
}

TurnInput RunSession::PhaseGenerateInput() {
    TurnInput input = inputGenerator->GenerateInput();
    std::cout << "  [PLAY] input generated: " << input.value << "\n";
    return input;
}

int RunSession::PhaseComputeBaseScore(const TurnInput& input) {
    int baseScore = scoringRule->ComputeBaseScore(input);
    std::cout << "  [SCORE] base score: " << baseScore << "\n";
    return baseScore;
}

int RunSession::PhaseComputeReward(int baseScore) {
    int reward = rewardRule->ComputeReward(baseScore, currentRound);
    return reward;
}

void RunSession::PhaseUpdateMoney(int reward) {
    totalMoney += reward;
    std::cout << "  [REWARD] gain: " << reward << " | total money: " << totalMoney << "\n";
}

void RunSession::PhaseShop() {
    shopSystem->OpenShop();
}

void RunSession::PhaseAdvanceRound() {
    currentRound++;
}