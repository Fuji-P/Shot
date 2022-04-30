/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

class BOSS {

	E_SHOT shot[BOSS_SHOTNUM];		//�e�\����

	int		gh_face[2];			//�O���t�B�b�N�n���h��
	int		gh_shot[3];			//�O���t�B�b�N�n���h��
	int		move_pattern;		//���݂̈ړ��p�^�[��
	int		shot_pattern;		//���݂̃V���b�g�p�^�[��
	double	angle;				//���v�p�x
	int		raise;				//������
	int		raise2;				//���ړ����̑�����
	int		waitcount;
	int		p3_state;
	int		count;				//�G���o�����Ă���̃J�E���g
	int		scount;				//�V���b�g���łĂ�悤�ɂȂ��Ă���̃J�E���g
	int		temp_scount;
	int		hp;
	double	x;					//���W
	double	y;					//���W
	double	prev_x;				//���W
	double	prev_y;				//���W
	double	movex;				//���̈ړ��ꏊ�܂ł̋���
	double	movey;				//���̈ړ��ꏊ�܂ł̋���
	bool	damageflag;			//�_���[�W�𕉂������ǂ����̃t���O
	static	bool	flag;				//�����Ă邩�ǂ����̃t���O
	bool	shotflag;
	bool	wait;
	bool	s_shot;

private:
	void Move();
	void Draw();
	void Appear();
	void MovePattern1();
	void MovePattern2();
	void MovePattern3();
	void MoveInit(
		double	bx,
		double	by,
		int		state
	);
	void Shot();
	int ShotSearch();
	bool ShotOutCheck(
		int	i
	);

public:
	BOSS();
	void All();
	void SetFlag(
		bool	flag
	);
	void SetShotFlag(
		int		index,
		bool	flag
	);
	void GetPosition(
		double* x,
		double* y
	);
	void SetGrazeFlag(
		int		index
	);
	bool GetGrazeFlag(
		int		index
	);
	bool GetShotPosition(
		int		index,
		double*	x,
		double*	y,
		int*	type
	);
	bool GetFlag();
	bool GetShotSound();
	int HpSet(
		int damage
	);

};