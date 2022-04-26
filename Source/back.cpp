/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include "pch.h"
#include "back.h"

BACK::BACK()
{
	gh = LoadGraph("back1.png");

	x = y = MARGIN;
}

void BACK::Draw()
{
	//1枚目描画
	DrawGraph(x, y, gh, FALSE);

	//二枚目描画
	DrawGraph(x, y - 460, gh, FALSE);

	//一番下までスクロールしたら初期値に戻す
	if (y == 460 + MARGIN) {
		y = 10;
	}
}

void BACK::Move()
{
	y += SCROLL_SPEED;
}

void BACK::All()
{
	Draw();
	Move();
}
