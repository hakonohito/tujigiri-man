#pragma once
#include "../Library/SceneBase.h"

class SelectScene : public SceneBase
{
public:
	SelectScene();
	~SelectScene();
	void Update() override;
	void Draw() override;
};