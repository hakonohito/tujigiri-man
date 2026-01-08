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
    //ƒƒCƒvˆ—
    bool isWiping = false;
    int wipeAlpha = 0;
    int wipeFrame = 0;

};

