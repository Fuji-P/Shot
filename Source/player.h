/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#ifndef _PLAYER
#define _PLAYER

#include "effect_pdead.h"
#include "ball.h"

class PLAYER{

private:

	SHOT			shot[PSHOT_NUM];	//弾
	EFFECT_PDEAD*	effect_pdead;		//プレイヤー消滅エフェクトクラス
	BALL			ball;				//ボールクラス

	int		gh[12];		//グラフィックハンドル格納用配列
	int		width;		//画像幅
	int		height;		//画像幅
	int		xcount;		//横方向のカウント数。
	int		ycount;		//縦方向のカウント数。
	int		ix;			//添字用変数
	int		iy;			//添字用変数
	int		result;		//添字用変数
	int		life;		//プレイヤーのライフ
	int		power;		//プレイヤーのパワー
	int		dcount;		//ダメージ中のカウント
	int		count;		//カウント
	double	x;			//x座標
	double	y;			//y座標
	float	move;		//移動係数
	bool	damageflag;
	bool	endflag;
	bool	s_shot;		//サウンド関連フラグショット音

private:
	void Move();
	void Shot();
	void ShotGenerate();
	void ShotMove();
	void Draw();
	void DrawShot();
	void DrawPlayer();
	void Ball();
	void BallShotSet(
		int		index
	);
	int NearEnemySearch();
public:
	PLAYER();
	void All();
	void SetDamageFlag();
	void SetPower(
		int		p
	);
	void SetShotFlag(
		int		index,
		bool	flag
	);
	void GetPosition(
		double* x,
		double* y
	);
	bool GetShotPosition(
		int		index,
		double* x,
		double* y
	);
	bool GetShotSound();
	bool GetDamageFlag();
	int GetLife();
	int GetPower();

};

#endif