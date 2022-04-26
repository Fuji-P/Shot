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
	int s_eshot;
	int s_pshot;

	//�T�E���h��炷���ǂ����̃t���O
	bool eshot_flag;
	bool pshot_flag;

private:
	CONTROL();
	~CONTROL();
	void SoundAll();
public:
	void All();
	void GetPlayerPosition(double *x,double *y);
	void GetEnemyPosition(int index,double *x,double *y);
	static CONTROL& GetInstance(){
		static CONTROL control;
		return control;
	}
};