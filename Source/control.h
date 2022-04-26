/*
* サイト名	：プログラミング入門サイト 〜bituse〜
* リンク	：https://bituse.info/
*/

#include "player.h"
#include "enemy.h"
#include "back.h"

class CONTROL{

	//プレイヤークラス
	PLAYER *player;

	//背景クラス
	BACK *back;

	//敵クラス
	ENEMY *enemy[ENEMY_NUM];

private:
	CONTROL();
	~CONTROL();
public:
	void All();
	void GetPlayerPosition(double *x,double *y);
	void GetEnemyPosition(int index,double *x,double *y);
	static CONTROL& GetInstance(){
		static CONTROL control;
		return control;
	}
};