/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/
#ifndef _BALL
#define _BALL

class BALL {
private:

	double	x;			//���W
	double	y;			//���W
	double	angle;		//�p�x
	int		gh;			//�O���t�B�b�N�n���h��
	int		raise;		//sin�g�Ɏg���p�x�̑�����
	bool	toggle;		//�ꎞ�t���O

private:
	void Move(
		double	px,
		double	py
	);
	void Draw();

public:
	BALL();
	void All(
		double	px,
		double	py
	);
	double GetPosition();

};

#endif
