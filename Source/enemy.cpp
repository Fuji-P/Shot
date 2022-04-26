/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include "pch.h"
#include "enemy.h"

ENEMY::ENEMY(
				const char*		c_filename,
				int				type,
				int				m_pattern,
				int				x,
				int				y,
				int				in_time,
				int				stop_time,
				int				shot_time,
				int				out_time,
				const char*		s_filename,
				int				stype,
				int				s_pattern,
				int				speed
			)
{

	//読み込み
	LoadDivGraph(c_filename, 3, 1, 3, 27, 25, gh);

	//サイズ
	width = 27;
	height = 25;

	//敵の種類
	this->type = type;

	//弾の種類
	this->stype = stype;

	//移動パターンとショットパターン
	this->m_pattern = m_pattern;
	this->s_pattern = s_pattern;

	//座標セット
	this->x = x;
	this->y = y;

	//出現、停止、発射、帰還時間セット
	this->in_time = in_time;

	this->stop_time = stop_time;

	this->shot_time = shot_time;

	this->out_time = out_time;

	//弾画像とサイズ取得
	int temp = LoadGraph(s_filename);
	int w, h;
	GetGraphSize(temp, &w, &h);

	//弾の初期化
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
	//出てきてから止まる時間までの間なら下に移動
	if (in_time < g_count && g_count < stop_time) {
//		y += 2;
		y += 1;
		//帰還時間を過ぎたら戻る。
	}
	else if (g_count > out_time) {
//		y -= 2;
		y -= 1;
		if (y < -40) {
			endflag = true;
		}
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
		temp = count % 80 / 20;
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