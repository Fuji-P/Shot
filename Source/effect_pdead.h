/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

class EFFECT_PDEAD {
private:

	PEFFECT_EXPAND expand[EFFECT_PDEADNUM];		//パーティクルエフェクト構造体

	int		gh[3];		//グラフィックハンドル
	int		width[3];	//画像のサイズ
	int		height[3];	//画像のサイズ
	int		alpha;		//透明度
	int		count;		//カウント
	double	rota;		//回転させる画像用の角度
	double	x;			//座標
	double	y;			//座標
	double	rate;		//拡大率
	bool	flag;		//実行中かどうかのフラグ

private:
	void Move();
	void Draw();

public:
	EFFECT_PDEAD();
	void All();
	void SetFlag(
		double	x, 
		double	y
	);
	bool GetFlag();
};