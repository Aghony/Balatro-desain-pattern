#ifndef POKER_ADAPTERS_H
#define POKER_ADAPTERS_H

#include <algorithm>
#include <iostream>
#include "InputGenerator.h"
#include "ScoringRule.h"
#include "RewardRule.h"
#include "HandGenerator.h"
#include "HandPlayer.h"
#include "PokerScoring.h"
#include "PokerReward.h"
#include "BlindRule.h"

class PokerInputGenerator : public IInputGenerator {
private:
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    static const int HAND_SIZE = 8;

public:
    explicit PokerInputGenerator(bool interactive = true, int decks = 1) : handPlayer(interactive) {
        handGenerator.setDecks(decks);
    }

    TurnInput GenerateInput() override {
        Hand played = handPlayer.play(handGenerator.generateHand(HAND_SIZE));

        std::cout << "  [PLAYED] ";
        int highest = 0;
        for (const Card& c : played.cards) {
            std::cout << ToString(c) << " ";
            highest = std::max(highest, c.rank);
        }
        std::cout << "\n";

        return TurnInput{ highest, played };
    }
};

class PokerScoringRule : public IScoringRule {
private:
    ScoringRule scoringRule;

public:
    int ComputeBaseScore(const TurnInput& input) override {
        std::cout << "  [RANK] " << ToString(scoringRule.evaluateRank(input.hand)) << "\n";
        return scoringRule.scoreHand(input.hand);
    }
};

class BlindRewardRule : public IRewardRule {
private:
    BlindRule blindRule;
    RewardRule rewardRule;

public:
    int ComputeReward(int baseScore, int currentRound) override {
        bool win = blindRule.checkBlind(baseScore);
        std::cout << "  [BLIND] round " << currentRound << " target " << blindRule.getTarget()
                  << " -> " << (win ? "PASSED" : "FAILED") << "\n";
        blindRule.nextBlind();
        return rewardRule.earnMoney(win, baseScore);
    }
};

#endif