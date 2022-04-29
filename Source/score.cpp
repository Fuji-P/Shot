/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

#include "pch.h"
#include "score.h"

SCORE::SCORE()
{

	if (-1 == LoadDivGraph("board2.png", 4, 1, 4, 160, 32.5, g_board)) {
		MSG("�G���[����");
	}
	if (-1 == LoadDivGraph("number.png", 10, 10, 1, 19, 27, g_number)) {
		MSG("�G���[����");
	}

	high_score = 0;
	score = 0;
	graze = 0;
	life = 0;
	power = 0;

}

void SCORE::All()
{
	Draw();
}

void SCORE::Draw()
{
	char buf[100];
	int num;

	//�X�R�A�{�[�h�̕����̕`��

	//�n�C�X�R�A
	DrawGraph(SCORE_X, 10, g_board[0], TRUE);
	//�X�R�A
	DrawGraph(SCORE_X, 70, g_board[1], TRUE);
	//�O���C�Y
	DrawGraph(SCORE_X, 140, g_board[2], TRUE);
	//���C�t
	DrawGraph(SCORE_X, 170, g_board[3], TRUE);

	//�n�C�X�R�A�`��
	num = sprintf(buf, "%d", high_score);
	for (int i = 0; i < num; ++i) {
		DrawGraph(SCORE_X + 20 + i * 19, 35, g_number[(buf[i] - '0')], TRUE);
	}

	//�X�R�A�`��
	num = sprintf(buf, "%d", score);
	for (int i = 0; i < num; ++i) {
		DrawGraph(SCORE_X + 20 + i * 19, 95, g_number[(buf[i] - '0')], TRUE);
	}

	//�O���C�Y���`��
	num = sprintf(buf, "%d", graze);
	for (int i = 0; i < num; ++i) {
		DrawGraph(SCORE_X + 100 + i * 19, 145, g_number[(buf[i] - '0')], TRUE);
	}

	//���C�t���`��
	num = sprintf(buf, "%d", life);
	for (int i = 0; i < num; ++i) {
		DrawGraph(SCORE_X + 100 + i * 19, 175, g_number[(buf[i] - '0')], TRUE);
	}
}

void SCORE::SetScore(SCOREDATA data, int val)
{
	switch (data) {

	case HIGH_SCORE:
		high_score += val;
		break;

	case CURRENT_SCORE:
		score += val;
		break;

	case GRAZE_SCORE:
		graze += val;
		break;

	case LIFE_SCORE:
		life = val;
		break;
	}
}

int SCORE::GetScore(SCOREDATA data)
{

	switch (data) {

	case HIGH_SCORE:
		return high_score;
		break;

	case CURRENT_SCORE:
		return score;
		break;

	case GRAZE_SCORE:
		return graze;
		break;

	case LIFE_SCORE:
		return life;
		break;
	}

	//�Y�����Ȃ��Ƃ��́[1��Ԃ��B
	return -1;
}
