#ifndef POKER_HAND_CHECKER_H
#define POKER_HAND_CHECKER_H

#include "Hand.h"
// Jika HandRank didefinisikan di file lain, pastikan di-include di sini
// #include "HandRank.h" 

class PokerHandChecker {
public:
    virtual ~PokerHandChecker() = default;

    virtual HandRank check(const Hand& hand) = 0;

    void setNext(PokerHandChecker* next) {
        nextChecker = next;
    }

protected:
    PokerHandChecker* nextChecker = nullptr;

    HandRank passToNext(const Hand& hand) {
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return HandRank::HighCard;
    }
};

#endif // POKER_HAND_CHECKER_H