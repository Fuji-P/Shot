/*
* サイト名	：プログラミング入門サイト 〜bituse〜
* リンク	：https://bituse.info/
*/

#include "pch.h"
#include "item.h"

int ITEM::gh[2];
int ITEM::ghs[2];

ITEM::ITEM()
{
	if (gh[0] == 0) {
		//0が青色で得点系、1が黄色でパワーアップ系
		gh[0] = LoadGraph("item1.png");
		gh[1] = LoadGraph("item2.png");
		ghs[0] = LoadGraph("items1.png");
		ghs[1] = LoadGraph("items2.png");

	}
	x = y = 0;

	rad = 0;

	count = 0;

	fall_flag = false;

	flag = false;

}

void ITEM::Move()
{

	double tempy;

	//0.04ラジアン(約2度)ずつ回転させる。
	rad = 0.04 * count;

	++count;

	if (!fall_flag) {
		tempy = y;
		y += (y - prev_y) + 1;
		//頂点までいったらフラグ立てる
		if ((y - prev_y) + 1 == 0) {
			fall_flag = true;
		}
		prev_y = tempy;
	}
	else {
		//落下時は一定速度で落下
		y += 1.5;
	}

	//画面の外にはみ出たらフラグを戻す。
	if (y > 500) {
		Delete();
	}
}

void ITEM::Delete()
{
	count = 0;
	fall_flag = false;
	flag = false;
}

void ITEM::Draw()
{
	DrawRotaGraph(x, y, 1.0, rad, gh[type], TRUE);
	DrawRotaGraph(x, y, 1.0, 0, ghs[type], TRUE);
}

void ITEM::SetFlag(double x, double y, int type)
{
	this->x = x;
	this->y = y - 8;
	prev_y = y;
	this->type = type;

	flag = true;
}

bool ITEM::GetFlag()
{
	return flag;
}

void ITEM::GetPosition(double* x, double* y)
{
	*x = this->x;
	*y = this->y;
}

int ITEM::GetType()
{
	return type;
}

void ITEM::All()
{
	Move();
	Draw();
}