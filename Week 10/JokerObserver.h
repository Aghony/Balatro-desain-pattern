#ifndef JOKER_OBSERVER_H
#define JOKER_OBSERVER_H

#include "ScoreContext.h"

class JokerObserver {
public:
    virtual ~JokerObserver() = default;

    virtual void onScoreCalculated(
        const ScoreContext& context
    ) = 0;
};

#endif
