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

	//エネミークラスの生成
	enemy = new ENEMY;

	back = new BACK;

}

CONTROL::~CONTROL()
{
	//プレイヤークラスの解放
	delete player;
}

void CONTROL::All()
{
	//描画領域を指定
	SetDrawArea(MARGIN, MARGIN, MARGIN + 380, MARGIN + 460);

	back->All();

	//プレイヤークラスのAll関数実行
	player->All();

	if (enemy != NULL) {
		if (enemy -> All()) {
			delete enemy;
			enemy = NULL;
		}
	}

	++g_count;
}