# balatro-replica # DP-Week1-5225600037-Justin

## Task 1 - Building a Balatro-Like Run

### Reflection

**1. What is the invariant structure in your program?**
The invariant structure in this program is the fixed sequence of phases executed inside `RunSession::StartRun()`. The loop strictly proceeds in this order for exactly 3 rounds:

1. Generate Input
2. Compute Base Score
3. Compute Reward
4. Update Money
5. Shop Phase
6. Advance Round

This lifecycle order and the structural flow are non-negotiable and guaranteed not to break regardless of how individual sub-mechanics behave.

**2. Which parts are mutable?**
The mutable parts are the concrete implementation details and calculation formulas encapsulated within the strategy interfaces and concrete classes:

- **Input Generation Logic**: How inputs are generated (e.g., deterministic vs. `RandomInputGenerator`).
- **Scoring Formulas**: How base score is calculated from the given input inside `IScoringRule`.
- **Reward Formulas**: The mathematical rule used to derive money from base score inside `IRewardRule`.
- **Shop System Items**: The catalog or interaction details presented inside `ShopSystem`.

**3. When you replaced the InputGenerator, why didn't RunSession change?**
`RunSession` relies on the abstract interface `IInputGenerator` rather than concrete classes (applying the Dependency Inversion Principle). Because `RunSession` only knows that it can call `GenerateInput()`, replacing `SimpleInputGenerator` with `RandomInputGenerator` changes runtime behavior without requiring any modifications to `RunSession` source code.

**4. What would happen if scoring logic was placed inside RunSession?**
If scoring logic was placed directly inside `RunSession`, it would violate the Single Responsibility Principle and break architectural discipline. Any modification to scoring formulas or rules would require editing `RunSession`, risking accidental changes to the core game loop and breaking the invariant structure. Tightly coupling state calculation with loop orchestration makes code refactoring risky and non-reusable.
