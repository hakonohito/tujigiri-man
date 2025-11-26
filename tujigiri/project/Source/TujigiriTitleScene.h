#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
/// </summary>
class TujigiriTitleScene : public SceneBase
{
public:
	TujigiriTitleScene();
	~TujigiriTitleScene();
	void Update() override;
	void Draw() override;
private:
	int BGMHandle = -1;
	int hImage[2];
};
