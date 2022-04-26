/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
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