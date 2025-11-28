#pragma once
class Field
{
public:
    Field();
    ~Field();

    void Draw(); // 地面の描画

private:
    int groundImage; // 地面の画像ハンドル
};
