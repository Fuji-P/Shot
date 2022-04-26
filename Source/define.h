/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include <windows.h>

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

//extern宣言してkey配列にどこからでもアクセスできるようにする
extern char key[256];

struct SHOT {
	bool	flag;			//弾が発射中かどうか
	double	x;				//x座標
	double	y;				//y座標
	int		gh;				//グラフィックハンドル
	int		width, height;	//画像の幅と高さ
};
