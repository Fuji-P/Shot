/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include "pch.h"
#include "enemy.h"

ENEMY::ENEMY()
{
	LoadDivGraph("enemy.png", 3, 1, 3, 27, 25, gh);

	width = 27;
	height = 25;

	x = 50;
	y = -50;

//	in_time = 180;
	in_time = 360;

//	stop_time = 300;
	stop_time = 600;

//	out_time = 420;
	out_time = 840;

	count = 0;

	endflag = false;

}

void ENEMY::Move()
{
	//出てきてから止まる時間までの間なら下に移動
	if (in_time < g_count && g_count < stop_time) {
//		y += 2;
		y += 1;
		//帰還時間を過ぎたら戻る。
	}
	else if (g_count > out_time) {
//		y -= 2;
		y -= 1;
		if (y < -40) {
			endflag = true;
		}
	}
}

void ENEMY::Draw()
{
	int temp;

	if (!endflag) {

//		temp = count % 40 / 10;
		temp = count % 80 / 20;
		if (temp == 3)
			temp = 1;

		DrawGraph(x, y, gh[temp], TRUE);
	}
}

bool ENEMY::All()
{
	Move();

	Draw();

	++count;

	return endflag;
}