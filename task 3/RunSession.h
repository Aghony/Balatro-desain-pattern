#ifndef RUN_SESSION_H
#define RUN_SESSION_H

#include "InputGenerator.h"
#include "ScoringRule.h"
#include "RewardRule.h"
#include "ShopSystem.h"

class RunSession {
public:
    RunSession(IInputGenerator* inputGen, IScoringRule* scoring, IRewardRule* reward, ShopSystem* shop);
    void StartRun();

private:
    IInputGenerator* inputGenerator;
    IScoringRule* scoringRule;
    IRewardRule* rewardRule;
    ShopSystem* shopSystem;

    int totalMoney;
    int currentRound;
    const int MAX_ROUNDS = 3;

    // Fasa-fasa yang menjaga urutan eksak (Invariant)
    TurnInput PhaseGenerateInput();
    int PhaseComputeBaseScore(const TurnInput& input);
    int PhaseComputeReward(int baseScore);
    void PhaseUpdateMoney(int reward);
    void PhaseShop();
    void PhaseAdvanceRound();
};

#endif