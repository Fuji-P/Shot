/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/
#ifndef _BALL
#define _BALL

class BALL {
private:

	double	x;			//座標
	double	y;			//座標
	double	angle;		//角度
	int		gh;			//グラフィックハンドル
	int		raise;		//sin波に使う角度の増加量
	bool	toggle;		//一時フラグ

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
