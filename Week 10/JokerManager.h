
#ifndef JOKER_MANAGER_H
#define JOKER_MANAGER_H

#include <iostream>
#include <vector>
#include <memory>
#include <cstddef>
#include <utility>

#include "JokerCard.h"
#include "ScoreContext.h"

class JokerManager {
private:
    static constexpr int MAX_JOKER_SLOTS = 5;

    std::vector<std::unique_ptr<Joker>> jokers;

public:
    bool addJoker(std::unique_ptr<Joker> joker) {
        if (!joker || isFull()) {
            std::cout << "[JOKER] Cannot add Joker.\n";
            return false;
        }

        std::cout << "[JOKER] Acquired: "
                  << joker->getName() << "\n";

        jokers.push_back(std::move(joker));
        return true;
    }

    void notifyScoreCalculatedWithLog(
        const ScoreContext& context
    ) {
        std::cout << "\n===== JOKER NOTIFICATION =====\n";

        for (const auto& joker : jokers) {
            joker->onScoreCalculated(context);
        }
    }

    void applyJokers(ScoreContext& context) {
        std::cout << "\n===== APPLY JOKERS =====\n";

        int ownedJokers = getJokerCount();

        for (const auto& joker : jokers) {
            joker->applyEffect(context, ownedJokers);
        }
    }

    void displayJokers() const {
        std::cout << "\n===== JOKER INVENTORY =====\n";

        if (jokers.empty()) {
            std::cout << "No Joker owned.\n";
            return;
        }

        for (std::size_t i = 0; i < jokers.size(); i++) {
            std::cout << i + 1 << ". "
                      << jokers[i]->getName()
                      << " - "
                      << jokers[i]->getDescription()
                      << "\n";
        }

        std::cout << "Slots: "
                  << jokers.size()
                  << "/" << MAX_JOKER_SLOTS << "\n";
    }

    bool sellJoker(std::size_t index) {
        if (index >= jokers.size()) {
            std::cout << "[JOKER] Invalid index!\n";
            return false;
        }

        std::cout << "[JOKER] Sold: "
                  << jokers[index]->getName() << "\n";

        jokers.erase(jokers.begin() + index);
        return true;
    }

    int getJokerCount() const {
        return static_cast<int>(jokers.size());
    }

    bool isFull() const {
        return jokers.size() >= MAX_JOKER_SLOTS;
    }
};

#endif
