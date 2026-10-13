#ifndef HAND_CHECKERS_H
#define HAND_CHECKERS_H

#include "PokerHandChecker.h"
#include "HandAnalysis.h"

class FlushHouseChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (HandAnalysis::IsFlush(hand) &&
            HandAnalysis::IsFullHouseShape(HandAnalysis::RankGroups(hand))) {
            return HandRank::FlushHouse;
        }
        return passToNext(hand);
    }
};

class FiveOfAKindChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        std::vector<int> g = HandAnalysis::RankGroups(hand);
        if (!g.empty() && g[0] == 5) {
            return HandRank::FiveOfAKind;
        }
        return passToNext(hand);
    }
};

class RoyalFlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (HandAnalysis::IsFlush(hand) && HandAnalysis::IsRoyal(hand)) {
            return HandRank::RoyalFlush;
        }
        return passToNext(hand);
    }
};

class StraightFlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (HandAnalysis::IsFlush(hand) && HandAnalysis::IsStraight(hand)) {
            return HandRank::StraightFlush;
        }
        return passToNext(hand);
    }
};

class FourOfAKindChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        std::vector<int> g = HandAnalysis::RankGroups(hand);
        if (!g.empty() && g[0] == 4) {
            return HandRank::FourOfAKind;
        }
        return passToNext(hand);
    }
};

class FullHouseChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (HandAnalysis::IsFullHouseShape(HandAnalysis::RankGroups(hand))) {
            return HandRank::FullHouse;
        }
        return passToNext(hand);
    }
};

class FlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (HandAnalysis::IsFlush(hand)) {
            return HandRank::Flush;
        }
        return passToNext(hand);
    }
};

class StraightChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (HandAnalysis::IsStraight(hand)) {
            return HandRank::Straight;
        }
        return passToNext(hand);
    }
};

class ThreeOfAKindChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        std::vector<int> g = HandAnalysis::RankGroups(hand);
        if (!g.empty() && g[0] == 3) {
            return HandRank::ThreeOfAKind;
        }
        return passToNext(hand);
    }
};

class TwoPairChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        std::vector<int> g = HandAnalysis::RankGroups(hand);
        if (g.size() >= 2 && g[0] == 2 && g[1] == 2) {
            return HandRank::TwoPair;
        }
        return passToNext(hand);
    }
};

class PairChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        std::vector<int> g = HandAnalysis::RankGroups(hand);
        if (!g.empty() && g[0] == 2) {
            return HandRank::Pair;
        }
        return passToNext(hand);
    }
};

#endif 