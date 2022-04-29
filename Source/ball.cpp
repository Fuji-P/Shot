/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include "pch.h"
#include "ball.h"

BALL::BALL()
{

	gh = LoadGraph("awa.png");
	x = 0;
	y = 0;
	angle = 0;
	raise = 2;
	toggle = false;
}

void BALL::All(
	double	px,
	double	py
)
{

	Move(
		px,
		py
	);
	Draw();

}

void BALL::Move(
	double	px,
	double	py
)
{
	angle += raise;

	x = px;

	y = py + sin(angle * M_PI / 180) * BALL_SHAKE;

	if (angle == 90) {
		toggle = true;
	}
	else if (angle == -90) {
		toggle = false;
	}


	if (toggle) {
		raise = -2;
	}
	else {
		raise = 2;
	}
}

void BALL::Draw()
{
	DrawRotaGraph(x + BALL_INITX, y + BALL_INITY, 1.0, 0, gh, TRUE);
	DrawRotaGraph(x - BALL_INITX, y + BALL_INITY, 1.0, 0, gh, TRUE);
}

double BALL::GetPosition()
{
	return y;

}
