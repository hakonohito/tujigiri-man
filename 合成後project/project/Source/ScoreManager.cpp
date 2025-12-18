#include "ScoreManager.h"
#include <algorithm>

std::vector<int> ScoreManager::scores;
int ScoreManager::lastScore = 0;

void ScoreManager::AddScore(int score)
{
	lastScore = score; // ← ここで最後のスコアを保存
	scores.push_back(score);
	std::sort(scores.begin(), scores.end(), std::greater<int>()); // 降順ソート
	if (scores.size() > 3) scores.resize(3); // 上位3つだけ保持
}

const std::vector<int>& ScoreManager::GetScores() {
	return scores;
}

int ScoreManager::GetLastScore()
{
	return lastScore;
}

int ScoreManager::GetRankOfLastScore()
{
	for (int i = 0; i < scores.size(); ++i) {
		if (scores[i] == lastScore) {
			return i; // 0なら1位、1なら2位、2なら3位
		}
	}
	return -1; // ランク外
}
