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

	//�����Ă邩�ǂ����̃t���O
	bool life;

	//�e
	SHOT shot[PSHOT_NUM];

	//�J�E���g
	int count;

private:
	void Move();
	void Draw();
	void Shot();

public:
	PLAYER();
	void All();

};