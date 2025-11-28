#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// ゲームプレイのシーンを制御する
/// </summary>
class tujigiriPlayScene : public SceneBase
{
public:
	tujigiriPlayScene();
	~tujigiriPlayScene();
	void Update() override;
	void Draw() override;
private:
	int SEHandle = -1;
};
