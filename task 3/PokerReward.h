#ifndef POKER_REWARD_H
#define POKER_REWARD_H

// Menentukan uang yang didapat setelah sebuah ronde.
class RewardRule {
public:
    // Kalah = 0. Menang = 3 dasar + 1 per 10 poin skor.
    int earnMoney(bool win, int score) {
        if (!win) {
            return 0;
        }
        return 3 + score / 10;
    }
};

#endif
