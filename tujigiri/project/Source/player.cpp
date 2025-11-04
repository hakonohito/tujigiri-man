#include "player.h"

Player::Player()
{
	hImage = LoadGraph("data/image/chara.png");
}

Player::~Player()
{

}

void Player::Update()
{

}

void Player::Draw()
{
	DrawRectGraph(352, 512, 0, 0, 128, 128, hImage, 1);
}