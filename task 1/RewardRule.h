#ifndef REWARD_RULE_H
#define REWARD_RULE_H

class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int ComputeReward(int baseScore, int currentRound) = 0;
};

// Modification 2: Aturan reward baru (Bukan sekadar reward = baseScore)
class BonusRewardRule : public IRewardRule {
public:
    int ComputeReward(int baseScore, int currentRound) override {
        // Contoh aturan: baseScore + 2, serta bonus pada ronde genap
        if (currentRound % 2 == 0) {
            return baseScore + 5;
        }
        return baseScore + 2;
    }
};

#endif