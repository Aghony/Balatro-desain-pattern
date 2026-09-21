#ifndef INPUT_GENERATOR_H
#define INPUT_GENERATOR_H

#include <cstdlib>

// Struktur data input
struct TurnInput {
    int value;
};

// Interface Abstract / Base Class
class IInputGenerator {
public:
    virtual ~IInputGenerator() = default;
    virtual TurnInput GenerateInput() = 0;
};

// Implementasi Konkret 1: Fixed / Simple Generator
class SimpleInputGenerator : public IInputGenerator {
private:
    int currentValue = 3;
public:
    TurnInput GenerateInput() override {
        return TurnInput{ currentValue++ };
    }
};

// Modification 1: Concrete Implementation Baru (RandomInputGenerator)
class RandomInputGenerator : public IInputGenerator {
public:
    TurnInput GenerateInput() override {
        // Mengubah nilai input secara acak (misal 1 - 10)
        return TurnInput{ (rand() % 10) + 1 };
    }
};

#endif