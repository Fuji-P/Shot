/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#define _USE_MATH_DEFINES

#include <windows.h>
#include <math.h>
#include <time.h>

//プレイヤーの歩くスピード
#define PLAYER_SPEED 4

//メッセージボックス
#define MSG(m) {\
	MessageBox(NULL,m, "メッセージ", MB_OK);}

//上下左右の余白
#define MARGIN 10

//背景スクロールスピード
#define SCROLL_SPEED 1

//最大弾数
#define PSHOT_NUM 10

//弾の速度
#define PSHOT_SPEED 7

#define ENEMY_SNUM 25

#define ENEMY_NUM 4

#define ENEMY_ANUM 13

//extern宣言してどこからでもアクセスできるようにする
//key配列
extern char key[256];

//ゲームが開始してから何ループしたのか
extern int g_count;

struct SHOT {
	bool	flag;			//弾が発射中かどうか
	double	x;				//x座標
	double	y;				//y座標
	int		gh;				//グラフィックハンドル
	int		width, height;	//画像の幅と高さ
};

struct E_SHOT {
	bool	flag;			//弾が発射中かどうか
	double	x;				//x座標
	double	y;				//y座標
	double	rad;			//角度(ラジアン)
	int		gh;				//グラフィックハンドル
	int		width, height;	//画像の幅と高さ
	int		pattern;		//ショットパターン
	int		speed;			//弾スピード
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