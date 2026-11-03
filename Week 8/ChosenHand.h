#ifndef CHOSEN_HAND_H
#define CHOSEN_HAND_H

#include <vector>
#include "Card.h"

class ChosenHand {
private:
    std::vector<Card> cards;
public:
    void addCard(const Card& card);
    void removeCard(size_t index);
    void clear();
    const std::vector<Card>& getCards() const;
    bool isEmpty() const;
};

#endif