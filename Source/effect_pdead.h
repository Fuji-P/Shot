/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

class EFFECT_PDEAD {
private:

	PEFFECT_EXPAND expand[EFFECT_PDEADNUM];		//�p�[�e�B�N���G�t�F�N�g�\����

	int		gh[3];		//�O���t�B�b�N�n���h��
	int		width[3];	//�摜�̃T�C�Y
	int		height[3];	//�摜�̃T�C�Y
	int		alpha;		//�����x
	int		count;		//�J�E���g
	double	rota;		//��]������摜�p�̊p�x
	double	x;			//���W
	double	y;			//���W
	double	rate;		//�g�嗦
	bool	flag;		//���s�����ǂ����̃t���O

private:
	void Move();
	void Draw();

public:
	EFFECT_PDEAD();
	void All();
	void SetFlag(
		double	x, 
		double	y
	);
	bool GetFlag();
};