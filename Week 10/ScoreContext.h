#ifndef SCORE_CONTEXT_H
#define SCORE_CONTEXT_H

#include "Hand.h"

class ScoreContext {
private:
    Hand hand;
    HandRank handRank;
    int chips;
    int mult;
    int finalScore;

public:
    ScoreContext(
        const Hand& playedHand,
        HandRank rank,
        int initialChips,
        int initialMult
    )
        : hand(playedHand),
          handRank(rank),
          chips(initialChips),
          mult(initialMult),
          finalScore(0) {}

    const Hand& getHand() const {
        return hand;
    }

    HandRank getHandRank() const {
        return handRank;
    }

    int getChips() const {
        return chips;
    }

    int getMult() const {
        return mult;
    }

    int getFinalScore() const {
        return finalScore;
    }

    void addChips(int amount) {
        chips += amount;
    }

    void addMult(int amount) {
        mult += amount;
    }

    void calculateFinalScore() {
        finalScore = chips * mult;
    }
};

#endif
