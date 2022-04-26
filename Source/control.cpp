/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

#include "pch.h"
#include "control.h"

CONTROL::CONTROL()
{
	//�v���C���[�N���X�̐���
	player = new PLAYER;

	//�G�l�~�[�N���X�̐���
	enemy = new ENEMY;

	back = new BACK;

}

CONTROL::~CONTROL()
{
	//�v���C���[�N���X�̉��
	delete player;
}

void CONTROL::All()
{
	//�`��̈���w��
	SetDrawArea(MARGIN, MARGIN, MARGIN + 380, MARGIN + 460);

	back->All();

	//�v���C���[�N���X��All�֐����s
	player->All();

	if (enemy != NULL) {
		if (enemy -> All()) {
			delete enemy;
			enemy = NULL;
		}
	}

	++g_count;
}