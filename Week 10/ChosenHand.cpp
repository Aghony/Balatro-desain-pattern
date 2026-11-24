#include "ChosenHand.h"

void ChosenHand::addCard(const Card& card) {
    cards.push_back(card);
}

void ChosenHand::removeCard(size_t index) {
    if (index < cards.size()) {
        cards.erase(cards.begin() + index);
    }
}

void ChosenHand::clear() {
    cards.clear();
}

const std::vector<Card>& ChosenHand::getCards() const {
    return cards;
}

bool ChosenHand::isEmpty() const {
    return cards.empty();
}