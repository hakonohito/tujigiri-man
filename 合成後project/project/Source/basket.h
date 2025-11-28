#pragma once
#include "DxLib.h"

class Basket
{
public:
    Basket() {}
    Basket(int imageHandle); // 画像ハンドルを受け取るコンストラクタ
    ~Basket();

    void Update(); // キー入力で移動
    void Draw();   // カゴの描画
    bool CheckCatch(float fx, float fy); // 果物との当たり判定

    int x, y;      // カゴの位置
    int width;     // カゴの幅
    int height;    // カゴの高さ

private:
    int basketImage; // バスケット画像のハンドル（外から直接触れない）
};
