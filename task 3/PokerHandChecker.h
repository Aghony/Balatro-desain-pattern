#ifndef POKER_HAND_CHECKER_H
#define POKER_HAND_CHECKER_H

#include <algorithm>
#include <functional>
#include <map>
#include <vector>

#include "Hand.h"

// ---------------------------------------------------------------------------
// Fungsi bantu untuk menganalisis tangan
// ---------------------------------------------------------------------------
namespace HandAnalysis {

// Jumlah kartu per rank, diurutkan menurun.
// Contoh: Full House (5,5,5,9,9) -> {3,2}; Two Pair (5,5,6,6,9) -> {2,2,1}
inline std::vector<int> RankGroups(const Hand& hand) {
    std::map<int, int> count;
    for (const Card& c : hand.cards) {
        ++count[c.rank];
    }
    std::vector<int> groups;
    for (const auto& entry : count) {
        groups.push_back(entry.second);
    }
    std::sort(groups.begin(), groups.end(), std::greater<int>());
    return groups;
}

// Flush: tepat 5 kartu dengan suit yang sama
inline bool IsFlush(const Hand& hand) {
    if (hand.cards.size() != 5) return false;
    for (const Card& c : hand.cards) {
        if (c.suit != hand.cards[0].suit) return false;
    }
    return true;
}

// Straight: 5 kartu berurutan dengan rank berbeda.
// As bisa rendah (A-2-3-4-5) atau tinggi (10-J-Q-K-A), tidak boleh "memutar" (K-A-2-3-4).
inline bool IsStraight(const Hand& hand) {
    if (hand.cards.size() != 5) return false;
    std::vector<int> ranks;
    for (const Card& c : hand.cards) {
        ranks.push_back(c.rank);
    }
    std::sort(ranks.begin(), ranks.end());
    if (std::adjacent_find(ranks.begin(), ranks.end()) != ranks.end()) return false;

    bool consecutive = (ranks[4] - ranks[0] == 4);
    bool aceLow = (ranks[0] == 2 && ranks[1] == 3 && ranks[2] == 4 &&
                   ranks[3] == 5 && ranks[4] == 14);
    return consecutive || aceLow;
}

// Royal: 10-J-Q-K-A
inline bool IsRoyal(const Hand& hand) {
    if (hand.cards.size() != 5) return false;
    std::vector<int> ranks;
    for (const Card& c : hand.cards) {
        ranks.push_back(c.rank);
    }
    std::sort(ranks.begin(), ranks.end());
    return ranks == std::vector<int>({ 10, 11, 12, 13, 14 });
}

inline bool IsFullHouseShape(const std::vector<int>& g) {
    return g.size() == 2 && g[0] == 3 && g[1] == 2;
}

} // namespace HandAnalysis

// ---------------------------------------------------------------------------
// Chain of Responsibility:
// tiap checker memeriksa satu peringkat. Kalau cocok, ia mengembalikan peringkatnya.
// Kalau tidak, ia meneruskan ke checker berikutnya (nextChecker).
// Jika rantai habis, hasilnya HighCard.
// ---------------------------------------------------------------------------
class PokerHandChecker {
public:
    virtual ~PokerHandChecker() = default;

    virtual HandRank check(const Hand& hand) = 0;

    void setNext(PokerHandChecker* next) {
        nextChecker = next;
    }

protected:
    PokerHandChecker* nextChecker = nullptr;

    // Dipakai kelas turunan untuk meneruskan pemeriksaan ke mata rantai berikutnya
    HandRank passToNext(const Hand& hand) {
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return HandRank::HighCard;
    }
};

// Flush House: Full House dengan semua kartu satu suit (butuh kartu kembar)
class FlushHouseChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (HandAnalysis::IsFlush(hand) &&
            HandAnalysis::IsFullHouseShape(HandAnalysis::RankGroups(hand))) {
            return HandRank::FlushHouse;
        }
        return passToNext(hand);
    }
};

// Five of a Kind: 5 kartu dengan rank sama (butuh kartu kembar)
class FiveOfAKindChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        std::vector<int> g = HandAnalysis::RankGroups(hand);
        if (!g.empty() && g[0] == 5) {
            return HandRank::FiveOfAKind;
        }
        return passToNext(hand);
    }
};

// Royal Flush: 10-J-Q-K-A satu suit
class RoyalFlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (HandAnalysis::IsFlush(hand) && HandAnalysis::IsRoyal(hand)) {
            return HandRank::RoyalFlush;
        }
        return passToNext(hand);
    }
};

// Straight Flush: Straight sekaligus Flush
class StraightFlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (HandAnalysis::IsFlush(hand) && HandAnalysis::IsStraight(hand)) {
            return HandRank::StraightFlush;
        }
        return passToNext(hand);
    }
};

// Four of a Kind: 4 kartu dengan rank sama
class FourOfAKindChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        std::vector<int> g = HandAnalysis::RankGroups(hand);
        if (!g.empty() && g[0] == 4) {
            return HandRank::FourOfAKind;
        }
        return passToNext(hand);
    }
};

// Full House: tiga kartu sama + sepasang
class FullHouseChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (HandAnalysis::IsFullHouseShape(HandAnalysis::RankGroups(hand))) {
            return HandRank::FullHouse;
        }
        return passToNext(hand);
    }
};

// Flush: kelima kartu memiliki suit yang sama
class FlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (HandAnalysis::IsFlush(hand)) {
            return HandRank::Flush;
        }
        return passToNext(hand);
    }
};

// Straight: kelima kartu berurutan
class StraightChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (HandAnalysis::IsStraight(hand)) {
            return HandRank::Straight;
        }
        return passToNext(hand);
    }
};

// Three of a Kind: 3 kartu dengan rank sama
class ThreeOfAKindChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        std::vector<int> g = HandAnalysis::RankGroups(hand);
        if (!g.empty() && g[0] == 3) {
            return HandRank::ThreeOfAKind;
        }
        return passToNext(hand);
    }
};

// Two Pair: dua pasang berbeda
class TwoPairChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        std::vector<int> g = HandAnalysis::RankGroups(hand);
        if (g.size() >= 2 && g[0] == 2 && g[1] == 2) {
            return HandRank::TwoPair;
        }
        return passToNext(hand);
    }
};

// Pair: sepasang kartu dengan rank sama
class PairChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        std::vector<int> g = HandAnalysis::RankGroups(hand);
        if (!g.empty() && g[0] == 2) {
            return HandRank::Pair;
        }
        return passToNext(hand);
    }
};

#endif
