/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

#include "pch.h"
#include "enemy.h"

ENEMY::ENEMY(
				int type,
				int stype,
				int m_pattern,
				int s_pattern,
				int in_time,
				int stop_time,
				int shot_time,
				int out_time,
				int x,
				int y,
				int speed,
				int hp,
				int item
			)
{

	//�T�C�Y
	width = 27;
	height = 25;

	//�G�̎��
	this->type = type;
	this->stype = stype;

	//�ړ��p�^�[���ƃV���b�g�p�^�[��
	this->m_pattern = m_pattern;
	this->s_pattern = s_pattern;

	this->x = x;
	this->y = y;

	this->in_time = in_time;

	this->stop_time = stop_time;

	this->shot_time = shot_time;

	this->out_time = out_time;

	//hp�ƃA�C�e�����
	this->hp = hp;
	this->item = item;

	//�G�摜�ǂݍ���
	if (type == 0) {
		LoadDivGraph("enemy.png", 3, 1, 3, 27, 25, gh);
	}

	int temp;
	//�e�摜�ǂݍ���
	if (stype == 0) {
		temp = LoadGraph("enemyshot1.png");
	}

	int w, h;
	GetGraphSize(temp, &w, &h);

	for (int i = 0; i < ENEMY_SNUM; ++i) {
		shot[i].flag = false;
		shot[i].gh = temp;
		shot[i].width = w;
		shot[i].height = h;
		shot[i].pattern = s_pattern;
		shot[i].speed = speed;
		shot[i].x = x;
		shot[i].y = y;
	}

	count = 0;
	scount = 0;

	deadflag = false;
	endflag = false;
	sflag = false;
}


void ENEMY::Move()
{
	//�܂������Ă邩��ʓ��ɋ���Ƃ���������
	if (!deadflag) {
		switch (m_pattern) {
			//�r���Ŏ~�܂��āA���̂܂܌��ɋA��p�^�[��
		case 0:

			//�o�Ă��Ă���~�܂鎞�Ԃ܂ł̊ԂȂ牺�Ɉړ�
			if (in_time < g_count && g_count < stop_time) {
//				y += 2;
				y += 1;
				//�A�Ҏ��Ԃ��߂�����߂�B
			}
			else if (g_count > out_time) {
//				y -= 2;
				y -= 1;
			}
			break;

			//���̂܂܎~�܂炸�ɉ��ɍs���p�^�[��
		case 1:

			if (in_time <= g_count) {
//				y += 2;
				y += 1;
			}

			break;

			//������Ƃ����Ɉړ����Ȃ�������Ă���
		case 2:
			if (in_time <= g_count) {
//				y += 1;
				y += 0.5;
				if (count % 10 == 0) {
//					x -= 1;
					x -= 0.5;
				}
			}
			break;

			//������Ƃ��E�Ɉړ����Ȃ�������Ă���
		case 3:
			if (in_time <= g_count) {
//				y += 1;
				y += 0.5;
				if (count % 10 == 0) {
//					x += 1;
					x += 0.5;
				}
			}
			break;

		}
		//��ʂ���͂ݏo������Adeadflag(�͂ݏo�������ʂ��̃t���O)��true�ɂ���B
		if (g_count >= stop_time) {
			if (OutCheck()) {
				deadflag = true;
			}
		}
		++count;
	}
}

void ENEMY::Draw()
{
	int temp;

	//�e����ŏ��ɕ`��
	for (int i = 0; i < ENEMY_SNUM; ++i) {
		if (shot[i].flag) {
			DrawGraph(shot[i].x, shot[i].y, shot[i].gh, true);
		}
	}

	if (!endflag) {

//		temp = count % 40 / 10;
		temp = count % 120 / 30;
		if (temp == 3)
			temp = 1;

		DrawGraph(x, y, gh[temp], TRUE);
	}
}

void ENEMY::Shot()
{

	//���˃^�C�~���O�ɂȂ�����A�t���O�𗧂Ă�
	if (shot_time == g_count) {
		sflag = true;
	}

	//�t���O�����Ă�Ƃ�����
	if (sflag) {

		switch (s_pattern) {
		case 0:
			//10��Ɉ�񔭎ˁB40�܂łȂ̂�5�����ˁB
//			if (scount % 10 == 0 && scount <= 40) {
			if (scount % 20 == 0 && scount <= 80) {
				for (int i = 0; i < ENEMY_SNUM; ++i) {
					//�t���O�������ĂȂ��e��T���āA���W�����Z�b�g
					if (shot[i].flag == false) {
						shot[i].flag = true;
						shot[i].x = x;
						shot[i].y = y;
						break;
					}
				}
			}
			break;
		}

		//�t���O�������Ă�e�̐�
		int s = 0;

		//�t���O�����Ă�e�����A�e�̈ړ����s��
		for (int i = 0; i < ENEMY_SNUM; ++i) {
			if (shot[i].flag) {
				shot[i].y += shot[i].speed;

				//�e����ʂ��͂ݏo����t���O��߂��B
				if (shot[i].x < -20 || shot[i].x>420 || shot[i].y < -20 || shot[i].y>500) {
					shot[i].flag = false;
					continue;
				}
				++s;
			}
		}
		//s���[���Ƃ������Ƃ͔��˒��̒e���Ȃ��B
		//����deadflag��TRUE�Ƃ������Ƃ͂��̓G�̃N���X�͏��ł����Ă��悢
		if (s == 0 && deadflag) {
			//�G�N���X���Ńt���O��TRUE�ɂ���
			endflag = true;
		}
		++scount;
	}
}

bool ENEMY::All()
{
	Move();

	Shot();

	Draw();

	++count;

	return endflag;
}

bool ENEMY::OutCheck()
{
	if (x < -50 || x > 520 || y < -50 || y > 530) {
		return true;
	}
	else {
		return false;
	}
}