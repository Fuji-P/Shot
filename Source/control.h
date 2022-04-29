/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
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

	PLAYER* player;									//�v���C���[�N���X
	BACK* back;										//�w�i�N���X
	ENEMY* enemy[ENEMY_NUM];						//�G�N���X
	EFFECT_EDEAD* effect_edead[EFFECT_EDEADNUM];	//�G���ŃG�t�F�N�g�N���X
	GRAZE* graze[GRAZE_NUM];						//�O���C�Y�N���X
	SCORE* score;									//�w�i�N���X
	ITEM* item[ITEM_NUM];							//�A�C�e���N���X
	BOSS* boss;										//�{�X�N���X


	//�T�E���h�n���h��
	int		s_edead;
	int		s_pdead;
	int		s_eshot;
	int		s_pshot;
	int		s_graze;
	int		s_item;

	//�T�E���h��炷���ǂ����̃t���O
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