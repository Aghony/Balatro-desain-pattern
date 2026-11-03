#ifndef BLIND_RULE_H
#define BLIND_RULE_H

class BlindRule {
private:
    int target;
    int step;

public:
    explicit BlindRule(int initialTarget = 35, int increment = 15)
        : target(initialTarget), step(increment) {}

    bool checkBlind(int score) {
        return score >= target;
    }

    int getTarget() const {
        return target;
    }

    void nextBlind() {
        target += step;
    }
};

#endif