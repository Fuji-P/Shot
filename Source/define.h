/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

#include <windows.h>

//�v���C���[�̕����X�s�[�h
#define PLAYER_SPEED 4

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

//extern�錾����key�z��ɂǂ�����ł��A�N�Z�X�ł���悤�ɂ���
extern char key[256];

struct SHOT {
	bool	flag;			//�e�����˒����ǂ���
	double	x;				//x���W
	double	y;				//y���W
	int		gh;				//�O���t�B�b�N�n���h��
	int		width, height;	//�摜�̕��ƍ���
};
