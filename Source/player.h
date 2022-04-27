/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

class PLAYER{

private:
	//x座標,y座標
	double x,y;

	//画像幅
	int width,height;

	//グラフィックハンドル格納用配列
	int gh[12];

	//移動係数
	float move;

	//横方向と縦方向のカウント数。
	int xcount,ycount;

	//添字用変数
	int ix,iy,result;

	//プレイヤーのライフ
	int life;
	bool damageflag;
	bool endflag;
	//ダメージ中のカウント
	int dcount;

	//弾
	SHOT shot[PSHOT_NUM];

	//カウント
	int count;

	//サウンド関連フラグ
	//ショット音
	bool s_shot;

private:
	void Move();
	void Draw();
//	void Shot();
	void ShotGenerate();
	void ShotMove();

public:
	PLAYER();
	bool GetDamageFlag();
	bool GetShotSound();
	bool GetShotPosition(
		int		index,
		double* x,
		double* y
	);
	void GetPosition(
		double* x,
		double* y
	);
	void SetDamageFlag();
	void SetShotFlag(
		int		index,
		bool	flag
	);
	void All();
};