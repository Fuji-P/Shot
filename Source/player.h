/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

#ifndef _PLAYER
#define _PLAYER

#include "effect_pdead.h"
#include "ball.h"

class PLAYER{

private:

	SHOT			shot[PSHOT_NUM];	//�e
	EFFECT_PDEAD*	effect_pdead;		//�v���C���[���ŃG�t�F�N�g�N���X
	BALL			ball;				//�{�[���N���X

	int		gh[12];		//�O���t�B�b�N�n���h���i�[�p�z��
	int		width;		//�摜��
	int		height;		//�摜��
	int		xcount;		//�������̃J�E���g���B
	int		ycount;		//�c�����̃J�E���g���B
	int		ix;			//�Y���p�ϐ�
	int		iy;			//�Y���p�ϐ�
	int		result;		//�Y���p�ϐ�
	int		life;		//�v���C���[�̃��C�t
	int		power;		//�v���C���[�̃p���[
	int		dcount;		//�_���[�W���̃J�E���g
	int		count;		//�J�E���g
	double	x;			//x���W
	double	y;			//y���W
	float	move;		//�ړ��W��
	bool	damageflag;
	bool	endflag;
	bool	s_shot;		//�T�E���h�֘A�t���O�V���b�g��

private:
	void Move();
	void Shot();
	void ShotGenerate();
	void ShotMove();
	void Draw();
	void DrawShot();
	void DrawPlayer();
	void Ball();
	void BallShotSet(
		int		index
	);
	int NearEnemySearch();
public:
	PLAYER();
	void All();
	void SetDamageFlag();
	void SetPower(
		int		p
	);
	void SetShotFlag(
		int		index,
		bool	flag
	);
	void GetPosition(
		double* x,
		double* y
	);
	bool GetShotPosition(
		int		index,
		double* x,
		double* y
	);
	bool GetShotSound();
	bool GetDamageFlag();
	int GetLife();
	int GetPower();

};

#endif