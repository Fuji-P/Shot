/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

class ENEMY {
private:
	double x, y;

	int gh[3];

	int width, height;

	int in_time, stop_time, out_time;

	int count;

	bool endflag;

public:
	bool All();

	void Move();

	void Draw();

	ENEMY();
};