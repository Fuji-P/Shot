/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

#include "pch.h"
#include "back.h"

BACK::BACK()
{
	//�摜�ǂݍ���
	gh = LoadGraph("back1.png");

	x = MARGIN;
	y = MARGIN;

}

void BACK::All()
{
	Move();
	Draw();
}

void BACK::Draw()
{
	int width = 460;

	//1���ڕ`��
	DrawGraph(x, y, gh, FALSE);

	//�񖇖ڕ`��
	DrawGraph(x, y - width, gh, FALSE);

	//��ԉ��܂ŃX�N���[�������珉���l�ɖ߂�
	if (y == width + MARGIN) {
		y = 10;
	}
}

void BACK::Move()
{
	y += SCROLL_SPEED;
}
