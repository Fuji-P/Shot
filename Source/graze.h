/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

class GRAZE {
private:

	static	int		gh;		//�O���t�B�b�N�n���h��
			int		alpha;	//�A���t�@�l
			int		count;	//�J�E���g
			double	x;		//���W
			double	y;		//���W
			double	rad;	//�p�x
			double	rate;	//�g�嗦
			bool	flag;	//���s�����ǂ����̃t���O

private:
	void Move();
	void Draw();
public:
	GRAZE();
	void All();
	void SetFlag(
		double	x,
		double	y
	);
	bool GetFlag();
};