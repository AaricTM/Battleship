#include "AI.h"

AI::AI() : difficulty(EASY) {} // Default to Easy

void AI::SetDifficulty(DifficultyLevel level) {
    difficulty = level;
}

DifficultyLevel AI::GetDifficulty() const {
    return difficulty;
}
