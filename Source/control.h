/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

#include "player.h"
#include "enemy.h"
#include "back.h"

class CONTROL{
private:
	//�v���C���[�N���X�̃|�C���^
	PLAYER* player;

	//�G�l�~�[�N���X�̃|�C���^
	ENEMY* enemy[ENEMY_NUM];

	//�w�i�N���X
	BACK *back;

public:
	CONTROL();
	~CONTROL();
	void All();
};