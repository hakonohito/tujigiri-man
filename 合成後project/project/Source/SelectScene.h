#pragma once
#include "../Library/SceneBase.h"

class SelectScene : public SceneBase
{
public:
	SelectScene();
	~SelectScene();
	void Update() override;
	void Draw() override;
private:
	int SEHandle;
	int SEHandle2;
	bool FaderCheck = false;
	bool HtoHeart = false; //í«â¡ÇµÇ‹ÇµÇΩÅ@Åiñÿë∫Åj

};