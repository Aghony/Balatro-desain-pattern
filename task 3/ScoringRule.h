#ifndef SCORING_RULE_H
#define SCORING_RULE_H

#include "InputGenerator.h"

class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    virtual int ComputeBaseScore(const TurnInput& input) = 0;
};

class StandardScoringRule : public IScoringRule {
public:
    int ComputeBaseScore(const TurnInput& input) override {
        // Menghitung base score dari input
        return input.value * 2;
    }
};

#endif