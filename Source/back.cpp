/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include "pch.h"
#include "back.h"

BACK::BACK()
{
	gh = LoadGraph("back1.png");
	gh2 = LoadGraph("back2.png");

	x = y = MARGIN;

}

void BACK::Draw()
{
	int width = 460;

	//1枚目描画
	DrawGraph(x, y, gh, FALSE);

	//二枚目描画
	DrawGraph(x, y - width, gh, FALSE);

	//一番下までスクロールしたら初期値に戻す
	if (y == width + MARGIN) {
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
