#pragma once
#include <vector>


class ScoreManager
{
public:
	static void AddScore(int score);
	static const std::vector<int>& GetScores();
	static int GetLastScore(); // ← 最新スコアを取得
	static int GetRankOfLastScore();   // ← 最新スコアが何位かを判定

private:
	static std::vector<int> scores;
	static int lastScore; 
};

