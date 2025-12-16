#include "ScoreManager.h"
#include <algorithm>

std::vector<int> ScoreManager::scores;

void ScoreManager::AddScore(int score) {
	scores.push_back(score);
	std::sort(scores.begin(), scores.end(), std::greater<int>()); // ~‡ƒ\[ƒg
	if (scores.size() > 4) scores.resize(4); // ãˆÊ4‚Â‚¾‚¯•Û
}

const std::vector<int>& ScoreManager::GetScores() {
	return scores;
}
