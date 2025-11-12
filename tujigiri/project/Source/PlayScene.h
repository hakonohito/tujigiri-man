#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// ゲームプレイのシーンを制御する
/// </summary>
class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
	int SEHandle = -1;
	int SEHandle2 = -1;
	int SEHandle3 = -1;
};
