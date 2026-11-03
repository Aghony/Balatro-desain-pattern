#ifndef POKER_REWARD_H
#define POKER_REWARD_H

class RewardRule {
public:
    int earnMoney(bool win, int score) {
        if (!win) {
            return 0;
        }
        return 3 + score / 10;
    }
};

#endif