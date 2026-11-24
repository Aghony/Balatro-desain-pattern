
#ifndef JOKER_FACTORY_H
#define JOKER_FACTORY_H

#include <memory>
#include <string>
#include <iostream>
#include "JokerCard.h"

// BASIC JOKER
class BasicJoker : public Joker {
public:
    BasicJoker()
        : Joker("Basic Joker", "+4 Mult", 4) {}

    void applyEffect(ScoreContext& context, int ownedJokers) override {
        context.addMult(4);
        std::cout << "[JOKER] Basic: +4 Mult\n";
    }
};

// GREEDY JOKER
class GreedyJoker : public Joker {
public:
    GreedyJoker()
        : Joker("Greedy Joker", "+3 Mult per Diamond", 5) {}

    void applyEffect(ScoreContext& context, int ownedJokers) override {
        int count = 0;

        for (const Card& card : context.getHand().cards) {
            if (card.suit == Suit::Diamonds) {
                count++;
            }
        }

        int bonus = count * 3;
        context.addMult(bonus);

        std::cout << "[JOKER] Greedy: +" << bonus << " Mult\n";
    }
};

// LUSTY JOKER
class LustyJoker : public Joker {
public:
    LustyJoker()
        : Joker("Lusty Joker", "+3 Mult per Heart", 5) {}

    void applyEffect(ScoreContext& context, int ownedJokers) override {
        int count = 0;

        for (const Card& card : context.getHand().cards) {
            if (card.suit == Suit::Hearts) {
                count++;
            }
        }

        int bonus = count * 3;
        context.addMult(bonus);

        std::cout << "[JOKER] Lusty: +" << bonus << " Mult\n";
    }
};

// PAIR JOKER
class PairJoker : public Joker {
public:
    PairJoker()
        : Joker("Pair Joker", "+8 Mult if Pair", 6) {}

    void applyEffect(ScoreContext& context, int ownedJokers) override {
        if (context.getHandRank() == HandRank::Pair) {
            context.addMult(8);
            std::cout << "[JOKER] Pair: +8 Mult\n";
        }
    }
};

// SLY JOKER
class SlyJoker : public Joker {
public:
    SlyJoker()
        : Joker("Sly Joker", "+50 Chips if Pair", 6) {}

    void applyEffect(ScoreContext& context, int ownedJokers) override {
        if (context.getHandRank() == HandRank::Pair) {
            context.addChips(50);
            std::cout << "[JOKER] Sly: +50 Chips\n";
        }
    }
};

// ABSTRACT JOKER
class AbstractJoker : public Joker {
public:
    AbstractJoker()
        : Joker("Abstract Joker", "+3 Mult per other Joker", 8) {}

    void applyEffect(ScoreContext& context, int ownedJokers) override {
        int bonus = (ownedJokers - 1) * 3;

        context.addMult(bonus);

        std::cout << "[JOKER] Abstract: +" << bonus << " Mult\n";
    }
};

// JOKER FACTORY
class JokerFactory {
public:
    static std::unique_ptr<Joker> createJoker(const std::string& type) {
        if (type == "Basic")
            return std::make_unique<BasicJoker>();

        if (type == "Greedy")
            return std::make_unique<GreedyJoker>();

        if (type == "Lusty")
            return std::make_unique<LustyJoker>();

        if (type == "Pair")
            return std::make_unique<PairJoker>();

        if (type == "Sly")
            return std::make_unique<SlyJoker>();

        if (type == "Abstract")
            return std::make_unique<AbstractJoker>();

        return nullptr;
    }
};

#endif
