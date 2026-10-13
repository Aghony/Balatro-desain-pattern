#ifndef HAND_ANALYSIS_H
#define HAND_ANALYSIS_H

#include <algorithm>
#include <map>
#include <vector>
#include "Hand.h"

namespace HandAnalysis {

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

inline bool IsFlush(const Hand& hand) {
    if (hand.cards.size() != 5) return false;
    for (const Card& c : hand.cards) {
        if (c.suit != hand.cards[0].suit) return false;
    }
    return true;
}

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

#endif // HAND_ANALYSIS_H