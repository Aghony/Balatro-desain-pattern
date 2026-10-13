#ifndef BLIND_RULE_H
#define BLIND_RULE_H

// Blind = target skor yang harus dicapai di sebuah ronde.
class BlindRule {
private:
    int target;
    int step;

public:
    explicit BlindRule(int initialTarget = 35, int increment = 15)
        : target(initialTarget), step(increment) {}

    // Lolos jika skor mencapai atau melewati target
    bool checkBlind(int score) {
        return score >= target;
    }

    int getTarget() const {
        return target;
    }

    // Naik ke blind berikutnya (target makin tinggi)
    void nextBlind() {
        target += step;
    }
};

#endif
