/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

class ENEMY {
private:
	//座標とグラフィックハンドル
	double x, y;
	int gh[3];

	//画像サイズ
	int width, height;

	//出現、停止、帰還、発射タイミング
	int in_time, stop_time, out_time, shot_time;

	//敵の種類
	int type;
	//弾の種類
	int stype;
	//移動パターン
	int m_pattern;
	//ショットパターン
	int s_pattern;

	//敵が出現してからのカウント
	int count;


	//敵消滅フラグ
	bool deadflag;
	//敵クラス消滅フラグ
	bool endflag;

	//弾構造体
	E_SHOT shot[ENEMY_SNUM];
	//ショットが撃てるようになったかのフラグ
	bool sflag;
	//ショットが打てるようになってからのカウント
	int scount;

public:
	bool All();

	void Move();

	void Shot();

	void Draw();

	ENEMY(
			const char* 	c_filename,
			int				type,
			int				m_pattern,
			int				x,
			int				y,
			int				in_time,
			int				stop_time,
			int				shot_time,
			int				out_time,
			const char*		s_filename,
			int				stype,
			int				s_pattern,
			int				speed
		);
};