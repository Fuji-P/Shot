/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include "pch.h"
#include "control.h"

bool BOSS::flag = true;
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
	temp_scount = 0;

	hp = BOSS_HP;

	wait = false;
	damageflag = false;
	shotflag = false;
	s_shot = false;

	//最初はfalseに設定
	no_damage = false;

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
		case 4:
			MoveToDefault();
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
		prev_x = x;
		prev_y = y;
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

	angle += 0.5;

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

//定位置に戻る
void BOSS::MoveToDefault()
{

	double temp;

	angle += 2;

	temp = sin(angle * M_PI / 180);

	x = prev_x + temp * movex;
	y = prev_y + temp * movey;

	//指定した位置まで移動したら
	if (angle == 90) {

		//次の移動＆ショットパターンに変更
		SetMovePattern(prev_move_pattern + 1);
		SetShotPattern(prev_shot_pattern + 1);
		//無敵フラグを戻す
		no_damage = false;

		//移動パターンが３なら
		if (move_pattern == 3)
			MoveInit(200, 160, 2);
	}

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

	if (damageflag) {
		return;
	}

	double px;
	double py;

	CONTROL& control = CONTROL::GetInstance();
	control.GetPlayerPosition(&px, &py);

	static double trad;
	if (scount == 0) {
		trad = atan2(py - y, px - x);
	}

	//サウンドフラグを戻す
	s_shot = false;

	//弾のセット
	switch (shot_pattern) {

		case 0:
			ShotPattern0(trad);
			break;

		case 1:
			ShotPattern1(px, py);
			break;

		case 2:
			ShotPattern2(px, py, trad);
			break;

		case 3:
			ShotPattern3(px, py);
			break;

		default:
			//何もしない
			break;
	}
	ShotMove();
}

void BOSS::ShotPattern0(
	double	trad
)
{

	//	if (scount % 5 == 0 && scount <= 15) {
	if (scount % 10 != 0 || scount > 30) {
		return;
	}

	//何発発射したか
	int num = 0;

	//空いてる弾の添え字
	int index = 0;

	while ((index = ShotSearch()) != -1) {
		shot[index].gh = gh_shot[1];
		shot[index].pattern = 0;
		shot[index].speed = 3;
		shot[index].type = 2;

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
}

void BOSS::ShotPattern1(
	double	px,
	double	py
)
{
	//	if (scount % 5 == 0) {
	if (scount % 10 != 0) {
		return;
	}

	//空いてる弾の添え字
	int index = 0;

	//	if ((index = ShotSearch()) != -1) {
	if ((index = ShotSearch()) == -1) {
		return;
	}
	shot[index].gh = gh_shot[2];
//	shot[index].speed = 4;
	shot[index].speed = 2;
	shot[index].rad = atan2(py - y, px - x) + (rand() % 41 - 20) * M_PI / 180;
	shot[index].pattern = 1;
	shot[index].type = 3;
	s_shot = true;
}

void BOSS::ShotPattern2(
	double	px,
	double	py,
	double	trad
)
{
	//	if (scount % 10 == 0) {
	if (scount % 20 != 0) {
		return;;
	}

	//何発発射したか
	int num = 0;

	//空いてる弾の添え字
	int index = 0;

	trad = atan2(py - y, px - x);
	while ((index = ShotSearch()) != -1) {
		shot[index].gh = gh_shot[0];
		//				shot[index].speed = 5;
		shot[index].speed = 2.5;
		shot[index].rad = trad + num * ((360 / 20) * M_PI / 180);
		shot[index].pattern = 2;
		shot[index].type = 1;
		++num;
		if (num == 20) {
			break;
		}
		s_shot = true;
	}
}

void BOSS::ShotPattern3(
	double	px,
	double	py
)
{
	//何発発射したか
	int num = 0;

	//空いてる弾の添え字
	int index = 0;

	//	if (scount % 15 == 0) {
	if (scount % 30 == 0) {
		while ((index = ShotSearch()) != -1) {
			shot[index].gh = gh_shot[0];
			//					shot[index].speed = 3;
			shot[index].speed = 1.5;
			shot[index].pattern = 3;
			shot[index].rad = ((360 / 20) * M_PI / 180) * num + ((scount / 30) * 0.08);
			shot[index].type = 1;

			++num;

			if (num == 20) {
				break;
			}
			s_shot = true;
		}
	}

	num = 0;

	//	if (scount % 5 == 0 && temp_scount <= scount) {
	if (scount % 10 == 0 && temp_scount <= scount) {
		while ((index = ShotSearch()) != -1) {
			shot[index].gh = gh_shot[1];
			//					shot[index].speed = 6;
			shot[index].speed = 3;
			shot[index].pattern = 3;
			shot[index].type = 2;

			if (num == 0) {
				shot[index].x = x - 50;
				shot[index].rad = atan2(py - y, px - (x - 50));
			}
			else if (num == 1) {
				shot[index].x = x + 50;
				shot[index].rad = atan2(py - y, px - (x + 50));
			}

			++num;

			if (num == 2) {

				//5発分打ち終わったら、60ループ(一秒間)停止
				if (temp_scount + 40 == scount) {
					temp_scount += 120;
				}
				break;
			}

			s_shot = true;
		}
	}
}

void BOSS::ShotMove()
{
	//scountを戻すかどうかのフラグ
	bool scflag = false;

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
		case 2:
		case 3:
			shot[i].x += shot[i].speed * cos(shot[i].rad);
			shot[i].y += shot[i].speed * sin(shot[i].rad);
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

void BOSS::SetDamageSetting()
{

	prev_x = x;
	prev_y = y;

	movex = 200 - x;
	movey = 80 - y;

	angle = 0;

	no_damage = true;

	SetMovePattern(4);
	SetShotPattern(4);

}

void BOSS::GetPosition(
	double* x,
	double* y
)
{
	*x = this->x;
	*y = this->y;

}

void BOSS::SetFlag(
	bool	flag
)
{
	this->flag = flag;
}

void BOSS::SetShotFlag(
	int		index,
	bool	flag
)
{
	shot[index].flag = flag;
}

void BOSS::SetMovePattern(
	int		pattern
)
{
	prev_move_pattern = move_pattern;
	move_pattern = pattern;
}

void BOSS::SetShotPattern(
	int		pattern
)
{

	prev_shot_pattern = shot_pattern;
	shot_pattern = pattern;

}

void BOSS::SetGrazeFlag(
	int index
)
{
	shot[index].gflag = true;
}

bool BOSS::GetGrazeFlag(
	int index
)
{
	return shot[index].gflag;
}

bool BOSS::GetShotPosition(
	int		index,
	double*	x,
	double*	y,
	int*	type
)
{
	if (shot[index].flag) {
		*x = shot[index].x;
		*y = shot[index].y;
		*type = shot[index].type;
		return true;
	}
	else {
		return false;
	}

}

bool BOSS::GetShotSound()
{
	return s_shot;
}

bool BOSS::GetFlag()
{
	return flag;
}

bool BOSS::GetNodamageFlag()
{
	return no_damage;
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

int BOSS::HpSet(
	int damage
)
{
	prev_hp = hp;
	hp -= damage;

	return hp;
}

int BOSS::GetPrevHp()
{
	return prev_hp;

}