/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include "player.h"
#include "enemy.h"
#include "back.h"
#include "effect_edead.h"
#include "graze.h"

class CONTROL{

	//プレイヤークラス
	PLAYER *player;

	//背景クラス
	BACK *back;

	//敵クラス
	ENEMY *enemy[ENEMY_NUM];

	//敵消滅エフェクトクラス
	EFFECT_EDEAD *effect_edead[EFFECT_EDEADNUM];

	//グレイズクラス
	GRAZE *graze[GRAZE_NUM];

	//サウンドハンドル
	int s_edead;
	int s_pdead;
	int s_eshot;
	int s_pshot;
	int s_graze;

	//サウンドを鳴らすかどうかのフラグ
	bool eshot_flag;
	bool pshot_flag;
	bool edead_flag;
	bool pdead_flag;
	bool graze_flag;

private:
	CONTROL();
	~CONTROL();
	void LoadEnemyData(
		ENEMYDATA *data
	);
	void EnemyDeadEffect(
		double x,
		double y
	);
	void SoundAll();
//	void CollisionAll();
	void CollisionEnemy();
	void CollisionPlayer();
	bool CircleCollision(
		double c1,
		double c2,
		double cx1,
		double cx2,
		double cy1,
		double cy2
	);
public:
	void All();
	void GetPlayerPosition(
		double *x,
		double *y
	);
	void GetEnemyPosition(
		int		index,
		double	*x,
		double	*y
	);
	static CONTROL& GetInstance(){
		static CONTROL control;
		return control;
	}
};