#ifndef JOKER_CARD_H
#define JOKER_CARD_H

#include <iostream>
#include <string>
#include "JokerObserver.h"
#include "ScoreContext.h"

class Joker : public JokerObserver {
protected:
    std::string name;
    std::string description;
    int cost;

public:
    Joker(
        const std::string& jokerName,
        const std::string& jokerDescription,
        int jokerCost
    )
        : name(jokerName),
          description(jokerDescription),
          cost(jokerCost) {}

    virtual ~Joker() = default;

    std::string getName() const {
        return name;
    }

    std::string getDescription() const {
        return description;
    }

    int getCost() const {
        return cost;
    }

    void onScoreCalculated(
        const ScoreContext& context
    ) override {
        std::cout << "[JOKER NOTIFICATION] "
                  << name
                  << " received score information.\n";
    }

    virtual void applyEffect(
        ScoreContext& context,
        int ownedJokers
    ) = 0;
};

#endif
