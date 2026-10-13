#ifndef HAND_H
#define HAND_H

#include <string>
#include <vector>

// Jenis kartu (suit)
enum class Suit { Clubs, Diamonds, Hearts, Spades };

// Satu kartu. rank: 2..10, 11 = J, 12 = Q, 13 = K, 14 = A
struct Card {
    int rank;
    Suit suit;
};

// "Hand" = kumpulan kartu yang dimainkan pemain (1 sampai 5 kartu)
struct Hand {
    std::vector<Card> cards;
};

// 12 peringkat tangan, dari terendah ke tertinggi
enum class HandRank {
    HighCard,
    Pair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush,
    FiveOfAKind,
    FlushHouse
};

inline std::string ToString(HandRank rank) {
    switch (rank) {
        case HandRank::HighCard:      return "High Card";
        case HandRank::Pair:          return "Pair";
        case HandRank::TwoPair:       return "Two Pair";
        case HandRank::ThreeOfAKind:  return "Three of a Kind";
        case HandRank::Straight:      return "Straight";
        case HandRank::Flush:         return "Flush";
        case HandRank::FullHouse:     return "Full House";
        case HandRank::FourOfAKind:   return "Four of a Kind";
        case HandRank::StraightFlush: return "Straight Flush";
        case HandRank::RoyalFlush:    return "Royal Flush";
        case HandRank::FiveOfAKind:   return "Five of a Kind";
        case HandRank::FlushHouse:    return "Flush House";
    }
    return "High Card";
}

inline std::string ToString(const Card& card) {
    static const char suitChar[] = { 'C', 'D', 'H', 'S' };
    std::string r;
    switch (card.rank) {
        case 11: r = "J"; break;
        case 12: r = "Q"; break;
        case 13: r = "K"; break;
        case 14: r = "A"; break;
        default: r = std::to_string(card.rank);
    }
    return r + suitChar[static_cast<int>(card.suit)];
}

#endif
