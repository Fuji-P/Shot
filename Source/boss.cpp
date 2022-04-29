/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include "pch.h"
#include "control.h"

//コンストラクタ
BOSS::BOSS()
{
	//座標初期値
	x = 200;
	y = -100;
	prev_x = 200;
	prev_y = -100;

	raise = 1;
	raise2 = 1;
	angle = 0;
	move_pattern = 0;
	shot_pattern = 0;

	movex = 0;
	movey = 180;

	waitcount = 0;
	p3_state = 0;
	scount = 0;
	count = 0;

	wait = false;
	damageflag = false;
	flag = true;
	shotflag = false;
	s_shot = false;

	//画像読み込み
	gh_face[0] = LoadGraph("boss.png");
	gh_face[1] = LoadGraph("boss_damage.png");

	gh_shot[0] = LoadGraph("enemyshot1.png");
	gh_shot[1] = LoadGraph("enemyshot2.png");
	gh_shot[2] = LoadGraph("enemyshot3.png");

	//弾初期化
	for (int i = 0; i < BOSS_SHOTNUM; ++i) {
		shot[i].flag = false;
		shot[i].gflag = false;
		shot[i].gh = 0;
		shot[i].pattern = 0;
		shot[i].rad = 0;
		shot[i].speed = 0;
		shot[i].x = 0;
		shot[i].y = 0;
	}
}

void BOSS::All()
{
	Move();

	if (shotflag) {
		Shot();
	}

	Draw();

	++count;
}

void BOSS::Move()
{

	switch (move_pattern) {
		case 0:
			Appear();
			break;
		case 1:
			MovePattern1();
			break;
		case 2:
			MovePattern2();
			break;
		case 3:
			MovePattern3();
			break;
	}
}

void BOSS::Appear()
{
	double temp;

	angle += 1;

	temp = sin(angle * M_PI / 180);

	x = 200;
	y = prev_y + temp * movey;

	//提位置まで移動したら移動パターンを1に変更
	if (angle == 90) {
		move_pattern = 1;
		angle = 0;
		shotflag = true;
	}
}

void BOSS::MovePattern1()
{
	angle += raise;

	y = 80 + sin(angle * M_PI / 180) * BOSS_SHAKE;

	if (angle == 90) {
		raise = -1;
	}
	else if (angle == -90) {
		raise = 1;
	}

	x = 200;
}

void BOSS::MovePattern2()
{
	if (!wait) {

		x += raise2;

		if (x == 70) {
			raise2 = 1;
			wait = true;
		}
		else if (x == 330) {
			raise2 = -1;
			wait = true;
		}
	}

	if (wait) {
		++waitcount;
		if (waitcount == 20) {
			wait = false;
			waitcount = 0;
		}
	}
}

void BOSS::MovePattern3()
{

	double temp;

	angle += 1;

	temp = sin(angle * M_PI / 180);

	x = prev_x + temp * movex;
	y = prev_y + temp * movey;

	if (angle == 90) {

		if (p3_state == 0) {
			MoveInit(70, 80, 1);
		}
		else if (p3_state == 1) {
			MoveInit(200, 160, 2);
		}
		else {
			MoveInit(330, 80, 0);
		}
	}
}

void BOSS::MoveInit(
	double	bx,
	double	by,
	int		state
)
{
	prev_x = x;
	prev_y = y;

	movex = bx - x;
	movey = by - y;

	angle = 0;

	p3_state = state;
}
void BOSS::Draw()
{
	//弾から最初に描画
	for (int i = 0; i < BOSS_SHOTNUM; ++i) {
		if (shot[i].flag) {
			DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + 90 * M_PI / 180, shot[i].gh, TRUE);
		}
	}

	//弾があたったときはダメージ用の画像を描画、
	if (damageflag) {
		DrawRotaGraph(x, y, 1.0, 0, gh_face[1], TRUE);
	}
	else {
		//何も無いときは通常描画
		DrawRotaGraph(x, y, 1.0, 0, gh_face[0], TRUE);
	}

	damageflag = false;
}

void BOSS::Shot()
{
	//何発発射したか
	int num = 0;
	//空いてる弾の添え字
	int index;

	//scountを戻すかどうかのフラグ
	bool scflag = false;

	CONTROL& control = CONTROL::GetInstance();

	double px;
	double py;
	static double trad;

	if (damageflag) {
		return;
	}

	control.GetPlayerPosition(&px, &py);

	if (scount == 0) {
		trad = atan2(py - y, px - x);
	}

	//サウンドフラグを戻す
	s_shot = false;

	//弾のセット
	switch (shot_pattern) {

		case 0:
//			if (scount % 5 == 0 && scount <= 15) {
			if (scount % 10 != 0 || scount > 30) {
				break;
			}

			while ((index = ShotSearch()) != -1) {
				shot[index].gh = gh_shot[1];
				shot[index].pattern = 0;
				shot[index].speed = 3;

				if (num == 0) {
					shot[index].rad = trad - (10 * M_PI / 180);
				}
				else if (num == 1) {
					shot[index].rad = trad - (5 * M_PI / 180);
				}
				else if (num == 2) {
					shot[index].rad = trad;
				}
				else if (num == 3) {
					shot[index].rad = trad + (5 * M_PI / 180);
				}
				else if (num == 4) {
					shot[index].rad = trad + (10 * M_PI / 180);
				}

				++num;

				s_shot = true;

				if (num == 5) {
					break;
				}
			}
			break;

		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
	}

	for (int i = 0; i < BOSS_SHOTNUM; ++i) {
		if (!shot[i].flag) {
			continue;
		}
		switch (shot[i].pattern) {

			case 0:
				shot[i].x += shot[i].speed * cos(shot[i].rad);
				shot[i].y += shot[i].speed * sin(shot[i].rad);

				if (scflag == false && scount == 80) {
					scflag = true;
				}

				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
		}

		//弾がはみ出てたらフラグを戻す
		if (ShotOutCheck(i)) {
			shot[i].flag = false;
		}
	}

	++scount;

	if (scflag) {
		scount = 0;
	}
}

int BOSS::ShotSearch()
{
	bool check = false;
	int i;

	for (i = 0; i < BOSS_SHOTNUM; ++i) {
		if (shot[i].flag == false) {
			check = true;
			break;
		}
	}
	if (check) {
		shot[i].flag = true;
		shot[i].x = x;
		shot[i].y = y;
	}
	else {
		i = -1;
	}

	return i;
}

bool BOSS::GetShotSound()
{
	return s_shot;
}

bool BOSS::ShotOutCheck(
	int	i
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