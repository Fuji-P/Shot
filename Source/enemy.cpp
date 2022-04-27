/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include "pch.h"
#include "enemy.h"
#include "control.h"

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
	switch (stype) {
		case 0:
			temp = LoadGraph("enemyshot1.png");
			break;
		case 1:
			temp = LoadGraph("enemyshot2.png");
			break;
		case 2:
			temp = LoadGraph("enemyshot3.png");
			break;
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
		shot[i].gflag = false;
	}

	count = 0;
	scount = 0;
	num = 0;
	rad = 0;

	deadflag = false;
	endflag = false;
	sflag = false;
	s_shot = false;
}


void ENEMY::Move()
{
	//まだ生きてるか画面内に居るときだけ処理
	if (deadflag) {
		return;
	}

	switch (m_pattern) {

		//途中で止まって、そのまま後ろに帰るパターン
		case 0:
			//出てきてから止まる時間までの間なら下に移動
			if (in_time < g_count && g_count < stop_time) {
//				y += 2;
				y += 1;
			}
			//帰還時間を過ぎたら戻る。
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

	++count;
	//画面からはみ出したら、deadflag(はみ出すか死ぬかのフラグ)をtrueにする。
	if (g_count < stop_time) {
		return;
	}
	if (OutCheck()) {
		deadflag = true;
	}
}

void ENEMY::Draw()
{
	int temp;

	//弾から最初に描画
	for (int i = 0; i < ENEMY_SNUM; ++i) {
		if (!shot[i].flag) {
			continue;
		}
		if (stype == 0 || stype == 2) {
			DrawGraph(shot[i].x - shot[i].width / 2, shot[i].y - shot[i].height / 2, shot[i].gh, true);
		}
		else {
			DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + (90 * M_PI / 180), shot[i].gh, true);
		}
	}

	if (deadflag) {
		return;
	}
//	temp = count % 40 / 10;
	temp = count % 120 / 30;
	if (temp == 3) {
		temp = 1;
	}
	DrawGraph(x - width / 2, y - height / 2, gh[temp], TRUE);
}

void ENEMY::Shot()
{

	//発射タイミングになったら、フラグを立てる
	if (shot_time == g_count) {
		sflag = true;
	}

	//フラグ立ってるときだけ
	if (!sflag) {
		return;
	}

	//ショット音フラグを戻す
	s_shot = false;

	ShotGenerate();
	ShotMove();

	++scount;
}

void ENEMY::ShotGenerate()
{
	//CONTROLクラスの参照
	CONTROL& control = CONTROL::GetInstance();
	double px, py;

	//敵が生きてるときだけ発射する。
	if (deadflag) {
		return;
	}
	//プレイヤーの一取得
	control.GetPlayerPosition(&px, &py);

	//敵とプレイヤーとの座標の差から逆正接を求める。
	//初回だけ実行
	if (scount == 0) {
		rad = atan2(py - y, px - x);
	}

	switch (s_pattern) {

		//前方にショット
		case 0:
			//5ループに一回発射。20までなので5発発射。
//			if (scount % 5 == 0 && scount <= 20) {
//			if (scount % 10 == 0 && scount <= 40) {
			if (scount % 10 != 0 || scount > 40) {
				break;
			}
			for (int i = 0; i < ENEMY_SNUM; ++i) {
				//フラグが立ってない弾を探して、座標等をセット
//				if (shot[i].flag == false) {
				if (shot[i].flag) {
					continue;
				}
				shot[i].flag = true;
				shot[i].x = x;
				shot[i].y = y;
				shot[i].rad = rad;
				break;
			}
			//ショットサウンドフラグを立てる
			s_shot = true;
			break;

		//プレイヤーに向かって直線ショット
		case 1:
			//6ループに一回発射。54までなので10発発射。
//			if (scount % 6 == 0 && scount <= 54) {
//			if (scount % 12 == 0 && scount <= 108) {
			if (scount % 12 != 0 || scount > 108) {
				break;
			}
			for (int i = 0; i < ENEMY_SNUM; ++i) {
				//フラグが立ってない弾を探して、座標等をセット
//				if (shot[i].flag == false) {
				if (shot[i].flag) {
					continue;
				}
				shot[i].flag = true;
				shot[i].x = x;
				shot[i].y = y;
				shot[i].rad = rad;
				break;
			}
			//ショットサウンドフラグを立てる
			s_shot = true;
			break;

		//3直線ショット
		case 2:
			//10ループに一回発射。1ループに3発なので5ループさせると１５発発射
//			if (scount % 10 == 0 && scount <= 40) {
//			if (scount % 20 == 0 && scount <= 80) {
			if (scount % 20 != 0 || scount > 80) {
				break;
			}
			for (int i = 0; i < ENEMY_SNUM; ++i) {
				//フラグが立ってない弾を探して、座標等をセット
//				if (shot[i].flag == false) {
				if (shot[i].flag) {
					continue;
				}
				shot[i].flag = true;
				shot[i].x = x;
				shot[i].y = y;

				//0の時は左より
				if (num == 0) {
					//敵とプレイヤーとの逆正接から10度引いたラジアンを代入
					shot[i].rad = rad - (10 * 3.14 / 180);
				}
				//1の時はプレイヤー一直線
				else if (num == 1) {
					//敵とプレイヤーとの逆正接を代入
					shot[i].rad = rad;
				}
				//2の時は右より
				else if (num == 2) {
					//敵とプレイヤーとの逆正接から10度足したラジアンを代入
					shot[i].rad = rad + (10 * M_PI / 180);
				}
				++num;

				//3発発射したら,numを0にしてループを抜ける。
				if (num == 3) {
					num = 0;
					break;
				}
			}
			//ショットサウンドフラグを立てる
			s_shot = true;
			break;

			//乱射ショット
		case 3:
			//10ループに一回発射。42までなので15発発射。
//			if (scount % 3 == 0 && scount <= 42) {
//			if (scount % 6 == 0 && scount <= 84) {
			if (scount % 6 != 0 || scount > 84) {
				break;
			}

			//1ループ毎に1発発射
			for (int i = 0; i < ENEMY_SNUM; ++i) {

				//フラグが立ってない弾を探して、座標等をセット
//				if (shot[i].flag == false) {
				if (shot[i].flag) {
					continue;
				}

				shot[i].flag = true;
				shot[i].x = x;
				shot[i].y = y;

				//初回だけ乱数初期化
				if (num == 0) {
					srand((unsigned int)time(NULL));
				}

				shot[i].rad = atan2(py - y, px - x) - (60 * M_PI / 180) + ((rand() % 120) * M_PI / 180);
				++num;
				break;
			}
			//ショットサウンドフラグを立てる
			s_shot = true;
			break;
	}
}

void ENEMY::ShotMove()
{
	//フラグが立ってる弾の数
	int s = 0;

	//フラグ立ってる弾だけ、弾の移動を行う
	for (int i = 0; i < ENEMY_SNUM; ++i) {
//		if (shot[i].flag) {
		if (!shot[i].flag) {
			continue;
		}
		switch (shot[i].pattern) {
			//単純に下に発射
		case 0:
			shot[i].y += shot[i].speed;
			break;

		case 1:
			shot[i].x += shot[i].speed * cos(shot[i].rad);
			shot[i].y += shot[i].speed * sin(shot[i].rad);
			break;

		case 2:
			shot[i].x += shot[i].speed * cos(shot[i].rad);
			shot[i].y += shot[i].speed * sin(shot[i].rad);
			break;

		case 3:
			shot[i].x += shot[i].speed * cos(shot[i].rad);
			shot[i].y += shot[i].speed * sin(shot[i].rad);
			break;
		}

		//弾が画面をはみ出たらフラグを戻す。
		if (ShotOutCheck(i)) {
			shot[i].flag = false;
			continue;
		}
		++s;
	}

	//sがゼロということは発射中の弾がない。
	//かつdeadflagがTRUEということはこの敵のクラスは消滅させてもよい
	if (s == 0 && deadflag) {
		//敵クラス消滅フラグをTRUEにする
		endflag = true;
	}
}

void ENEMY::GetPosition(
	double* x,
	double* y
)
{
	*x = this->x;
	*y = this->y;

}

void ENEMY::SetDeadFlag()
{
	deadflag = true;
}

void ENEMY::SetShotFlag(
	int		index,
	bool	flag
)
{
	shot[index].flag = flag;
}

void ENEMY::SetGrazeFlag(
	int index
)
{
	shot[index].gflag = true;
}

int ENEMY::GetShotType()
{
	return stype;
}

bool ENEMY::GetGrazeFlag(
	int index
)
{
	return shot[index].gflag;
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

bool ENEMY::ShotOutCheck(
	int i
)
{
	//弾が画面をはみ出たらフラグを戻す。
	if (shot[i].x < -20 || shot[i].x > 420 || shot[i].y < -20 || shot[i].y > 500) {
		return true;
	}
	else {
		return false;
	}
}

bool ENEMY::GetShotSound()
{
	return s_shot;
}

bool ENEMY::GetDeadFlag()
{
	return deadflag;
}

bool ENEMY::GetShotPosition(
	int		index,
	double*	x,
	double*	y
)
{
	if (shot[index].flag) {
		*x = shot[index].x;
		*y = shot[index].y;
		return true;
	}
	else {
		return false;
	}
}