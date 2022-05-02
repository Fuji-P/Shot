/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

class BOSS {

	E_SHOT shot[BOSS_SHOTNUM];		//弾構造体

			int		gh_face[2];			//グラフィックハンドル
			int		gh_shot[3];			//グラフィックハンドル
			int		move_pattern;		//現在の移動パターン
			int		shot_pattern;		//現在のショットパターン
			int		prev_move_pattern;	//現在の移動パターン
			int		prev_shot_pattern;	//現在のショットパターン
			int		raise;				//増加量
			int		raise2;				//横移動時の増加量
			int		waitcount;
			int		p3_state;
			int		count;				//敵が出現してからのカウント
			int		scount;				//ショットが打てるようになってからのカウント
			int		temp_scount;
			int		hp;
			int		prev_hp;
			double	x;					//座標
			double	y;					//座標
			double	prev_x;				//座標
			double	prev_y;				//座標
			double	movex;				//次の移動場所までの距離
			double	movey;				//次の移動場所までの距離
			double	angle;				//合計角度
	static	bool	flag;				//生きてるかどうかのフラグ
			bool	damageflag;			//ダメージを負ったかどうかのフラグ
			bool	shotflag;
			bool	wait;
			bool	s_shot;
			bool	no_damage;			//ダメージを負わないフラグ


private:
	void Move();
	void Appear();
	void MoveToDefault();
	void MovePattern1();
	void MovePattern2();
	void MovePattern3();
	void MoveInit(
		double	bx,
		double	by,
		int		state
	);
	void SetMovePattern(
		int		pattern
	);
	void SetShotPattern(
		int		pattern
	);
	void Draw();
	void Shot();
	void ShotPattern0(
		double	trad
	);
	void ShotPattern1(
		double	px,
		double	py
	);
	void ShotPattern2(
		double	px,
		double	py,
		double	trad
	);
	void ShotPattern3(
		double	px,
		double	py
	);
	void ShotMove();
	int ShotSearch();
	bool ShotOutCheck(
		int		i
	);

public:
	BOSS();
	void All();
	void SetDamageSetting();
	void SetFlag(
		bool	flag
	);
	void SetShotFlag(
		int		index,
		bool	flag
	);
	void GetPosition(
		double* x,
		double* y
	);
	void SetGrazeFlag(
		int		index
	);
	bool GetGrazeFlag(
		int		index
	);
	bool GetShotPosition(
		int		index,
		double*	x,
		double*	y,
		int*	type
	);
	bool GetFlag();
	bool GetShotSound();
	bool GetNodamageFlag();
	int HpSet(
		int		damage
	);
	int GetPrevHp();

};