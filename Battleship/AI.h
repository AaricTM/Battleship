#pragma once
#ifndef AI_H
#define AI_H

enum DifficultyLevel { EASY, MEDIUM, HARD };

class AI {
private:
    DifficultyLevel difficulty;
public:
    AI();
    void SetDifficulty(DifficultyLevel level);
    DifficultyLevel GetDifficulty() const;
};

#endif // AI_H
