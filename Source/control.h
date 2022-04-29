/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include "player.h"
#include "enemy.h"
#include "back.h"
#include "effect_edead.h"
#include "graze.h"
#include "score.h"
#include "item.h"
#include "boss.h"

class CONTROL {

	PLAYER* player;									//プレイヤークラス
	BACK* back;										//背景クラス
	ENEMY* enemy[ENEMY_NUM];						//敵クラス
	EFFECT_EDEAD* effect_edead[EFFECT_EDEADNUM];	//敵消滅エフェクトクラス
	GRAZE* graze[GRAZE_NUM];						//グレイズクラス
	SCORE* score;									//背景クラス
	ITEM* item[ITEM_NUM];							//アイテムクラス
	BOSS* boss;										//ボスクラス


	//サウンドハンドル
	int		s_edead;
	int		s_pdead;
	int		s_eshot;
	int		s_pshot;
	int		s_graze;
	int		s_item;

	//サウンドを鳴らすかどうかのフラグ
	bool	eshot_flag;
	bool	pshot_flag;
	bool	edead_flag;
	bool	pdead_flag;
	bool	graze_flag;
	bool	item_flag;

private:
	CONTROL();
	~CONTROL();
	void LoadEnemyData(
		ENEMYDATA*	data
	);
	void EnemyDeadEffect(
		double	x,
		double	y
	);
	void SoundAll();
	void CollisionAll();
	void CollisionEnemy();
	void CollisionPlayer();
	void CollisionItem();
	bool CircleCollision(
		double	c1,
		double	c2,
		double	cx1,
		double	cx2,
		double	cy1,
		double	cy2
	);

public:
	void All();
	void GetPlayerPosition(
		double*	x,
		double*	y
	);
	bool GetEnemyPosition(
		int		index,
		double* x,
		double* y
	);
	static CONTROL& GetInstance(){
		static CONTROL control;
		return control;
	}
};