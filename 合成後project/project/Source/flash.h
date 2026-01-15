#pragma once
#include "../Library/GameObject.h"

class Flash : public GameObject {
public:
	Flash();
	~Flash();
	void Update() override;
	void Draw() override;
	bool isChange = false;
private:
	int alpha;
	int count;
};