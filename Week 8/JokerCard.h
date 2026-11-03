#ifndef JOKER_CARD_H
#define JOKER_CARD_H

#include <iostream>

class JokerCard {
private:
    int bonusMultiplier;
public:
    JokerCard(int bonus = 10) : bonusMultiplier(bonus) {}

    // Step 4: Observer notification
    void onHandPlayed(int score) {
        std::cout << "  [JOKER] Notified: Hand played with score " << score << "\n";
    }

    // Step 5: Modify score
    int modifyScore(int currentScore) {
        int modified = currentScore + bonusMultiplier;
        std::cout << "  [JOKER] Score modified from " << currentScore << " to " << modified << "\n";
        return modified;
    }
};

#endif