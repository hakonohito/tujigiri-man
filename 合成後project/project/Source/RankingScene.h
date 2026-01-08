#pragma once
#include "../Library/SceneBase.h"

class RankingScene : public SceneBase
{
public:
    RankingScene();
    ~RankingScene();
    void Update() override;
    void Draw() override;
private:
    //ワイプ処理
    bool isWiping = false;
    int wipeAlpha = 0;
    int wipeFrame = 0;
    //oキーでセレクトシーン切り替え
    bool goSelect = false;


};

