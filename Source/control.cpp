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

	//�w�i�N���X�̐���
	back = new BACK;

	//�G�t�F�N�g�N���X�̃C���X�^���X����
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		effect_edead[i] = new EFFECT_EDEAD;
	}

	//�O���C�Y�N���X�̃C���X�^���X����
	for (int i = 0; i < GRAZE_NUM; ++i) {
		graze[i] = new GRAZE;
	}

	//�X�R�A�N���X�̐���
	score = new SCORE;

	//�A�C�e���N���X�̃C���X�^���X����
	for (int i = 0; i < ITEM_NUM; ++i) {
		item[i] = new ITEM;
	}

	//�G�l�~�[�f�[�^�̓ǂݍ���
	ENEMYDATA data[ENEMY_NUM];

	LoadEnemyData(data);

	//�G�N���X����
	for (int i = 0; i < ENEMY_NUM; ++i) {
		enemy[i] = new ENEMY(
							data[i].type,
							data[i].stype,
							data[i].m_pattern,
							data[i].s_pattern,
							data[i].in_time,
							data[i].stop_time,
							data[i].shot_time,
							data[i].out_time,
							data[i].x,
							data[i].y,
							data[i].speed,
							data[i].hp,
							data[i].item
							);
	}

	//�T�E���h�t�@�C���ǂݍ���
	s_edead = LoadSoundMem("enemydead.wav");
	s_pdead = LoadSoundMem("playdead.wav");
	s_eshot = LoadSoundMem("enemyshot.wav");
	s_pshot = LoadSoundMem("playershot.wav");
	s_graze = LoadSoundMem("graze.wav");
	s_item = LoadSoundMem("item.wav");

	edead_flag = false;
	pdead_flag = false;
	eshot_flag = false;
	pshot_flag = false;
	graze_flag = false;
	item_flag = false;
}

CONTROL::~CONTROL()
{
	//�v���C���[�N���X�̉��
	delete player;

	//�w�i�N���X�̉��
	delete back;

	//�G�l�~�[�N���X�̉��
	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] != NULL) {
			delete enemy[i];
		}
	}

	//�O���C�Y�N���X�̉��
	for (int i = 0; i < GRAZE_NUM; ++i) {
		if (graze[i] != NULL) {
			delete graze[i];
		}
	}

	//�G���ŃG�t�F�N�g�N���X�̉��
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		if (effect_edead[i] != NULL) {
			delete effect_edead[i];
		}
	}

	//�X�R�A�N���X�̉��
	delete score;

	//�A�C�e���N���X�̉��
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (item[i] != NULL) {
			delete item[i];
		}
	}
}

void CONTROL::LoadEnemyData(
	ENEMYDATA *data
)
{
	FILE* fp;
	char buf[200] = "";
	int chr;
	int col = 1;
	int row = 0;

	memset(buf, 0, sizeof(buf));
	fp = fopen("enemydata.csv", "r");

	//�w�b�_�ǂݔ�΂�
	while (fgetc(fp) != '\n');

	while (1) {

		while (1) {

			chr = fgetc(fp);

			//�����Ȃ烋�[�v�𔲂���B
			if (chr == EOF) {
				return;
			}

			//�J���}�����s�łȂ���΁A�����Ƃ��ĂȂ���
			if (chr != ',' && chr != '\n') {
				strcat(buf, (const char*)&chr);
			}
			//�J���}�����s�Ȃ烋�[�v������B
			else {
				break;
			}
		}
		//�����ɗ����Ƃ������Ƃ́A1�Z�����̕����񂪏o���オ�����Ƃ�������
		switch (col) {
			//1��ڂ͓G��ނ�\���Batoi�֐��Ő��l�Ƃ��đ���B
		case 1:
			data[row].type = atoi(buf);
			break;
			//2��ڂ͒e��ށB�ȍ~�ȗ��B
		case 2:
			data[row].stype = atoi(buf);
			break;
		case 3:
			data[row].m_pattern = atoi(buf);
			break;
		case 4:
			data[row].s_pattern = atoi(buf);
			break;
		case 5:
			data[row].in_time = atoi(buf);
			break;
		case 6:
			data[row].stop_time = atoi(buf);
			break;
		case 7:
			data[row].shot_time = atoi(buf);
			break;
		case 8:
			data[row].out_time = atoi(buf);
			break;
		case 9:
			data[row].x = atoi(buf);
			break;
		case 10:
			data[row].y = atoi(buf);
			break;
		case 11:
			data[row].speed = atoi(buf);
			break;
		case 12:
			data[row].hp = atoi(buf);
			break;
		case 13:
			data[row].item = atoi(buf);
			break;
		}
		//�o�b�t�@��������
		memset(buf, 0, sizeof(buf));
		//�񐔂𑫂�
		++col;

		//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
		if (chr == '\n') {
			col = 1;
			++row;
		}
	}
}

void CONTROL::All()
{

	//�T�E���h�t���O��������
	edead_flag = false;
	pdead_flag = false;
	eshot_flag = false;
	pshot_flag = false;
	graze_flag = false;
	item_flag = false;

	//�w�i�N���X��All�֐����s
	back->All();

	//�`��̈���w��
	SetDrawArea(MARGIN, MARGIN, MARGIN + 380, MARGIN + 460);

	//�v���C���[�N���X��All�֐����s
	player->All();

	//�v���C���[�V���b�g�T�E���h�t���O�`�F�b�N
	if (player->GetShotSound()) {
		pshot_flag = true;
	}

	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] == NULL) {
			continue;
		}
		//�G�V���b�g�T�E���h�t���O�`�F�b�N
		if (enemy[i]->GetShotSound()) {
			eshot_flag = true;
		}
		if (enemy[i]->All()) {
			delete enemy[i];
			enemy[i] = NULL;
		}
	}

	//�����蔻��
	CollisionAll();

	//�O���C�Y�`��
	for (int i = 0; i < GRAZE_NUM; ++i) {
		if (graze[i]->GetFlag()) {
			graze[i]->All();
		}
	}

	//�G���ŃG�t�F�N�g
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		if (effect_edead[i]->GetFlag()) {
			effect_edead[i]->All();
		}
	}

	//�A�C�e���`��
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (item[i]->GetFlag()) {
			item[i]->All();
		}
	}

	//�`��̈���w��
	SetDrawArea(0, 0, 640, 480);

	//�X�R�A�`��
	score->All();

	SoundAll();
	++g_count;
}

void CONTROL::EnemyDeadEffect(
	double x,
	double y
)
{
	//�G�t�F�N�g�Z�b�g
	for (int z = 0; z < EFFECT_EDEADNUM; ++z) {
		if (!effect_edead[z]->GetFlag()) {
			effect_edead[z]->SetFlag(x, y);
			break;
		}
	}
}

void CONTROL::SoundAll()
{

	if (pshot_flag) {
		PlaySoundMem(s_pshot, DX_PLAYTYPE_BACK);
	}

	if (eshot_flag) {
		PlaySoundMem(s_eshot, DX_PLAYTYPE_BACK);
	}

	if (edead_flag) {
		PlaySoundMem(s_edead, DX_PLAYTYPE_BACK);
	}

	if (pdead_flag) {
		PlaySoundMem(s_pdead, DX_PLAYTYPE_BACK);
	}

	if (graze_flag) {
		PlaySoundMem(s_graze, DX_PLAYTYPE_BACK);
	}
	
	if (item_flag) {
		PlaySoundMem(s_item, DX_PLAYTYPE_BACK);
	}

}

void CONTROL::CollisionAll()
{
	CollisionEnemy();

	//�v���C���[�������Ă��
	if (!player->GetDamageFlag()) {
		CollisionPlayer();
		CollisionItem();
	}

	//���C�t�͖���擾
	score->SetScore(LIFE_SCORE, player->GetLife());
}

void CONTROL::CollisionEnemy()
{
	double px, py;
	double ex, ey;

	//����L�����̒e�ƓG�Ƃ̓����蔻��
	for (int i = 0; i < PSHOT_NUM; ++i) {
		if (!player->GetShotPosition(i, &px, &py)) {
			continue;
		}
		for (int s = 0; s < ENEMY_NUM; ++s) {
			//�G�N���X�̃|�C���^��NULL����Ȃ��A����deadflag��false(����łȂ����A�҂��ĂȂ�)
			if (enemy[s] == NULL || enemy[s]->GetDeadFlag()) {
				continue;
			}
			enemy[s]->GetPosition(&ex, &ey);
			//�����蔻��
			if (!CircleCollision(PSHOT_COLLISION, ENEMY1_COLLISION, px, ex, py, ey)) {
				continue;
			}
			//�������Ă���΁Adeadflag�𗧂Ă�
			enemy[s]->SetDeadFlag();
			//���������e�̃t���O��߂�
			player->SetShotFlag(i, false);
			//�G���ŉ��t���O�Z�b�g
			edead_flag = true;
			//�G���ŃG�t�F�N�g�Z�b�g
			EnemyDeadEffect(ex, ey);
			//���_��������
			score->SetScore(CURRENT_SCORE, 100);
			//�A�C�e���o��
			for (int z = 0; z < ITEM_NUM; ++z) {
				if (!item[z]->GetFlag()) {
					item[z]->SetFlag(ex, ey, enemy[s]->GetItem());
					break;
				}
			}
		}
	}
}

void CONTROL::CollisionPlayer()
{
	double px, py;
	double ex, ey;

	//�G�̒e�Ƒ���L�����Ƃ̓����蔻��
	player->GetPosition(&px, &py);
	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] == NULL) {
			continue;
		}
		for (int s = 0; s < ENEMY_SNUM; ++s) {
			//�e�t���O�������Ă����true��Ԃ�
			if (!enemy[i]->GetShotPosition(s, &ex, &ey)) {
				continue;
			}
			//�e�ɂ���ē����蔻�肪�Ⴄ�̂�switch���ŕ���
			int eshot_coll = 0;
			switch (enemy[i]->GetShotType()) {
				case 0:
					eshot_coll = ESHOT0_COLLISION;
				break;

				case 1:
					eshot_coll = ESHOT1_COLLISION;
					break;

				case 2:
					eshot_coll = ESHOT2_COLLISION;
					break;
			}

			//�O���C�Y�����蔻��t���O��true�Ȃ�
			if (CircleCollision(GRAZE_COLLISION, eshot_coll, px, ex, py, ey)) {
				//�܂�
				if (!enemy[i]->GetGrazeFlag(s)) {
					enemy[i]->SetGrazeFlag(s);
					//�O���C�Y�̃C���X�^���X����
					for (int z = 0; z < GRAZE_NUM; ++z) {
						if (!graze[z]->GetFlag()) {
							graze[z]->SetFlag(px, py);
							break;
						}
					}
					//�O���C�Y�̓��_��������
					score->SetScore(GRAZE_SCORE, 1);
					score->SetScore(CURRENT_SCORE, 20);
					//�O���C�Y���Z�b�g
					graze_flag = true;
				}
			}

			//�������Ă��
			if (CircleCollision(PLAYER_COLLISION, eshot_coll, px, ex, py, ey)) {
				//����L������damageflag�𗧂Ă�
				player->SetDamageFlag();
				//�e������
				enemy[i]->SetShotFlag(s, false);
				//�v���C���[���ŉ��t���O�𗧂Ă�
				pdead_flag = true;
			}
		}
	}
}

void CONTROL::CollisionItem()
{
	double px, py;
	double ix, iy;

	//�A�C�e���ƃv���C���[�̓����蔻��
	player->GetPosition(&px, &py);
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (!item[i]->GetFlag()) {
			continue;
		}
		item[i]->GetPosition(&ix, &iy);
		if (!CircleCollision(PLAYER_COLLISION, ITEM_COLLISION, px, ix, py, iy)) {
			continue;
		}
		switch (item[i]->GetType()) {
		case 0:
			score->SetScore(CURRENT_SCORE, 300);
			break;
		case 1:
			player->SetPower(1);
			score->SetScore(POWER_SCORE, player->GetPower());
			//�p���[�𑝂₷
			break;
		}
		item[i]->Delete();
		//�A�C�e���擾�����Z�b�g
		item_flag = true;
	}
}

void CONTROL::GetPlayerPosition(
	double* x,
	double* y
)
{
	double tempx, tempy;

	player->GetPosition(&tempx, &tempy);

	*x = tempx;
	*y = tempy;
}

bool CONTROL::GetEnemyPosition(
	int		index,
	double*	x,
	double*	y
)
{
	double tempx;
	double tempy;

	if (enemy[index] == NULL || enemy[index]->GetDeadFlag())
		return false;

	//�w�肵���Y���̓G�̍��W���擾
	enemy[index]->GetPosition(&tempx, &tempy);

	//���
	*x = tempx;
	*y = tempy;

	return true;
}


bool CONTROL::CircleCollision(
	double c1,
	double c2,
	double cx1,
	double cx2,
	double cy1,
	double cy2
)
{

	double hlength = c1 + c2;
	double xlength = cx1 - cx2;
	double ylength = cy1 - cy2;

	if (hlength * hlength >= xlength * xlength + ylength * ylength) {
		return true;
	}
	else {
		return false;
	}
}