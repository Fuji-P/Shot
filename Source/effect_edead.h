/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

class EFFECT_EDEAD {
private:

	static	int		gh[3];		//�O���t�B�b�N�n���h��
			int		alpha;		//�����x
			int		index;		//�ǂ̉摜���g�����̓Y��
			int		count;		//�J�E���g
			double	x;			//���W
			double	y;			//���W
			double	rad;		//�G�t�F�N�g�摜�̊p�x
			double	rate;		//�g�嗦
			bool	flag;		//���s�����ǂ����̃t���O

private:
	void Move();
	void Draw();

public:
	EFFECT_EDEAD();
	void All();
	void SetFlag(
		double	x,
		double	y
	);
	bool GetFlag();
};