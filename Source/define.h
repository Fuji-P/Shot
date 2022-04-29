/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#define _USE_MATH_DEFINES

#include <windows.h>
#include <math.h>
#include <time.h>

//メッセージボックス
#define MSG(m) {\
	MessageBox(NULL,m, "メッセージ", MB_OK);}

#define PLAYER_SPEED		4		//プレイヤーの歩くスピード
#define PLAYER_INITX		180
#define PLAYER_INITY		400
#define MARGIN				10		//上下左右の余白
#define SCROLL_SPEED		1		//背景スクロールスピード
#define PSHOT_NUM			50		//プレイヤーの最大弾数
#define PSHOT_SPEED			7		//弾の速度
#define ENEMY_NUM			13		//最大敵数
#define ENEMY_SNUM			25		//敵の最大弾数
#define ENEMY_ANUM			13
#define EFFECT_EDEADNUM		20
#define EFFECT_PDEADNUM		20
#define GRAZE_NUM			25
#define ITEM_NUM			30		//アイテムの総数
#define SCORE_X				390
#define BALL_SHAKE			15
#define BALL_INITX			50
#define BALL_INITY			30

//当たり判定用半径定義
#define PLAYER_COLLISION	4
#define ENEMY1_COLLISION	14
#define PSHOT_COLLISION		3
#define ESHOT0_COLLISION	10
#define ESHOT1_COLLISION	3
#define ESHOT2_COLLISION	2
#define GRAZE_COLLISION		10
#define ITEM_COLLISION		16		//アイテムの当たり判定用半径

//extern宣言してどこからでもアクセスできるようにする
extern char	key[256];		//key配列
extern int	g_count;		//ゲームが開始してから何ループしたのか

struct SHOT {
	bool	flag;			//弾が発射中かどうか
	double	x;				//x座標
	double	y;				//y座標
	int		gh;				//グラフィックハンドル
	int		width;			//画像の幅
	int		height;			//画像の高さ
	double	rad;			//角度

};

struct E_SHOT {
	bool	flag;			//弾が発射中かどうか
	double	x;				//x座標
	double	y;				//y座標
	double	rad;			//角度(ラジアン)
	int		gh;				//グラフィックハンドル
	int		width;			//画像の幅
	int		height;			//画像の高さ
	int		pattern;		//ショットパターン
	int		speed;			//弾スピード
	bool	gflag;			//グレイズ判定用フラグ
};

struct ENEMYDATA {
	int		type;			//敵種類
	int		stype;			//弾種類
	int		m_pattern;		//移動パターン
	int		s_pattern;		//発射パターン
	int		in_time;		//出現時間
	int		stop_time;		//停止時間
	int		shot_time;		//弾発射時間
	int		out_time;		//帰還時間
	int		x;				//x座標
	int		y;				//y座標
	int		speed;			//弾スピード
	int		hp;				//HP
	int		item;			//アイテム
};

struct PEFFECT_EXPAND {
	double	x;
	double	y;
	double	rad;
	int		speed;
};