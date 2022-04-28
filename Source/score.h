/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
*/

enum SCOREDATA {
	HIGH_SCORE,
	CURRENT_SCORE,
	GRAZE_SCORE,
	LIFE_SCORE
};

class SCORE {
private:
	//�O���t�B�b�N�n���h��
	int g_board[4], g_number[10];

	int high_score, score, graze, life;

private:
	void Draw();
public:
	void SetScore(SCOREDATA data, int val);
	int GetScore(SCOREDATA data);
	void All();
	SCORE();
};