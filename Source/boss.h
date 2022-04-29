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
	int		angle;				//���v�p�x
	int		raise;				//������
	int		raise2;				//���ړ����̑�����
	int		waitcount;
	int		p3_state;
	double	x;					//���W
	double	y;					//���W
	double	prev_x;				//���W
	double	prev_y;				//���W
	double	movex;				//���̈ړ��ꏊ�܂ł̋���
	double	movey;				//���̈ړ��ꏊ�܂ł̋���
	bool	damageflag;			//�_���[�W�𕉂������ǂ����̃t���O
	bool	flag;				//�����Ă邩�ǂ����̃t���O
	bool	wait;

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
public:
	BOSS();
	void All();
	void SetDamageFlag();
	void SetFlag(
		bool	f
	);
	bool GetFlag();
};