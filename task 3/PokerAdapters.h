#ifndef POKER_ADAPTERS_H
#define POKER_ADAPTERS_H

// Adapter: membungkus kelas-kelas dari diagram Balatro (HandGenerator, HandPlayer,
// ScoringRule, BlindRule, RewardRule) supaya cocok dengan interface Task 1
// (IInputGenerator, IScoringRule, IRewardRule). RunSession tidak perlu diubah.

#include <algorithm>
#include <iostream>

#include "InputGenerator.h"
#include "ScoringRule.h"   // IScoringRule (Task 1)
#include "RewardRule.h"    // IRewardRule  (Task 1)
#include "HandGenerator.h"
#include "HandPlayer.h"
#include "PokerScoring.h"  // ScoringRule  (diagram)
#include "PokerReward.h"   // RewardRule   (diagram)
#include "BlindRule.h"

// HandGenerator + HandPlayer  ->  IInputGenerator
class PokerInputGenerator : public IInputGenerator {
private:
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    static const int HAND_SIZE = 8;   // kartu yang dibagikan, pemain memilih 1-5 untuk dimainkan

public:
    // interactive = true: pemain memilih kartu sendiri. false: otomatis.
    // decks = jumlah dek (1 = standar; 2-3 agar Five of a Kind / Flush House bisa muncul).
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

        // value hanya ringkasan untuk log RunSession (kartu tertinggi);
        // perhitungan skor memakai input.hand
        return TurnInput{ highest, played };
    }
};

// ScoringRule (diagram)  ->  IScoringRule
class PokerScoringRule : public IScoringRule {
private:
    ScoringRule scoringRule;

public:
    int ComputeBaseScore(const TurnInput& input) override {
        std::cout << "  [RANK] " << ToString(scoringRule.evaluateRank(input.hand)) << "\n";
        return scoringRule.scoreHand(input.hand);
    }
};

// BlindRule + RewardRule (diagram)  ->  IRewardRule
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
