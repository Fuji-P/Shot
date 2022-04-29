/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

#define _USE_MATH_DEFINES

#include <windows.h>
#include <math.h>
#include <time.h>

//���b�Z�[�W�{�b�N�X
#define MSG(m) {\
	MessageBox(NULL,m, "���b�Z�[�W", MB_OK);}

#define PLAYER_SPEED		4		//�v���C���[�̕����X�s�[�h
#define PLAYER_INITX		180
#define PLAYER_INITY		400
#define MARGIN				10		//�㉺���E�̗]��
#define SCROLL_SPEED		1		//�w�i�X�N���[���X�s�[�h
#define PSHOT_NUM			50		//�v���C���[�̍ő�e��
#define PSHOT_SPEED			7		//�e�̑��x
#define ENEMY_NUM			13		//�ő�G��
#define ENEMY_SNUM			25		//�G�̍ő�e��
#define ENEMY_ANUM			13
#define EFFECT_EDEADNUM		20
#define EFFECT_PDEADNUM		20
#define GRAZE_NUM			25
#define ITEM_NUM			30		//�A�C�e���̑���
#define SCORE_X				390
#define BALL_SHAKE			15
#define BALL_INITX			50
#define BALL_INITY			30

//�����蔻��p���a��`
#define PLAYER_COLLISION	4
#define ENEMY1_COLLISION	14
#define PSHOT_COLLISION		3
#define ESHOT0_COLLISION	10
#define ESHOT1_COLLISION	3
#define ESHOT2_COLLISION	2
#define GRAZE_COLLISION		10
#define ITEM_COLLISION		16		//�A�C�e���̓����蔻��p���a

//extern�錾���Ăǂ�����ł��A�N�Z�X�ł���悤�ɂ���
extern char	key[256];		//key�z��
extern int	g_count;		//�Q�[�����J�n���Ă��牽���[�v�����̂�

struct SHOT {
	bool	flag;			//�e�����˒����ǂ���
	double	x;				//x���W
	double	y;				//y���W
	int		gh;				//�O���t�B�b�N�n���h��
	int		width;			//�摜�̕�
	int		height;			//�摜�̍���
	double	rad;			//�p�x

};

struct E_SHOT {
	bool	flag;			//�e�����˒����ǂ���
	double	x;				//x���W
	double	y;				//y���W
	double	rad;			//�p�x(���W�A��)
	int		gh;				//�O���t�B�b�N�n���h��
	int		width;			//�摜�̕�
	int		height;			//�摜�̍���
	int		pattern;		//�V���b�g�p�^�[��
	int		speed;			//�e�X�s�[�h
	bool	gflag;			//�O���C�Y����p�t���O
};

struct ENEMYDATA {
	int		type;			//�G���
	int		stype;			//�e���
	int		m_pattern;		//�ړ��p�^�[��
	int		s_pattern;		//���˃p�^�[��
	int		in_time;		//�o������
	int		stop_time;		//��~����
	int		shot_time;		//�e���ˎ���
	int		out_time;		//�A�Ҏ���
	int		x;				//x���W
	int		y;				//y���W
	int		speed;			//�e�X�s�[�h
	int		hp;				//HP
	int		item;			//�A�C�e��
};

struct PEFFECT_EXPAND {
	double	x;
	double	y;
	double	rad;
	int		speed;
};