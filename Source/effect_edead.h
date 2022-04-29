/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

class EFFECT_EDEAD {
private:

	static	int		gh[3];		//グラフィックハンドル
			int		alpha;		//透明度
			int		index;		//どの画像を使うかの添字
			int		count;		//カウント
			double	x;			//座標
			double	y;			//座標
			double	rad;		//エフェクト画像の角度
			double	rate;		//拡大率
			bool	flag;		//実行中かどうかのフラグ

private:
	void Move();
	void Draw();

public:
	EFFECT_EDEAD();
	void All();
	void SetFlag(
		double	x,
		double	y
	);
	bool GetFlag();
};