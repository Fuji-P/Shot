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
			if (c == EOF)
				goto out;

			//カンマか改行でなければ、文字としてつなげる
			if (c != ',' && c != '\n')
				strcat(buf, (const char*)&c);
			//カンマか改行ならループ抜ける。
			else
				break;
		}
		//ここに来たということは、1セル分の文字列が出来上がったということ
		switch (col) {
			//1列目は敵種類を表す。atoi関数で数値として代入。
		case 1:	data[row].type = atoi(buf); break;
			//2列目は弾種類。以降省略。
		case 2: data[row].stype = atoi(buf); break;
		case 3: data[row].m_pattern = atoi(buf); break;
		case 4: data[row].s_pattern = atoi(buf); break;
		case 5: data[row].in_time = atoi(buf); break;
		case 6: data[row].stop_time = atoi(buf); break;
		case 7: data[row].shot_time = atoi(buf); break;
		case 8: data[row].out_time = atoi(buf); break;
		case 9: data[row].x = atoi(buf); break;
		case 10: data[row].y = atoi(buf); break;
		case 11: data[row].speed = atoi(buf); break;
		case 12: data[row].hp = atoi(buf); break;
		case 13: data[row].item = atoi(buf); break;
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
}

void CONTROL::All()
{
	//描画領域を指定
	SetDrawArea(MARGIN, MARGIN, MARGIN + 380, MARGIN + 460);

	back->All();

	//プレイヤークラスのAll関数実行
	player->All();

	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] != NULL) {
			if (enemy[i]->All()) {
				delete enemy[i];
				enemy[i] = NULL;
			}
		}
	}
	++g_count;
}