#ifndef SCORING_RULE_H
#define SCORING_RULE_H

#include "InputGenerator.h"
#include "ScoreContext.h"

class IScoringRule {
public:
    virtual ~IScoringRule() = default;

    // Fungsi scoring lama
    virtual int ComputeBaseScore(const TurnInput& input) = 0;

    // Fungsi baru untuk sistem Joker
    virtual ScoreContext CreateScoreContext(const TurnInput& input) = 0;
};

class StandardScoringRule : public IScoringRule {
public:
    int ComputeBaseScore(const TurnInput& input) override {
        return input.value * 2;
    }

    ScoreContext CreateScoreContext(const TurnInput& input) override {
        int chips = input.value * 2;

        return ScoreContext(
            input.hand,
            HandRank::HighCard,
            chips,
            1
        );
    }
};

#endif
