#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// ゲームプレイのシーンを制御する
/// </summary>
class TujigiriPlayScene : public SceneBase
{
public:
	TujigiriPlayScene();
	~TujigiriPlayScene();
	void Update() override;
	void Draw() override;
private:
	int SEHandle = -1;
};
