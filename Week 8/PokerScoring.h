#ifndef POKER_SCORING_H
#define POKER_SCORING_H

#include "Hand.h"
#include "PokerHandChecker.h"
#include "HandCheckers.h"

class ScoringRule {
private:
    FlushHouseChecker flushHouseChecker;
    FiveOfAKindChecker fiveOfAKindChecker;
    RoyalFlushChecker royalFlushChecker;
    StraightFlushChecker straightFlushChecker;
    FourOfAKindChecker fourOfAKindChecker;
    FullHouseChecker fullHouseChecker;
    FlushChecker flushChecker;
    StraightChecker straightChecker;
    ThreeOfAKindChecker threeOfAKindChecker;
    TwoPairChecker twoPairChecker;
    PairChecker pairChecker;

    static int cardChips(const Card& card) {
        if (card.rank == 14) return 11;
        if (card.rank >= 11) return 10;
        return card.rank;
    }

public:
    ScoringRule() {
        PokerHandChecker* chain[] = {
            &flushHouseChecker, &fiveOfAKindChecker, &royalFlushChecker,
            &straightFlushChecker, &fourOfAKindChecker, &fullHouseChecker,
            &flushChecker, &straightChecker, &threeOfAKindChecker,
            &twoPairChecker, &pairChecker
        };
        const int n = static_cast<int>(sizeof(chain) / sizeof(chain[0]));
        for (int i = 0; i + 1 < n; ++i) {
            chain[i]->setNext(chain[i + 1]);
        }
    }

    ScoringRule(const ScoringRule&) = delete;
    ScoringRule& operator=(const ScoringRule&) = delete;

    HandRank evaluateRank(const Hand& hand) {
        return flushHouseChecker.check(hand);
    }

    int convertRankToScore(HandRank rank) {
        switch (rank) {
            case HandRank::HighCard:      return 10;
            case HandRank::Pair:          return 20;
            case HandRank::TwoPair:       return  30;
            case HandRank::ThreeOfAKind:  return 40;
            case HandRank::Straight:      return 50;
            case HandRank::Flush:         return 60;
            case HandRank::FullHouse:     return 70;
            case HandRank::FourOfAKind:   return 80;
            case HandRank::StraightFlush: return 100;
            case HandRank::RoyalFlush:    return 120;
            case HandRank::FiveOfAKind:   return 140;
            case HandRank::FlushHouse:    return 160;
        }
        return 10;
    }

    int scoreHand(const Hand& hand) {
        int score = convertRankToScore(evaluateRank(hand));
        for (const Card& c : hand.cards) {
            score += cardChips(c);
        }
        return score;
    }
};

#endif