/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#ifndef _ENEMY
#define _ENEMY

class ENEMY {
private:

	E_SHOT shot[ENEMY_SNUM];		//弾構造体

	int		gh[3];		//グラフィックハンドル
	int		width;		//画像サイズ
	int		height;		//画像サイズ
	int		in_time;	//出現
	int		stop_time;	//停止
	int		out_time;	//帰還
	int		shot_time;	//発射タイミング
	int		type;		//敵の種類
	int		stype;		//弾の種類
	int		m_pattern;	//移動パターン
	int		s_pattern;	//ショットパターン
	int		count;		//敵が出現してからのカウント
	int		hp;			//HP
	int		item;		//アイテム
	int		num;		//発射した弾数
	int		scount;		//ショットが打てるようになってからのカウント
	double	x;			//座標
	double	y;			//座標
	double	rad;		//発射直後のラジアン
	bool	deadflag;	//敵消滅フラグ
	bool	endflag;	//敵クラス消滅フラグ
	bool	sflag;		//ショットが撃てるようになったかのフラグ
	bool	s_shot;

private:
	void Move();
	void Shot();
	void ShotGenerate();
	void ShotMove();
	void Draw();
	bool OutCheck();
	bool ShotOutCheck(
		int	i
	);

public:
	ENEMY(
		int		type,
		int		stype,
		int		m_pattern,
		int		s_pattern,
		int		in_time,
		int		stop_time,
		int		shot_time,
		int		out_time,
		int		x,
		int		y,
		int		speed,
		int		hp,
		int		item
	);
	bool All();
	bool GetShotSound();
	bool GetDeadFlag();
	bool GetGrazeFlag(
		int		index
	);
	bool GetShotPosition(
		int		index,
		double*	x,
		double*	y
	);
	void GetPosition(
		double* x,
		double* y
	);
	void SetGrazeFlag(
		int		index
	);
	void SetDeadFlag();
	void SetShotFlag(
		int		index,
		bool	flag
	);
	int GetShotType();
	int GetItem();
};

#endif