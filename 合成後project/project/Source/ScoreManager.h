#pragma once
#include <vector>


class ScoreManager
{
public:
	static void AddScore(int score);
	static const std::vector<int>& GetScores();

private:
	static std::vector<int> scores;

};

