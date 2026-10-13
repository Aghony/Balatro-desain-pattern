#ifndef HAND_GENERATOR_H
#define HAND_GENERATOR_H

#include <algorithm>
#include <random>
#include <vector>

#include "Hand.h"

// Membagikan kartu acak dari dek.
// Dengan 1 dek (52 kartu) tidak ada kartu kembar, sehingga Five of a Kind dan Flush House
// mustahil muncul. Naikkan jumlah dek (setDecks) agar kartu kembar ada:
//   2 dek -> Five of a Kind mungkin muncul
//   3 dek -> Flush House juga mungkin muncul
class HandGenerator {
private:
    std::mt19937 rng;
    std::vector<Card> deck;

    void buildDeck(int decks) {
        deck.clear();
        for (int d = 0; d < decks; ++d) {
            for (int s = 0; s < 4; ++s) {
                for (int r = 2; r <= 14; ++r) {
                    deck.push_back(Card{ r, static_cast<Suit>(s) });
                }
            }
        }
    }

public:
    HandGenerator() : rng(std::random_device{}()) { buildDeck(1); }

    // Seed tetap, berguna untuk pengujian yang bisa diulang
    explicit HandGenerator(unsigned int seed) : rng(seed) { buildDeck(1); }

    void setDecks(int decks) {
        if (decks < 1) decks = 1;
        if (decks > 8) decks = 8;
        buildDeck(decks);
    }

    int deckSize() const {
        return static_cast<int>(deck.size());
    }

    Hand generateHand(int size = 5) {
        if (size < 1) size = 1;
        if (size > deckSize()) size = deckSize();

        // Pengocokan parsial (Fisher-Yates): cukup mengocok 'size' kartu pertama
        for (int i = 0; i < size; ++i) {
            std::uniform_int_distribution<int> pick(i, deckSize() - 1);
            std::swap(deck[i], deck[pick(rng)]);
        }

        Hand hand;
        hand.cards.assign(deck.begin(), deck.begin() + size);
        return hand;
    }
};

#endif
