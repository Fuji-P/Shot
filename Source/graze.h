/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

class GRAZE {
private:

	static	int		gh;		//グラフィックハンドル
			int		alpha;	//アルファ値
			int		count;	//カウント
			double	x;		//座標
			double	y;		//座標
			double	rad;	//角度
			double	rate;	//拡大率
			bool	flag;	//実行中かどうかのフラグ

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