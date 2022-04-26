/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include "player.h"
#include "back.h"

class CONTROL{
private:
	//プレイヤークラスのポインタ
	PLAYER *player;

	//背景クラス
	BACK *back;

public:
	CONTROL();
	~CONTROL();
	void All();
};