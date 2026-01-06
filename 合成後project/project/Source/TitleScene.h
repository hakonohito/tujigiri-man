#pragma once
#include "../Library/SceneBase.h"

class TitleScene : public SceneBase
{
public:
    TitleScene();
    ~TitleScene();
    void Update() override;
    void Draw() override;

private:
    //ワイプ処理変数
	bool isWiping = false; //ワイプ中かどうか
	int wipeAlpha = 0;    //黒板の透明度
	int wipeFrame = 0;    //経過フレーム数

    int nextScene = -1;
    // 0 = HEART（プレイ）
    // 1 = SELECT
    // 2 = RANKING
    // 3 = EXIT

};
