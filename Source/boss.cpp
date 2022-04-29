/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

#include "pch.h"
#include "boss.h"

//�R���X�g���N�^
BOSS::BOSS()
{
	//���W�����l
	x = 200;
	y = -100;
	prev_x = 200;
	prev_y = -100;

	raise = 1;
	raise2 = 1;
	angle = 0;
	move_pattern = 3;
	shot_pattern = 0;

	movex = 0;
	movey = 180;

	waitcount = 0;
	p3_state = 0;

	wait = false;
	damageflag = false;
	flag = true;

	//�摜�ǂݍ���
	gh_face[0] = LoadGraph("boss.png");
	gh_face[1] = LoadGraph("boss_damage.png");

	gh_shot[0] = LoadGraph("enemyshot1.png");
	gh_shot[1] = LoadGraph("enemyshot2.png");
	gh_shot[2] = LoadGraph("enemyshot3.png");

	//�e������
	for (int i = 0; i < BOSS_SHOTNUM; ++i) {
		shot[i].flag = false;
		shot[i].gflag = false;
		shot[i].gh = 0;
		shot[i].pattern = 0;
		shot[i].rad = 0;
		shot[i].speed = 0;
		shot[i].x = 0;
		shot[i].y = 0;
	}
}

void BOSS::All()
{
	Move();
	Draw();
}

void BOSS::Move()
{

	switch (move_pattern) {
		case 0:
			Appear();
			break;
		case 1:
			MovePattern1();
			break;
		case 2:
			MovePattern2();
			break;
		case 3:
			MovePattern3();
			break;
	}
}

void BOSS::Appear()
{
	double temp;

	angle += 1;

	temp = sin(angle * M_PI / 180);

	x = 200;
	y = prev_y + temp * movey;

	//��ʒu�܂ňړ�������ړ��p�^�[����1�ɕύX
	if (angle == 90) {
		move_pattern = 3;
		angle = 0;
	}
}

void BOSS::MovePattern1()
{
	angle += raise;

	y = 80 + sin(angle * M_PI / 180) * BOSS_SHAKE;

	if (angle == 90) {
		raise = -1;
	}
	else if (angle == -90) {
		raise = 1;
	}

	x = 200;
}

void BOSS::MovePattern2()
{
	if (!wait) {

		x += raise2;

		if (x == 70) {
			raise2 = 1;
			wait = true;
		}
		else if (x == 330) {
			raise2 = -1;
			wait = true;
		}
	}

	if (wait) {
		++waitcount;
		if (waitcount == 20) {
			wait = false;
			waitcount = 0;
		}
	}
}

void BOSS::MovePattern3()
{

	double temp;

	angle += 1;

	temp = sin(angle * M_PI / 180);

	x = prev_x + temp * movex;
	y = prev_y + temp * movey;

	if (angle == 90) {

		if (p3_state == 0) {
			MoveInit(70, 80, 1);
		}
		else if (p3_state == 1) {
			MoveInit(200, 160, 2);
		}
		else {
			MoveInit(330, 80, 0);
		}
	}
}

void BOSS::MoveInit(
	double	bx,
	double	by,
	int		state
)
{
	prev_x = x;
	prev_y = y;

	movex = bx - x;
	movey = by - y;

	angle = 0;

	p3_state = state;
}
void BOSS::Draw()
{
	//�e�����������Ƃ��̓_���[�W�p�̉摜��`��A
	if (damageflag) {
		DrawRotaGraph(x, y, 1.0, 0, gh_face[1], TRUE);
	}
	else {
		//���������Ƃ��͒ʏ�`��
		DrawRotaGraph(x, y, 1.0, 0, gh_face[0], TRUE);
	}


	damageflag = false;
}
