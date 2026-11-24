
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "HandGenerator.h"

Hand HandGenerator::generateHand(int size) {
    std::cout << "Generating random hand...\n";

    // Buat standar deck 52 kartu
    std::vector<Card> deck;

    Suit suits[] = {
        Suit::Hearts,
        Suit::Diamonds,
        Suit::Clubs,
        Suit::Spades
    };

    for (Suit suit : suits) {
        for (int rank = 2; rank <= 14; ++rank) {
            deck.push_back({rank, suit});
        }
    }

    // Acak deck
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);

    // Ambil kartu sesuai jumlah yang diminta
    Hand hand;

    for (int i = 0; i < size && i < static_cast<int>(deck.size()); ++i) {
        hand.cards.push_back(deck[i]);
    }

    return hand;
}
