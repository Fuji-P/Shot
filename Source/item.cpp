/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

#include "pch.h"
#include "item.h"

int ITEM::gh[2];
int ITEM::ghs[2];

ITEM::ITEM()
{

	//0���F�œ��_�n�A1�����F�Ńp���[�A�b�v�n
	if (gh[0] == 0) {
		gh[0] = LoadGraph("item1.png");
		gh[1] = LoadGraph("item2.png");
	}

	if (ghs[0] == 0) {
		ghs[0] = LoadGraph("items1.png");
		ghs[1] = LoadGraph("items2.png");
	}

	x = 0;
	y = 0;
	prev_y = 0;

	type = 0;

	rad = 0;

	count = 0;

	fall_flag = false;

	flag = false;

}

void ITEM::All()
{
	Move();
	Draw();
}

void ITEM::Move()
{

	double tempy;

	//0.04���W�A��(��2�x)����]������B
	rad = 0.04 * count;

	++count;

	if (!fall_flag) {
		tempy = y;
		y += (y - prev_y) + 1;
		//���_�܂ł�������t���O���Ă�
		if ((y - prev_y) + 1 == 0) {
			fall_flag = true;
		}
		prev_y = tempy;
	}
	else {
		//�������͈�葬�x�ŗ���
		y += 1.5;
	}

	//��ʂ̊O�ɂ͂ݏo����t���O��߂��B
	if (y > 500) {
		Delete();
	}
}

void ITEM::Draw()
{
	DrawRotaGraph(x, y, 1.0, rad, gh[type], TRUE);
	DrawRotaGraph(x, y, 1.0, 0, ghs[type], TRUE);
}

void ITEM::Delete()
{
	count = 0;
	fall_flag = false;
	flag = false;
}

void ITEM::SetFlag(double x, double y, int type)
{
	this->x = x;
	this->y = y - 8;
	prev_y = y;
	this->type = type;

	flag = true;
}

void ITEM::GetPosition(double* x, double* y)
{
	*x = this->x;
	*y = this->y;
}

bool ITEM::GetFlag()
{
	return flag;
}

int ITEM::GetType()
{
	return type;
}
