#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "HandGenerator.h"

Hand HandGenerator::generateHand() {
    std::cout << "Generating random hand...\n";
    
    // 1. Buat standar deck 52 kartu (Suit: Hearts, Diamonds, Clubs, Spades)
    std::vector<Card> deck;
    char suits[] = {'H', 'D', 'C', 'S'};
    for (char suit : suits) {
        for (int rank = 2; rank <= 14; ++rank) { // 2 sampai Ace (14)
            deck.push_back({rank, suit});
        }
    }
    
    // 2. Acak posisi kartu di dalam deck secara random
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
    
    // 3. Ambil 5 kartu pertama dari deck yang sudah diacak
    Hand hand;
    for (int i = 0; i < 5 && i < deck.size(); ++i) {
        hand.cards.push_back(deck[i]);
    }
    
    return hand;
}