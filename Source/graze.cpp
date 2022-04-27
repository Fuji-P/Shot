/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include "pch.h"
#include "graze.h"

int GRAZE::gh;

GRAZE::GRAZE()
{
	x, y = 0;

	//初回だけ読む
	if (gh == 0) {
		gh = LoadGraph("graze.png");
	}

	rad = rate = 0;

	alpha = 255;

	flag = false;

	count = 0;

	srand((unsigned)time(NULL));
}

void GRAZE::Move()
{
	//初回だけ角度設定
	if (count == 0) {
		rad = rand() % 628 / 100;
	}

	int tempalpha = 255;
	alpha = tempalpha - (tempalpha / 20) * count;

	rate = 1.0 - 0.05 * count;

	x += cos(rad) * 6;
	y += sin(rad) * 6;

	++count;

	if (count == 20) {
		count = 0;
		flag = false;
	}
}
void GRAZE::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawRotaGraph(x, y, rate, 1, gh, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GRAZE::All()
{
	if (flag) {
		Move();
		Draw();
	}

}

bool GRAZE::GetFlag()
{
	return flag;
}

void GRAZE::SetFlag(double x, double y)
{
	this->x = x;
	this->y = y;
	flag = true;
}
