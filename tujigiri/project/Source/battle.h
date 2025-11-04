#pragma once
#include "../Library/GameObject.h"

class Battle : public GameObject 
{
public:
	Battle();
	~Battle();
	void Update() override;
	void Draw() override;
private:
	bool start;
	bool finish;
	bool result;
	int count;
	int randomtime = 0;
	int level;
	void Random();
};