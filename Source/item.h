/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

class ITEM {
private:

	static	int		gh[2];		//�O���t�B�b�N�n���h��
	static	int		ghs[2];		//�O���t�B�b�N�n���h��
			int		type;		//�ǂ����̃A�C�e�����������ϐ�
			int		count;		//�J�E���g
			double	x;			//���W
			double	y;			//���W
			double	prev_y;
			double	rad;		//��]�p�x
			bool	fall_flag;	//�A�C�e�����������n�߂�t���O
			bool	flag;		//�o�������ǂ����̃t���O

private:
	void Move();
	void Draw();

public:
	ITEM();
	void All();
	void SetFlag(double x, double y, int type);
	void Delete();
	void GetPosition(double* x, double* y);
	int  GetType();
	bool GetFlag();
};
