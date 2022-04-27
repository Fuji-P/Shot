/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

class PLAYER{

private:
	//x���W,y���W
	double x,y;

	//�摜��
	int width,height;

	//�O���t�B�b�N�n���h���i�[�p�z��
	int gh[12];

	//�ړ��W��
	float move;

	//�������Əc�����̃J�E���g���B
	int xcount,ycount;

	//�Y���p�ϐ�
	int ix,iy,result;

	//�v���C���[�̃��C�t
	int life;
	bool damageflag;
	bool endflag;
	//�_���[�W���̃J�E���g
	int dcount;

	//�e
	SHOT shot[PSHOT_NUM];

	//�J�E���g
	int count;

	//�T�E���h�֘A�t���O
	//�V���b�g��
	bool s_shot;

private:
	void Move();
	void Draw();
//	void Shot();
	void ShotGenerate();
	void ShotMove();

public:
	PLAYER();
	bool GetDamageFlag();
	bool GetShotSound();
	bool GetShotPosition(
		int		index,
		double* x,
		double* y
	);
	void GetPosition(
		double* x,
		double* y
	);
	void SetDamageFlag();
	void SetShotFlag(
		int		index,
		bool	flag
	);
	void All();
};