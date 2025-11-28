#pragma once
#include "DxLib.h"

class fruit
{
public:
    fruit();
    ~fruit();
    void Update();
    void Draw();
    //追加：中央エリアの範囲を設定する関数
    void setDropArea(int left, int right);

    int redpict;
    int active;
    int bluepict;
    int yellowpict;
    int dptime; // 落下速度（1フレームあたりの移動量）
    float x, y;// 果物の位置（x座標とy座標）
    int type; // 果物の種類 ※例（0:いちご, 1:みかん, 2:ぶどう）
    int spwandelay;// 出現までの待ち時間（未使用なら今後の拡張用）
private:
    //追加：中央エリアの範囲を保持する変数
    int dropLeft = 0;
    int dropRight = 640;
};

