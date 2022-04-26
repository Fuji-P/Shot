/*
* サイト名	：プログラミング入門サイト 〜bituse〜
* リンク	：https://bituse.info/
*/

#include "pch.h"
#include "enemy.h"

ENEMY::ENEMY(
				int type,
				int stype,
				int m_pattern,
				int s_pattern,
				int in_time,
				int stop_time,
				int shot_time,
				int out_time,
				int x,
				int y,
				int speed,
				int hp,
				int item
			)
{

	//サイズ
	width = 27;
	height = 25;

	//敵の種類
	this->type = type;
	this->stype = stype;

	//移動パターンとショットパターン
	this->m_pattern = m_pattern;
	this->s_pattern = s_pattern;

	this->x = x;
	this->y = y;

	this->in_time = in_time;

	this->stop_time = stop_time;

	this->shot_time = shot_time;

	this->out_time = out_time;

	//hpとアイテム代入
	this->hp = hp;
	this->item = item;

	//敵画像読み込み
	if (type == 0) {
		LoadDivGraph("enemy.png", 3, 1, 3, 27, 25, gh);
	}

	int temp;
	//弾画像読み込み
	if (stype == 0) {
		temp = LoadGraph("enemyshot1.png");
	}

	int w, h;
	GetGraphSize(temp, &w, &h);

	for (int i = 0; i < ENEMY_SNUM; ++i) {
		shot[i].flag = false;
		shot[i].gh = temp;
		shot[i].width = w;
		shot[i].height = h;
		shot[i].pattern = s_pattern;
		shot[i].speed = speed;
		shot[i].x = x;
		shot[i].y = y;
	}

	count = 0;
	scount = 0;

	deadflag = false;
	endflag = false;
	sflag = false;
}


void ENEMY::Move()
{
	//まだ生きてるか画面内に居るときだけ処理
	if (!deadflag) {
		switch (m_pattern) {
			//途中で止まって、そのまま後ろに帰るパターン
		case 0:

			//出てきてから止まる時間までの間なら下に移動
			if (in_time < g_count && g_count < stop_time) {
//				y += 2;
				y += 1;
				//帰還時間を過ぎたら戻る。
			}
			else if (g_count > out_time) {
//				y -= 2;
				y -= 1;
			}
			break;

			//そのまま止まらずに下に行くパターン
		case 1:

			if (in_time <= g_count) {
//				y += 2;
				y += 1;
			}

			break;

			//ちょっとずつ左に移動しながら消えていく
		case 2:
			if (in_time <= g_count) {
//				y += 1;
				y += 0.5;
				if (count % 10 == 0) {
//					x -= 1;
					x -= 0.5;
				}
			}
			break;

			//ちょっとずつ右に移動しながら消えていく
		case 3:
			if (in_time <= g_count) {
//				y += 1;
				y += 0.5;
				if (count % 10 == 0) {
//					x += 1;
					x += 0.5;
				}
			}
			break;

		}
		//画面からはみ出したら、deadflag(はみ出すか死ぬかのフラグ)をtrueにする。
		if (g_count >= stop_time) {
			if (OutCheck()) {
				deadflag = true;
			}
		}
		++count;
	}
}

void ENEMY::Draw()
{
	int temp;

	//弾から最初に描画
	for (int i = 0; i < ENEMY_SNUM; ++i) {
		if (shot[i].flag) {
			DrawGraph(shot[i].x, shot[i].y, shot[i].gh, true);
		}
	}

	if (!endflag) {

//		temp = count % 40 / 10;
		temp = count % 120 / 30;
		if (temp == 3)
			temp = 1;

		DrawGraph(x, y, gh[temp], TRUE);
	}
}

void ENEMY::Shot()
{

	//発射タイミングになったら、フラグを立てる
	if (shot_time == g_count) {
		sflag = true;
	}

	//フラグ立ってるときだけ
	if (sflag) {

		switch (s_pattern) {
		case 0:
			//10回に一回発射。40までなので5発発射。
//			if (scount % 10 == 0 && scount <= 40) {
			if (scount % 20 == 0 && scount <= 80) {
				for (int i = 0; i < ENEMY_SNUM; ++i) {
					//フラグが立ってない弾を探して、座標等をセット
					if (shot[i].flag == false) {
						shot[i].flag = true;
						shot[i].x = x;
						shot[i].y = y;
						break;
					}
				}
			}
			break;
		}

		//フラグが立ってる弾の数
		int s = 0;

		//フラグ立ってる弾だけ、弾の移動を行う
		for (int i = 0; i < ENEMY_SNUM; ++i) {
			if (shot[i].flag) {
				shot[i].y += shot[i].speed;

				//弾が画面をはみ出たらフラグを戻す。
				if (shot[i].x < -20 || shot[i].x>420 || shot[i].y < -20 || shot[i].y>500) {
					shot[i].flag = false;
					continue;
				}
				++s;
			}
		}
		//sがゼロということは発射中の弾がない。
		//かつdeadflagがTRUEということはこの敵のクラスは消滅させてもよい
		if (s == 0 && deadflag) {
			//敵クラス消滅フラグをTRUEにする
			endflag = true;
		}
		++scount;
	}
}

bool ENEMY::All()
{
	Move();

	Shot();

	Draw();

	++count;

	return endflag;
}

bool ENEMY::OutCheck()
{
	if (x < -50 || x > 520 || y < -50 || y > 530) {
		return true;
	}
	else {
		return false;
	}
}