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

	//背景クラスの生成
	back = new BACK;

	//エフェクトクラスのインスタンス生成
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		effect_edead[i] = new EFFECT_EDEAD;
	}

	//グレイズクラスのインスタンス生成
	for (int i = 0; i < GRAZE_NUM; ++i) {
		graze[i] = new GRAZE;
	}

	//スコアクラスの生成
	score = new SCORE;

	//アイテムクラスのインスタンス生成
	for (int i = 0; i < ITEM_NUM; ++i) {
		item[i] = new ITEM;
	}

	//エネミーデータの読み込み
	ENEMYDATA data[ENEMY_NUM];

	LoadEnemyData(data);

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
	//プレイヤークラスの解放
	delete player;

	//背景クラスの解放
	delete back;

	//エネミークラスの解放
	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] != NULL) {
			delete enemy[i];
		}
	}

	//グレイズクラスの解放
	for (int i = 0; i < GRAZE_NUM; ++i) {
		if (graze[i] != NULL) {
			delete graze[i];
		}
	}

	//敵消滅エフェクトクラスの解放
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		if (effect_edead[i] != NULL) {
			delete effect_edead[i];
		}
	}

	//スコアクラスの解放
	delete score;

	//アイテムクラスの解放
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

	//ヘッダ読み飛ばし
	while (fgetc(fp) != '\n');

	while (1) {

		while (1) {

			chr = fgetc(fp);

			//末尾ならループを抜ける。
			if (chr == EOF) {
				return;
			}

			//カンマか改行でなければ、文字としてつなげる
			if (chr != ',' && chr != '\n') {
				strcat(buf, (const char*)&chr);
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
		if (chr == '\n') {
			col = 1;
			++row;
		}
	}
}

void CONTROL::All()
{

	//サウンドフラグを初期化
	edead_flag = false;
	pdead_flag = false;
	eshot_flag = false;
	pshot_flag = false;
	graze_flag = false;
	item_flag = false;

	//背景クラスのAll関数実行
	back->All();

	//描画領域を指定
	SetDrawArea(MARGIN, MARGIN, MARGIN + 380, MARGIN + 460);

	//プレイヤークラスのAll関数実行
	player->All();

	//プレイヤーショットサウンドフラグチェック
	if (player->GetShotSound()) {
		pshot_flag = true;
	}

	for (int i = 0; i < ENEMY_NUM; ++i) {
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

	//グレイズ描画
	for (int i = 0; i < GRAZE_NUM; ++i) {
		if (graze[i]->GetFlag()) {
			graze[i]->All();
		}
	}

	//敵消滅エフェクト
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		if (effect_edead[i]->GetFlag()) {
			effect_edead[i]->All();
		}
	}

	//アイテム描画
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (item[i]->GetFlag()) {
			item[i]->All();
		}
	}

	//描画領域を指定
	SetDrawArea(0, 0, 640, 480);

	//スコア描画
	score->All();

	SoundAll();
	++g_count;
}

void CONTROL::EnemyDeadEffect(
	double x,
	double y
)
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

	//プレイヤーが生きてれば
	if (!player->GetDamageFlag()) {
		CollisionPlayer();
		CollisionItem();
	}

	//ライフは毎回取得
	score->SetScore(LIFE_SCORE, player->GetLife());
}

void CONTROL::CollisionEnemy()
{
	double px, py;
	double ex, ey;

	//操作キャラの弾と敵との当たり判定
	for (int i = 0; i < PSHOT_NUM; ++i) {
		if (!player->GetShotPosition(i, &px, &py)) {
			continue;
		}
		for (int s = 0; s < ENEMY_NUM; ++s) {
			//敵クラスのポインタがNULLじゃない、かつdeadflagがfalse(死んでない＆帰還してない)
			if (enemy[s] == NULL || enemy[s]->GetDeadFlag()) {
				continue;
			}
			enemy[s]->GetPosition(&ex, &ey);
			//当たり判定
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
			//得点を加える
			score->SetScore(CURRENT_SCORE, 100);
			//アイテム出現
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

	//敵の弾と操作キャラとの当たり判定
	player->GetPosition(&px, &py);
	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] == NULL) {
			continue;
		}
		for (int s = 0; s < ENEMY_SNUM; ++s) {
			//弾フラグが立っていればtrueを返す
			if (!enemy[i]->GetShotPosition(s, &ex, &ey)) {
				continue;
			}
			//弾によって当たり判定が違うのでswitch文で分岐
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

			//グレイズ当たり判定フラグがtrueなら
			if (CircleCollision(GRAZE_COLLISION, eshot_coll, px, ex, py, ey)) {
				//まだ
				if (!enemy[i]->GetGrazeFlag(s)) {
					enemy[i]->SetGrazeFlag(s);
					//グレイズのインスタンス検索
					for (int z = 0; z < GRAZE_NUM; ++z) {
						if (!graze[z]->GetFlag()) {
							graze[z]->SetFlag(px, py);
							break;
						}
					}
					//グレイズの得点を加える
					score->SetScore(GRAZE_SCORE, 1);
					score->SetScore(CURRENT_SCORE, 20);
					//グレイズ音セット
					graze_flag = true;
				}
			}

			//当たってれば
			if (CircleCollision(PLAYER_COLLISION, eshot_coll, px, ex, py, ey)) {
				//操作キャラのdamageflagを立てる
				player->SetDamageFlag();
				//弾を消す
				enemy[i]->SetShotFlag(s, false);
				//プレイヤー消滅音フラグを立てる
				pdead_flag = true;
			}
		}
	}
}

void CONTROL::CollisionItem()
{
	double px, py;
	double ix, iy;

	//アイテムとプレイヤーの当たり判定
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
			//パワーを増やす
			break;
		}
		item[i]->Delete();
		//アイテム取得音をセット
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

	//指定した添字の敵の座標を取得
	enemy[index]->GetPosition(&tempx, &tempy);

	//代入
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