/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

#ifndef _ENEMY
#define _ENEMY

class ENEMY {
private:

	E_SHOT shot[ENEMY_SNUM];		//�e�\����

	int		gh[3];		//�O���t�B�b�N�n���h��
	int		width;		//�摜�T�C�Y
	int		height;		//�摜�T�C�Y
	int		in_time;	//�o��
	int		stop_time;	//��~
	int		out_time;	//�A��
	int		shot_time;	//���˃^�C�~���O
	int		type;		//�G�̎��
	int		stype;		//�e�̎��
	int		m_pattern;	//�ړ��p�^�[��
	int		s_pattern;	//�V���b�g�p�^�[��
	int		count;		//�G���o�����Ă���̃J�E���g
	int		hp;			//HP
	int		item;		//�A�C�e��
	int		num;		//���˂����e��
	int		scount;		//�V���b�g���łĂ�悤�ɂȂ��Ă���̃J�E���g
	double	x;			//���W
	double	y;			//���W
	double	rad;		//���˒���̃��W�A��
	bool	deadflag;	//�G���Ńt���O
	bool	endflag;	//�G�N���X���Ńt���O
	bool	sflag;		//�V���b�g�����Ă�悤�ɂȂ������̃t���O
	bool	s_shot;

private:
	void Move();
	void Shot();
	void ShotGenerate();
	void ShotMove();
	void Draw();
	bool OutCheck();
	bool ShotOutCheck(
		int	i
	);

public:
	ENEMY(
		int		type,
		int		stype,
		int		m_pattern,
		int		s_pattern,
		int		in_time,
		int		stop_time,
		int		shot_time,
		int		out_time,
		int		x,
		int		y,
		int		speed,
		int		hp,
		int		item
	);
	bool All();
	bool GetShotSound();
	bool GetDeadFlag();
	bool GetGrazeFlag(
		int		index
	);
	bool GetShotPosition(
		int		index,
		double*	x,
		double*	y
	);
	void GetPosition(
		double* x,
		double* y
	);
	void SetGrazeFlag(
		int		index
	);
	void SetDeadFlag();
	void SetShotFlag(
		int		index,
		bool	flag
	);
	int GetShotType();
	int GetItem();
};

#endif