/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

#include "player.h"
#include "enemy.h"
#include "back.h"

class CONTROL{

	//�v���C���[�N���X
	PLAYER *player;

	//�w�i�N���X
	BACK *back;

	//�G�N���X
	ENEMY *enemy[ENEMY_NUM];

	//�T�E���h�n���h��
	int s_edead;
	int s_pdead;
	int s_eshot;
	int s_pshot;

	//�T�E���h��炷���ǂ����̃t���O
	bool eshot_flag;
	bool pshot_flag;
	bool edead_flag;
	bool pdead_flag;

private:
	CONTROL();
	~CONTROL();
	void SoundAll();
	void CollisionAll();
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
	void GetPlayerPosition(double *x,double *y);
	void GetEnemyPosition(int index,double *x,double *y);
	static CONTROL& GetInstance(){
		static CONTROL control;
		return control;
	}
};