/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

class BACK {
private:

	int		gh;		//グラフィックハンドル
	double	x;		//座標
	double	y;		//座標

private:
	void Move();
	void Draw();

public:
	BACK();
	void All();
};