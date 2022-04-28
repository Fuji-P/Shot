/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

#define _USE_MATH_DEFINES

#include <windows.h>
#include <math.h>
#include <time.h>

//�v���C���[�̕����X�s�[�h
#define PLAYER_SPEED 4

#define PLAYER_INITX 180
#define PLAYER_INITY 400

//���b�Z�[�W�{�b�N�X
#define MSG(m) {\
	MessageBox(NULL,m, "���b�Z�[�W", MB_OK);}

//�㉺���E�̗]��
#define MARGIN 10

//�w�i�X�N���[���X�s�[�h
#define SCROLL_SPEED 1

//�ő�e��
#define PSHOT_NUM 10

//�e�̑��x
#define PSHOT_SPEED 7

#define ENEMY_SNUM 25

#define ENEMY_NUM 13

#define ENEMY_ANUM 13

#define EFFECT_EDEADNUM 20

#define EFFECT_PDEADNUM 20

#define GRAZE_NUM 25

//�����蔻��p���a��`
#define PLAYER_COLLISION 4
#define ENEMY1_COLLISION 14

#define PSHOT_COLLISION 3
#define ESHOT0_COLLISION 10
#define ESHOT1_COLLISION 3
#define ESHOT2_COLLISION 2

#define GRAZE_COLLISION 10

#define SCORE_X 390

//�A�C�e���̓����蔻��p���a
#define ITEM_COLLISION 16

//�A�C�e���̑���
#define ITEM_NUM 30

//extern�錾���Ăǂ�����ł��A�N�Z�X�ł���悤�ɂ���
//key�z��
extern char key[256];

//�Q�[�����J�n���Ă��牽���[�v�����̂�
extern int g_count;

struct SHOT {
	bool	flag;			//�e�����˒����ǂ���
	double	x;				//x���W
	double	y;				//y���W
	int		gh;				//�O���t�B�b�N�n���h��
	int		width, height;	//�摜�̕��ƍ���
};

struct E_SHOT {
	bool	flag;			//�e�����˒����ǂ���
	double	x;				//x���W
	double	y;				//y���W
	double	rad;			//�p�x(���W�A��)
	int		gh;				//�O���t�B�b�N�n���h��
	int		width, height;	//�摜�̕��ƍ���
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
	double	x, y;
	double	rad;
	int		speed;
};