/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

class ENEMY {
private:
	//���W�ƃO���t�B�b�N�n���h��
	double x, y;
	int gh[3];

	//�摜�T�C�Y
	int width, height;

	//�o���A��~�A�A�ҁA���˃^�C�~���O
	int in_time, stop_time, out_time, shot_time;

	//�G�̎��
	int type;
	//�e�̎��
	int stype;
	//�ړ��p�^�[��
	int m_pattern;
	//�V���b�g�p�^�[��
	int s_pattern;

	//�G���o�����Ă���̃J�E���g
	int count;


	//�G���Ńt���O
	bool deadflag;
	//�G�N���X���Ńt���O
	bool endflag;

	//�e�\����
	E_SHOT shot[ENEMY_SNUM];
	//�V���b�g�����Ă�悤�ɂȂ������̃t���O
	bool sflag;
	//�V���b�g���łĂ�悤�ɂȂ��Ă���̃J�E���g
	int scount;

public:
	bool All();

	void Move();

	void Shot();

	void Draw();

	ENEMY(
			const char* 	c_filename,
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
		);
};