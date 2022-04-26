/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

#include "pch.h"
#include "enemy.h"

ENEMY::ENEMY(
				const char*		c_filename,
				int				type,
				int				m_pattern,
				int				x,
				int				y,
				int				in_time,
				int				stop_time,
				int				shot_time,
				int				out_time,
				const char*		s_filename,
				int				stype,
				int				s_pattern,
				int				speed
			)
{

	//�ǂݍ���
	LoadDivGraph(c_filename, 3, 1, 3, 27, 25, gh);

	//�T�C�Y
	width = 27;
	height = 25;

	//�G�̎��
	this->type = type;

	//�e�̎��
	this->stype = stype;

	//�ړ��p�^�[���ƃV���b�g�p�^�[��
	this->m_pattern = m_pattern;
	this->s_pattern = s_pattern;

	//���W�Z�b�g
	this->x = x;
	this->y = y;

	//�o���A��~�A���ˁA�A�Ҏ��ԃZ�b�g
	this->in_time = in_time;

	this->stop_time = stop_time;

	this->shot_time = shot_time;

	this->out_time = out_time;

	//�e�摜�ƃT�C�Y�擾
	int temp = LoadGraph(s_filename);
	int w, h;
	GetGraphSize(temp, &w, &h);

	//�e�̏�����
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
	//�o�Ă��Ă���~�܂鎞�Ԃ܂ł̊ԂȂ牺�Ɉړ�
	if (in_time < g_count && g_count < stop_time) {
//		y += 2;
		y += 1;
		//�A�Ҏ��Ԃ��߂�����߂�B
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

	//�e����ŏ��ɕ`��
	for (int i = 0; i < ENEMY_SNUM; ++i) {
		if (shot[i].flag) {
			DrawGraph(shot[i].x, shot[i].y, shot[i].gh, true);
		}
	}

	if (!endflag) {

//		temp = count % 40 / 10;
		temp = count % 80 / 20;
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