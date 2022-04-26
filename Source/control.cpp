/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include "pch.h"
#include "control.h"

CONTROL::CONTROL()
{
	//プレイヤークラスの生成
	player = new PLAYER;

	back = new BACK;

	//エフェクトクラスのインスタンス生成
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		effect_edead[i] = new EFFECT_EDEAD;
	}

	FILE* fp;
	ENEMYDATA data[ENEMY_NUM];
	char buf[100];
	int c;
	int col = 1;
	int row = 0;

	memset(buf, 0, sizeof(buf));
	fp = fopen("enemydata.csv", "r");

	//ヘッダ読み飛ばし
	while (fgetc(fp) != '\n');

	while (1) {

		while (1) {

			c = fgetc(fp);

			//末尾ならループを抜ける。
			if (c == EOF) {
				goto out;
			}

			//カンマか改行でなければ、文字としてつなげる
			if (c != ',' && c != '\n') {
				strcat(buf, (const char*)&c);
			}
			//カンマか改行ならループ抜ける。
			else {
				break;
			}
		}
		//ここに来たということは、1セル分の文字列が出来上がったということ
		switch (col) {
			//1列目は敵種類を表す。atoi関数で数値として代入。
			case 1:	
				data[row].type = atoi(buf);
				break;
			//2列目は弾種類。以降省略。
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
		//バッファを初期化
		memset(buf, 0, sizeof(buf));
		//列数を足す
		++col;

		//もし読み込んだ文字が改行だったら列数を初期化して行数を増やす
		if (c == '\n') {
			col = 1;
			++row;
		}
	}
out:

	//敵クラス生成
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

	//サウンドファイル読み込み
	s_edead = LoadSoundMem("enemydead.wav");
	s_pdead = LoadSoundMem("playdead.wav");
	s_eshot = LoadSoundMem("enemyshot.wav");
	s_pshot = LoadSoundMem("playershot.wav");

	edead_flag = false;
	pdead_flag = false;
	eshot_flag = false;
	pshot_flag = false;
}

CONTROL::~CONTROL()
{
	//プレイヤークラスの解放
	delete player;

	delete back;

	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] != NULL) {
			delete enemy[i];
		}
	}

	//敵消滅エフェクト
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		if (effect_edead[i] != NULL) {
			delete effect_edead[i];
		}
	}
}

void CONTROL::All()
{

	//サウンドフラグを初期化
	edead_flag = pdead_flag =  eshot_flag = pshot_flag = false;

	//描画領域を指定
	SetDrawArea(MARGIN, MARGIN, MARGIN + 380, MARGIN + 460);

	back->All();

	//プレイヤークラスのAll関数実行
	player->All();

	//プレイヤーショットサウンドフラグチェック
	if (player->GetShotSound()) {
		pshot_flag = true;
	}

	for (int i = 0; i < ENEMY_NUM; ++i) {
//		if (enemy[i] != NULL) {
		if (enemy[i] == NULL) {
			continue;
		}
		//敵ショットサウンドフラグチェック
		if (enemy[i]->GetShotSound()) {
			eshot_flag = true;
		}
		if (enemy[i]->All()) {
			delete enemy[i];
			enemy[i] = NULL;
		}
	}

	//当たり判定
	CollisionAll();

	//敵消滅エフェクト
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		if (effect_edead[i]->GetFlag()) {
			effect_edead[i]->All();
		}
	}

	SoundAll();
	++g_count;
}

void CONTROL::EnemyDeadEffect(double x, double y)
{
	//エフェクトセット
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

}

void CONTROL::GetPlayerPosition(double* x, double* y)
{
	double tempx, tempy;

	player->GetPosition(&tempx, &tempy);

	*x = tempx;
	*y = tempy;
}

void CONTROL::GetEnemyPosition(int index, double* x, double* y)
{
	double tempx, tempy;
	//指定した添字の敵の座標を取得
	enemy[index]->GetPosition(&tempx, &tempy);

	//代入
	*x = tempx;
	*y = tempy;
}

void CONTROL::CollisionAll()
{
	double px, py, ex, ey;
	bool tempflag = false;

	//操作キャラの弾と敵との当たり判定
	for (int i = 0; i < PSHOT_NUM; ++i) {
//		if (player->GetShotPosition(i, &px, &py)) {
		if (!player->GetShotPosition(i, &px, &py)) {
			continue;
		}
		for (int s = 0; s < ENEMY_NUM; ++s) {
			//敵クラスのポインタがNULLじゃない、かつdeadflagがfalse(死んでない＆帰還してない)
//			if (enemy[s] != NULL && !enemy[s]->GetDeadFlag()) {
			if (enemy[s] == NULL || enemy[s]->GetDeadFlag()) {
				continue;
			}
			enemy[s]->GetPosition(&ex, &ey);
			//当たり判定
//			if (CircleCollision(PSHOT_COLLISION, ENEMY1_COLLISION, px, ex, py, ey)) {
			if (!CircleCollision(PSHOT_COLLISION, ENEMY1_COLLISION, px, ex, py, ey)) {
				continue;
			}
			//当たっていれば、deadflagを立てる
			enemy[s]->SetDeadFlag();
			//当たった弾のフラグを戻す
			player->SetShotFlag(i, false);
			//敵消滅音フラグセット
			edead_flag = true;
			//敵消滅エフェクトセット
			EnemyDeadEffect(ex, ey);
		}
	}

	//敵の弾と操作キャラとの当たり判定
	//プレイヤーが生きてれば
//	if (!player->GetDamageFlag()) {
	if (player->GetDamageFlag()) {
		return;
	}
	player->GetPosition(&px, &py);
	for (int i = 0; i < ENEMY_NUM; ++i) {
//		if (enemy[i] != NULL) {
		if (enemy[i] == NULL) {
			continue;
		}
		for (int s = 0; s < ENEMY_SNUM; ++s) {
			//弾フラグが立っていればtrueを返す
//			if (enemy[i]->GetShotPosition(s, &ex, &ey)) {
			if (!enemy[i]->GetShotPosition(s, &ex, &ey)) {
				continue;
			}
			//弾によって当たり判定が違うのでswitch文で分岐
			switch (enemy[i]->GetShotType()) {

				case 0:
					//当たってれば
					if (CircleCollision(PLAYER_COLLISION, ESHOT0_COLLISION, px, ex, py, ey)) {
						tempflag = true;
					}
					break;

				case 1:
					if (CircleCollision(PLAYER_COLLISION, ESHOT1_COLLISION, px, ex, py, ey)) {
						tempflag = true;
					}
					break;

				case 2:
					if (CircleCollision(PLAYER_COLLISION, ESHOT2_COLLISION, px, ex, py, ey)) {
						tempflag = true;
						}
					break;
			}

//			if (tempflag) {
			if (!tempflag) {
				continue;
			}
			//操作キャラのdamageflagを立てる
			player->SetDamageFlag();
			//弾を消す
			enemy[i]->SetShotFlag(s, false);
			//プレイヤー消滅音フラグを立てる
			pdead_flag = true;
			//一時フラグを戻す
			tempflag = false;
		}
	}
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